
#include <iostream>
#include "mt/MinimalTuringComplete.hpp"

int main() {
    MT::memory.write(2, 0xAB);
    MT::memory.write(3, 0xCD);
    MT::execute(MT::Instr::JUMP, 0);

    std::cout << MT::cpu.readRegister(MT::R_PC).toHexString() << std::endl;

    return 0;
}
