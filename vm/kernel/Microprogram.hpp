#ifndef MICROPROGRAM_HPP
#define MICROPROGRAM_HPP

#include <functional>
#include "Cpu.hpp"
#include "Memory.hpp"
#include "Microprogram.hpp"

template <size_t S>
class Microprogram {
 public:
    virtual ~Microprogram() = default;
    virtual void execute(
        Cpu<S>& cpu,
        Memory& memory,
        const address_t& instruction_addr,
        const size_t& num_args,
        const std::function<void(Cpu<S>&, Memory&)>& process_function_) = 0;
};

#endif
