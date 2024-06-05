#ifndef WORD_HPP
#define WORD_HPP

#include <vector>
#include "Virtual.hpp"

/**
 * @class Word
 * @brief A class representing a word of memory with specific endianness.
 */
class Word final {
 public:
    /**
     * @brief Constructs a Word object with the specified size and endianness type.
     * @param size The size of the word in bytes.
     */
    explicit Word(const size_t& size);

    /**
     * @brief Sets the bytes of the word.
     * @param bytes Pointer to the bytes to be set.
     */
    void setBytes(const byte* bytes);

    /**
     * @brief Gets the bytes of the word.
     * @return A vector containing the bytes of the word.
     */
    [[nodiscard]] std::vector<byte> getBytes() const;

    /**
     * @brief Gets the size of the word.
     * @return the size of the word.
     */
    [[nodiscard]] size_t size() const;

    [[nodiscard]] std::string toHex() const;

 private:
    /**
     * @brief The size of the word in bytes.
     */
    size_t size_;

    /**
     * @brief Container for the word's bytes.
     */
    std::vector<byte> data_;
};

#endif
