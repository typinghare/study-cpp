#ifndef CPU_HPP
#define CPU_HPP
#include "RegisterFile.hpp"

class Cpu {
 public:
    explicit Cpu(RegisterFile register_file);

    [[nodiscard]] Register& getRegister(const size_t& index);

 private:
    RegisterFile register_file_;
};

#endif
