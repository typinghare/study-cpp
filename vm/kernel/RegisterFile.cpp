#include "RegisterFile.hpp"

RegisterFile::RegisterFile(const size_t& size, const size_t& word_size) :
    registers_(size, Register(word_size)), size_(size), word_size_(word_size) {}

Register& RegisterFile::get(const size_t& index)  {
    if (index >= size_) {
        throw std::invalid_argument("Invalid index: " + std::to_string(index));
    }

    return registers_.at(index);
}
