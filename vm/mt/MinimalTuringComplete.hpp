#ifndef MINIMALTURINGCOMPLETE_HPP
#define MINIMALTURINGCOMPLETE_HPP

#include "../kernel/Cpu.hpp"
#include "../kernel/Instruction.hpp"
#include "../kernel/Memory.hpp"
#include "../kernel/Microprogram.hpp"

namespace MT {

// Constants
constexpr size_t WORD_SIZE = 2;
constexpr size_t MEMORY_SIZE = 1 << WORD_SIZE * 8;
constexpr size_t REGISTER_COUNT = 16;

// Registers
constexpr size_t R_PC = 0;  // Program Counter
constexpr size_t R_SP = 1;  // Stack Pointer
constexpr size_t R_IR = 3;  // Instruction Register
constexpr size_t R_TI = 4;  // Temporary Instruction Register
constexpr size_t R_ST = 5;  // Status Register [X, X, X, X, X, JUMP_FLAG, NEGATIVE_FLAG, ZERO_FLAG]
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

// Status Register flags
constexpr size_t ST_ZERO = 0;
constexpr size_t ST_NEGATIVE = 1;
constexpr size_t ST_JUMP = 2;

// Components
inline Memory memory{ MEMORY_SIZE };
inline Cpu cpu{ RegisterFile<WORD_SIZE>(REGISTER_COUNT) };

inline bool getStatusFlag(Cpu<WORD_SIZE>& cpu, const size_t& flag) {
    const byte _byte = cpu.readRegister(R_ST).getBytes().at(1);
    return (_byte >> flag & 0b1) == 1;
}

inline void setStatusFlag(Cpu<WORD_SIZE>& cpu, const size_t& flag, const bool& status) {
    auto bytes = cpu.readRegister(R_ST).getBytes();
    const auto _byte = bytes.at(1);
    const auto mask0 = 0xFF & 0 << flag;
    const auto mask1 = (status ? 1 : 0) << flag;
    bytes[1] = _byte & mask0 | mask1;
    cpu.loadRegister(R_ST, Word{ bytes });
}

// Microprogram
class MTMicroprogram final : public Microprogram<WORD_SIZE> {
 public:
    void execute(
        Cpu<WORD_SIZE>& cpu,
        Memory& memory,
        const address_t& instruction_addr,
        const size_t& num_args,
        const std::function<void(Cpu<WORD_SIZE>&, Memory&)>& process_function_) override {
        // Load the arguments to the register
        for (int i = 0; i < num_args; ++i) {
            const size_t arg_address = instruction_addr + (i + 1) * WORD_SIZE;
            cpu.loadFromMemory(memory, arg_address, R_A0 + i);
        }

        // Invoke the process function
        process_function_(cpu, memory);

        // Increase the PC if the jump flag is 0, else, jump to IR
        if (const auto jumpFlag = getStatusFlag(cpu, ST_JUMP); !jumpFlag) {
        } else {
            cpu.moveRegister(R_IR, R_PC);
        }

        // reset the jump flag
        setStatusFlag(cpu, ST_JUMP, false);
    }
};
inline MTMicroprogram microprogram;

// Instructions
namespace Instr {

// Process function parameters
#define PF_PARAM Cpu<WORD_SIZE>&cpu, [[maybe_unused]] Memory &memory

using MTInstruction = Instruction<WORD_SIZE>;

// <register_index> <value>
inline MTInstruction LOAD_IMMEDIATE{ &microprogram, 2, [](PF_PARAM) {
                                        const auto registerIndex =
                                            cpu.readRegister(R_A0).getBytes().at(1);
                                        cpu.loadRegister(registerIndex, cpu.readRegister(R_A1));
                                    } };

// <from_register_index> <to_register_index>
inline MTInstruction MOVE_RR{ &microprogram, 2, [](PF_PARAM) {
                                 const auto fromRegisterIndex =
                                     cpu.readRegister(R_A0).getBytes().at(1);
                                 const auto toRegisterIndex =
                                     cpu.readRegister(R_A1).getBytes().at(1);
                                 cpu.moveRegister(fromRegisterIndex, toRegisterIndex);
                             } };

//
inline MTInstruction JUMP{ &microprogram, 1, [](PF_PARAM) {
                              cpu.moveRegister(R_A0, R_IR);
                              setStatusFlag(cpu, ST_JUMP, true);
                          } };

}  // namespace Instr

/**
 * @brief Executes one instruction.
 */
inline void execute(Instruction<WORD_SIZE>& instruction, const address_t& instruction_address) {
    instruction.execute(cpu, memory, instruction_address);
}

}  // namespace MT

#endif
