#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <Logger.h>

namespace messagefactory
{
// Convert from hexStream to std::vector type of bytes
inline const std::vector<uint8_t> bytesFromHex(const std::string &hexStr)
{
    if (hexStr.length() % 2 != 0)
    {
        PCPP_LOG(pcpp::Logger::Error, "Hex string must have an even length");
    }

    std::vector<uint8_t> bytes;
    bytes.reserve(hexStr.length() / 2);

    for (size_t i = 0; i < hexStr.length(); i += 2)
    {
        uint8_t byte = std::stoi(hexStr.substr(i, 2), nullptr, 16);
        bytes.push_back(byte);
    }

    return bytes;
}
inline void printStdVectorBytesStream(std::vector<uint8_t> vector)
{
        std::ostringstream os;
        const int _size = vector.size();
        std::cout << "[";
        for (int i = 0; i < _size; i++)
        {
            os << static_cast<int>(vector[i]);
            if (i < _size - 1)
            {
                os << ",";
            }
        }
        os << "]";
        std::cout << os.str() << std::endl;
}

template <typename T>
inline T endian_be(T value) 
{
    static_assert(std::is_integral<T>::value, "T must be an integral type.");

    T result = 0;
    for (size_t i = 0; i < sizeof(T); ++i) {
        result |= ((value >> (i * 8)) & 0xFF) << ((sizeof(T) - 1 - i) * 8);
    }
    return result;
}
template <typename T>

inline T endian_le(T value) 
{
    static_assert(std::is_integral<T>::value, "T must be an integral type.");

    T result = 0;
    for (size_t i = 0; i < sizeof(T); ++i) {
        result |= ((value >> ((sizeof(T) - 1 - i) * 8)) & 0xFF) << (i * 8);
    }
    return result;
}
}