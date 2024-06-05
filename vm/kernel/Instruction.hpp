#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <functional>
#include "Cpu.hpp"
#include "Memory.hpp"
#include "Microprogram.hpp"

/**
 * @class Instruction
 * @brief Macro instruction.
 */
template <size_t S>
class Instruction final {
 public:
    Instruction(
        Microprogram<S>* microprogram,
        const size_t& num_args,
        const std::function<void(Cpu<S>&, Memory&)>& process_function_);

    void execute(Cpu<S>& cpu, Memory& memory, const address_t& instruction_addr);

 private:
    Microprogram<S>* microprogram_;
    const std::function<void(Cpu<S>&, Memory&)> process_function_;
    const size_t num_args_;
};

template <size_t S>
Instruction<S>::Instruction(
    Microprogram<S>* microprogram,
    const size_t& num_args,
    const std::function<void(Cpu<S>&, Memory&)>& process_function_) :
    microprogram_(microprogram), process_function_(process_function_), num_args_(num_args) {}

template <size_t S>
void Instruction<S>::execute(Cpu<S>& cpu, Memory& memory, const address_t& instruction_addr) {
    microprogram_->execute(cpu, memory, instruction_addr, num_args_, process_function_);
}

#endif
