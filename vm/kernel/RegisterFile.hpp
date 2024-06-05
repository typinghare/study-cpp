#ifndef REGISTERFILE_HPP
#define REGISTERFILE_HPP

#include "Register.hpp"
#include <vector>

/**
 * @class RegisterFile
 * @brief A class representing a register file containing multiple registers.
 */
template <size_t S>
class RegisterFile final {
 public:
    /**
     * @brief Constructs a RegisterFile object with the specified number of registers.
     * @param size The number of registers in the register file.
     */
    explicit RegisterFile(const size_t& size);

    /**
     * @brief Gets a reference to the register at the specified index.
     * @param index The index of the register to retrieve.
     * @return A reference to the register at the specified index.
     * @throws std::out_of_range if the index is out of bounds.
     */
    [[nodiscard]] Register<S>& get(const size_t& index);

 private:
    /**
     * @brief Vector containing the registers in the register file.
     */
    std::vector<Register<S>> registers_;

    /**
     * @brief The number of registers in the register file.
     */
    size_t size_;
};

template <size_t S>
RegisterFile<S>::RegisterFile(const size_t& size) : registers_(size, Register<S>()), size_(size) {}

template <size_t S>
Register<S>& RegisterFile<S>::get(const size_t& index) {
    return registers_.at(index);
}


#endif
