#ifndef TURINGCOMPLETE_HPP
#define TURINGCOMPLETE_HPP

#include "../kernel/Cpu.hpp"
#include "../kernel/Memory.hpp"
#include "../kernel/MicroInstruction.hpp"

#define MI_PARAMS                                                                                  \
    [[maybe_unused]] Cpu &cpu, [[maybe_unused]] auto &memory, [[maybe_unused]] const auto &arg

namespace Tr {

// Constants
constexpr size_t WORD_SIZE = 2;
constexpr size_t MEMORY_SIZE = 1 << WORD_SIZE * 8;
constexpr size_t REGISTER_NUMBER = 16;

// Registers
constexpr size_t R_PC = 0;  // Program Counter
constexpr size_t R_AC = 1;  // Accumulator
constexpr size_t R_SP = 2;  // Stack Pointer
constexpr size_t R_IR = 3;  // Instruction Register
constexpr size_t R_TI = 4;  // Temporary Instruction Register
constexpr size_t R_ST = 5;  // Status Register [X, X, X, X, X, X, NEGATIVE_FLAG, ZERO_FLAG]
constexpr size_t R_C0 = 6;  // Constant 0
constexpr size_t R_C1 = 7;  // Constant 1
constexpr size_t R_N1 = 8;  // Constant -1
constexpr size_t R_A0 = 9;  // Argument Register 0
constexpr size_t R_A1 = 10;  // Argument Register 1
constexpr size_t R_A2 = 11;  // Argument Register 2
constexpr size_t R_T0 = 12;  // Temporary Register 0
constexpr size_t R_T1 = 13;  // Temporary Register 1
constexpr size_t R_T2 = 14;  // Temporary Register 2
constexpr size_t R_T3 = 15;  // Temporary Register 2

// Components
inline Memory memory{ MEMORY_SIZE };
inline Cpu cpu{ RegisterFile(REGISTER_NUMBER, WORD_SIZE) };

// Micro instructions
namespace Micro {

// Set the program counter
inline MicroInstruction<WORD_SIZE> JUMP([](MI_PARAMS) { cpu.getRegister(R_PC).load(arg); });

// Jump if the zero flag is set
inline MicroInstruction<WORD_SIZE> JUMP_ZERO([](MI_PARAMS) {
    // Get the lower byte
    const byte lower = cpu.getRegister(R_ST).read().getBytes().at[1];
    if (const auto zeroFlag = lower & 0b1; zeroFlag == 1) {
        cpu.getRegister(R_PC).load(arg);
    }
});

// Jump if the negative flag is set
inline MicroInstruction<WORD_SIZE> JUMP_NEG([](MI_PARAMS) {
    // Get the lower byte
    const byte lower = cpu.getRegister(R_ST).read().getBytes().at[1];
    if (const auto negativeFlag = (lower & 0b10) >> 1; negativeFlag == 1) {
        cpu.getRegister(R_PC).load(arg);
    }
});

}  // namespace Micro

namespace Macro {

}

inline void execute(const MicroInstruction<WORD_SIZE>& instruction) {
    instruction.execute(cpu, memory);
}

inline Word word(const byte& byte1, const byte& byte2) {
    const byte bytes[2] = { byte1, byte2 };
    Word word(2);
    word.setBytes(bytes);

    return word;
}

inline Word word(const int& byte1, const int& byte2) {
    const byte bytes[2] = { static_cast<byte>(byte1), static_cast<byte>(byte2) };
    Word word(2);
    word.setBytes(bytes);

    return word;
}

inline Word reg(const int& index) { return cpu.getRegister(index).read(); }

}  // namespace Tr

#endif
