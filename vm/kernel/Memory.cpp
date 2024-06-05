#include "Memory.hpp"

#include <string>

Memory::Memory(const size_t& size) : size_(size) { data_ = new byte[size]; }

Memory::~Memory() {
    // delete[] data_;
}

byte Memory::read(const address_t& address) const {
    if (address >= size_) {
        throw InvalidAddress(address, size_);
    }

    return data_[address];
}

void Memory::write(const address_t& address, const byte& value) const {
    if (address >= size_) {
        throw InvalidAddress(address, size_);
    }

    data_[address] = value;
}

size_t Memory::size() const { return size_; }

Memory::InvalidAddress::InvalidAddress(const address_t& address, const size_t& size) :
    address_(address), size_(size) {
    message = "Address is out of range: " + std::to_string(address_) +
              ". The size of the memory block is: " + std::to_string(size_) + ".";
}

const char* Memory::InvalidAddress::what() const noexcept { return message.c_str(); }
