#ifndef CPU_HPP
#define CPU_HPP

#include "Memory.hpp"
#include "RegisterFile.hpp"

template <size_t S>
class Cpu {
 public:
    explicit Cpu(RegisterFile<S> register_file);

    [[nodiscard]] Register<S>& getRegister(const size_t& register_index);

    void
    loadFromMemory(const Memory& memory, const address_t& address, const size_t& register_index);

    void
    writeToMemory(const Memory& memory, const address_t& address, const size_t& register_index);

    Word<S> readRegister(const size_t& register_index);

    void loadRegister(const size_t& register_index, const Word<S>& word);

    void moveRegister(const size_t& from_register_index, const size_t& to_register_index);

 private:
    RegisterFile<S> register_file_;
};

template <size_t S>
Cpu<S>::Cpu(RegisterFile<S> register_file) : register_file_(register_file) {}

template <size_t S>
Register<S>& Cpu<S>::getRegister(const size_t& register_index) {
    return register_file_.get(register_index);
}

template <size_t S>
void Cpu<S>::loadFromMemory(
    const Memory& memory, const address_t& address, const size_t& register_index) {
    // Load contiguous bytes from the memory
    std::array<byte, S> byteArray;
    for (int i = 0; i < S; ++i) {
        byteArray[i] = memory.read(address + i);
    }

    // Load the bytes to the register
    register_file_.get(register_index).load(Word{ byteArray });
}

template <size_t S>
void Cpu<S>::writeToMemory(
    const Memory& memory, const address_t& address, const size_t& register_index) {
    const std::array<byte, S> byteArray = register_file_.get(register_index).read().getBytes();

    for (int i = 0; i < S; ++i) {
        memory.write(address + i, byteArray[i]);
    }
}

template <size_t S>
Word<S> Cpu<S>::readRegister(const size_t& register_index) {
    return getRegister(register_index).read();
}

template <size_t S>
void Cpu<S>::loadRegister(const size_t& register_index, const Word<S>& word) {
    return getRegister(register_index).load(word);
}
template <size_t S>
void Cpu<S>::moveRegister(const size_t& from_register_index, const size_t& to_register_index) {
    loadRegister(to_register_index, readRegister(from_register_index));
}

#endif
