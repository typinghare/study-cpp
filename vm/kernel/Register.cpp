#include "Register.hpp"

#include <iostream>

Register::Register(const size_t& size) : word_(Word(size)), size_(size) {}

void Register::load(const Word& word) {
    if (word.size() != size_) {
        throw LoadException(word.size(), size_);
    }

    word_ = word;
    std::cout << "";
}

Word Register::read() const { return word_; }

Register::LoadException::LoadException(const size_t& word_size, const size_t& register_size) :
    word_size_(word_size), register_size_(register_size) {
    message_ = "LoadException: Attempted to load a word of size " + std::to_string(word_size_) +
               " into a register of size " + std::to_string(register_size_) + ".";
}

const char* Register::LoadException::what() const noexcept { return message_.c_str(); }
