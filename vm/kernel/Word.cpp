#include "Word.hpp"
#include <sstream>

Word::Word(const size_t& size) : size_(size), data_(size, 0) {}

void Word::setBytes(const byte* bytes) { std::memcpy(data_.data(), bytes, size_); }

[[nodiscard]] std::vector<byte> Word::getBytes() const { return data_; }

size_t Word::size() const { return size_; }

std::string Word::toHex() const {
    std::stringstream ss;
    ss << "0x";

    for (const auto _byte : data_) {
        ss << byteToHex(_byte);
    }

    return ss.str();
}
