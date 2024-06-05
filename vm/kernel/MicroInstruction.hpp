#ifndef MICROINSTRUCTION_HPP
#define MICROINSTRUCTION_HPP

#include <functional>
#include "Cpu.hpp"
#include "Instruction.hpp"
#include "Memory.hpp"

using InstructionProcessFunction = std::function<void(Cpu&, Memory&, const Word&)>;

/**
 * @class MicroInstruction
 * @brief A class representing a microinstruction to be executed by the CPU.
 */
template <int>
class MicroInstruction final : public Instruction {
 public:
    /**
     * @brief Constructs a MicroInstruction object with the specified process function.
     * @param process_function The function representing the microinstruction's process.
     */
    explicit MicroInstruction(InstructionProcessFunction process_function);

    /**
     * @brief Executes the microinstruction's process function with the given CPU and memory.
     * @param cpu The CPU object.
     * @param memory The Memory object.
     */
    void execute(Cpu& cpu, Memory& memory) const override;

    MicroInstruction operator()(const Word& word);

 private:
    /**
     * @brief The function representing the microinstruction's process.
     */
    InstructionProcessFunction process_function_;

    /**
     * @brief The parameter of the instruction.
     */
    Word word_;
};

template <int WS>
MicroInstruction<WS>::MicroInstruction(InstructionProcessFunction process_function) :
    process_function_(std::move(process_function)), word_(Word(WS)) {}

template <int WS>
void MicroInstruction<WS>::execute(Cpu& cpu, Memory& memory) const {
    process_function_(cpu, memory, word_);
}

template <int WS>
MicroInstruction<WS> MicroInstruction<WS>::operator()(const Word& word) {
    MicroInstruction copy = *this;
    copy.word_ = word;

    return copy;
}

#endif  // MICROINSTRUCTION_HPP
