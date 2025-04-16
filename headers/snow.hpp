#ifndef __SNOW_H_
#define __SNOW_H_

#include <algorithm>
#include <cstdint>
#include <cstring>

template <typename A, typename B>
inline std::ptrdiff_t GetPtrDiff(A* a, B* b)
{
    return reinterpret_cast<std::ptrdiff_t>(a) -
           reinterpret_cast<std::ptrdiff_t>(b);
}

constexpr const uint32_t SNOW_BLOCKS_SIZE = sizeof(uint32_t);
constexpr const uint32_t SNOW_NUM_BLOCKS = 16;

class SnowCipher
{
private:
    uint32_t m_State[20];
    uint32_t m_Buffer[16];
    uint32_t m_BlocksAvailable;

public:
    void SetKey(const uint8_t* key);

    template <typename T>
    inline void DecryptBuffer(T* outBuffer, const uint8_t* inBuffer,
                              uint32_t dataSize)
    {
        this->DecryptBufferImpl(reinterpret_cast<uint32_t*>(outBuffer),
                                inBuffer, dataSize);
    }

private:
    void DecryptBufferImpl(uint32_t* outBuffer, const uint8_t* inBuffer,
                           uint32_t dataSize);
    void DecryptBlock();
};

#endif  // __SNOW_H_
