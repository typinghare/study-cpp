#include <iostream>
#include "kernel/Memory.hpp"
#include "tr/TuringComplete.hpp"

int main() {
    const auto jump = Tr::Micro::JUMP(Tr::word(0, 42));
    Tr::execute(jump);
    std::cout << Tr::reg(Tr::R_PC).toHex() << std::endl;

    return 0;
}
