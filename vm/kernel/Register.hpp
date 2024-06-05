#ifndef REGISTER_HPP
#define REGISTER_HPP

#include "Word.hpp"

/**
 * @class Register
 * @brief A class representing a register that can hold a word of memory.
 * @tparam S The size of the word in bytes.
 */
template <size_t S>
class Register final {
 public:
    /**
     * @brief Loads a Word into the register.
     * @param word The Word object to be loaded into the register.
     */
    void load(const Word<S>& word);

    /**
     * @brief Reads the Word from the register.
     * @return The Word stored in the register.
     */
    [[nodiscard]] Word<S> read() const;

 private:
    /**
     * @brief The word stored in the register.
     */
    Word<S> word_;
};

template <size_t S>
void Register<S>::load(const Word<S>& word) {
    word_ = word;
}

template <size_t S>
Word<S> Register<S>::read() const {
    return word_;
}

#endif  // REGISTER_HPP
