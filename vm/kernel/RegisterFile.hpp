#ifndef REGISTERFILE_HPP
#define REGISTERFILE_HPP

#include <vector>
#include "Register.hpp"

/**
 * @class RegisterFile
 * @brief A class representing a register file containing multiple registers.
 */
class RegisterFile final {
 public:
    /**
     * @brief Constructs a RegisterFile object with the specified number of registers.
     * @param size The number of registers in the register file.
     * @param word_size The size of a word.
     */
    explicit RegisterFile(const size_t& size, const size_t& word_size);

    /**
     * @brief Gets a reference to the register at the specified index.
     * @param index The index of the register to retrieve.
     * @return A reference to the register at the specified index.
     * @throws std::out_of_range if the index is out of bounds.
     */
    [[nodiscard]] Register& get(const size_t& index);

 private:
    /**
     * @brief Vector containing the registers in the register file.
     */
    std::vector<Register> registers_;

    /**
     * @brief The number of registers in the register file.
     */
    size_t size_;

    /**
     * @brief The size of a word.
     */
    size_t word_size_;
};

#endif  // REGISTERFILE_HPP
