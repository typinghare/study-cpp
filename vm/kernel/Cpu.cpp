#include "Cpu.hpp"

Cpu::Cpu(RegisterFile register_file) : register_file_(std::move(register_file)) {}

Register& Cpu::getRegister(const size_t& index) { return register_file_.get(index); }
