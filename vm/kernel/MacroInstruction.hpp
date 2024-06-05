#ifndef MACROINSTRUCTION_HPP
#define MACROINSTRUCTION_HPP

#include <vector>
#include "Instruction.hpp"
#include "MicroInstruction.hpp"

template <int WS>
class MacroInstruction final : public Instruction {
 public:
    void execute(Cpu& cpu, Memory& memory) const override;

 private:
    std::vector<MicroInstruction<WS>> micro_instructions_;
};

template <int WS>
void MacroInstruction<WS>::execute(Cpu& cpu, Memory& memory) const {
    for (const auto& micro_instruction : micro_instructions_) {
        micro_instruction.execute(cpu, memory);
    }
}

#endif
