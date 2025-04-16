#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>

#include "cmdparser.hpp"
#include "fsutils.hpp"

#include "pakfile.hpp"
#include "util.hpp"

inline void PrintHeader()
{
    std::cout << "csopak - A 'pak' file extractor for Nexon's Counter-Strike: "
                 "Online\n";
}

inline void PrintHelp()
{
    std::cout << "Usages:\n"
              << "\tcsopak <INPUT FILE> [OPTIONS]\n"
              << "\n"
              << "Options:\n"
              << "\t-o <PATH>\tExtract files to <PATH> directory (default is "
                 "current directory, ignored when '-l' is used)\n"
              << "\t-l\tList files inside the PAK file\n"
              << "\t-h\tPrints this help text\n"
              << "\n"
              << "Examples:\n"
              << "\tcsopak common_00004.pak\n"
              << "\tcsopak na_00000.pak -l\n";
}

inline int ListEntries(fs::path& sourceFile, std::vector<uint8_t> vDataBuf)
{
    PakFile pakFile(std::move(vDataBuf),
                    sourceFile.filename().generic_u16string());

    if (pakFile.ParseHeader() == false)
    {
        std::cout << "Failed to parse file '" << sourceFile << "' header\n";
        return 1;
    }

    if (pakFile.ParseEntries() == false)
    {
        std::cout << "Failed to parse file '" << sourceFile << "' entries\n";
        return 1;
    }

    std::cout << "\n";

    auto header = pakFile.GetHeader();

    std::cout << "PAK header data -- version: " << (uint32_t)header.PakVersion
              << " number of files: " << header.NumEntries << "\n\n";

    for (const auto& entry : pakFile.GetEntries())
    {
        std::cout << String_UTF16toUTF8(entry.FilePath) << "\t"
                  << entry.RealSize << " bytes\n";
    }

    return 0;
}

inline int ExtractEntries(const fs::path& outPath, const fs::path& sourceFile,
                          std::vector<uint8_t> vDataBuf)
{
    PakFile pakFile(std::move(vDataBuf),
                    sourceFile.filename().generic_u16string());

    if (pakFile.ParseHeader() == false)
    {
        std::cout << "Failed to parse file '" << sourceFile << "' header\n";
        return 1;
    }

    if (pakFile.ParseEntries() == false)
    {
        std::cout << "Failed to parse file '" << sourceFile << "' entries\n";
        return 1;
    }

    for (const auto& entry : pakFile.GetEntries())
    {
        auto [unpacked, vOutBuf] = pakFile.UnpackEntry(entry);

        if (unpacked == false)
        {
            std::cerr << "Failed to unpack entry '"
                      << String_UTF16toUTF8(entry.FilePath) << "'\n";
            return 1;
        }

        fs::path outFilePath = outPath;
        outFilePath /= fs::path(entry.FilePath);

        fs::create_directories(outFilePath.parent_path());

        const bool writeRes = WriteBufferToFile(vOutBuf, outFilePath.string());

        if (writeRes == false)
        {
            std::cerr << "Failed to write unpacked file to " << outFilePath
                      << "\n";
            return 1;
        }

        std::cout << "Wrote decrypted file to " << outFilePath << "\n";
    }

    return 0;
}

int main(int argc, const char* argv[])
{
    CmdParser cmd(argv, argc);

    PrintHeader();

    if (cmd.GetArgsNum() < 2 || cmd.HasOption("-h") == true)
    {
        PrintHelp();
        return 0;
    }

    fs::path sourceFile = cmd.GetByIndex(1);
    auto [bFileRead, vDataBuf] = ReadFileToBuffer(sourceFile.generic_string());

    if (bFileRead == false)
    {
        std::cerr << "Failed to read encrypted file " << sourceFile << "\n";
        return 1;
    }

    if (cmd.HasOption("-l") == true)
    {
        std::cout << "Listing files inside '" << sourceFile << "'...\n";
        return ListEntries(sourceFile, std::move(vDataBuf));
    }

    fs::path outPath;

    if (cmd.HasOption("-o") == true)
    {
        outPath = cmd.GetOption("-o");
    }
    else
    {
        outPath = fs::current_path();
    }

    std::cout << "Extracting files inside '" << sourceFile << "'...\n";
    return ExtractEntries(outPath, sourceFile, std::move(vDataBuf));
}
