#ifndef WORD_HPP
#define WORD_HPP

#include <array>
#include <sstream>
#include "Virtual.hpp"

/**
 * @class Word
 * @brief A class representing a word of memory with a specific size.
 * @tparam S The size of the word in bytes.
 */
template <size_t S>
class Word final {
 public:
    Word();

    explicit Word(const std::array<byte, S>& bytes);

    /**
     * @brief Sets the bytes of the word.
     * @param bytes An array containing the bytes to be set.
     */
    void setBytes(const std::array<byte, S>& bytes);

    /**
     * @brief Gets the bytes of the word.
     * @return An array containing the bytes of the word.
     */
    [[nodiscard]] std::array<byte, S> getBytes() const;

    [[nodiscard]] std::string toHexString() const;

 private:
    /**
     * @brief Storage for the word's bytes.
     */
    std::array<byte, S> bytes_{};
};

template <size_t S>
Word<S>::Word() = default;

template <size_t S>
Word<S>::Word(const std::array<byte, S>& bytes) {
    setBytes(bytes);
}

template <size_t S>
void Word<S>::setBytes(const std::array<byte, S>& bytes) {
    bytes_ = bytes;
}

template <size_t S>
std::array<byte, S> Word<S>::getBytes() const {
    return bytes_;
}

template <size_t S>
std::string Word<S>::toHexString() const {
    std::stringstream ss;
    ss << "0x";

    for (const auto _byte : bytes_) {
        ss << to_hex_string(_byte);
    }

    return ss.str();
}

#endif  // WORD_HPP
