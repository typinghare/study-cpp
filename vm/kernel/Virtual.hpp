#ifndef VIRTUAL_HPP
#define VIRTUAL_HPP

#include <cstddef>
#include <string>

// A byte is an unsigned char
typedef unsigned char byte;

// Address type is usigned long
using address_t = size_t;

/**
 * @brief Converts a byte to a hex string.
 * @param byte The byte to process.
 * @return a hex string.
 */
inline std::string to_hex_string(const byte& byte) {
    static constexpr char map[16] = { '0', '1', '2', '3', '4', '5', '6', '7',
                                      '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    return std::string(1, map[byte >> 4]) + map[byte & 0xF];
}

#endif
