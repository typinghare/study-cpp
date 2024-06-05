#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include "Cpu.hpp"
#include "Memory.hpp"

class Instruction {
 public:
    virtual ~Instruction() = default;

 private:
    /**
     * @brief Executes the microinstruction's process function with the given CPU and memory.
     * @param cpu The CPU object.
     * @param memory The Memory object.
     */
    virtual void execute(Cpu& cpu, Memory& memory) const = 0;
};

#endif
