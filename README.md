# CSO Voxel

A command line tool to extract files from PAK files used in the video game Counter-Strike Online.

The PAK format is a container for encrypted files and/or compressed files.
For encryption, it seems to be using some custom version of SOSEMANUK, which was decompiled as I couldn't find any library that worked.
At the moment this tool does not support decompression.

The library must be compiled with a C++20 compatible compiler.

The program has been tested under:

- GNU/Linux with GCC 10.2.0
- GNU/Linux (Wine) with MinGW 10.2.0

## Usage

Usage:

- csopak \<INPUT FILE\> [OPTIONS]

Options:

- -o \<PATH\> Extract files to \<PATH\> directory (default is current directory, ignored when '-l' is used)
- -l List files inside the PAK file
- -h Prints this help text

Examples:

- csopak common_00004.pak
- csopak na_00000.pak -l

## License

csovxl is licensed under the GNU GPLv3 license.

## Credits

- Luís Leite - https://git.sr.ht/~leite/cso-pak
