#ifndef VIRTUAL_HPP
#define VIRTUAL_HPP

#include <cstddef>

using byte = unsigned char;
using address_t = size_t;

inline std::string byteToHex(const byte byte) {
    static constexpr char map[16] = { '0', '1', '2', '3', '4', '5', '6', '7',
                                      '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    return std::string(1, map[byte >> 4]) + map[byte & 0xF];
}

#endif
