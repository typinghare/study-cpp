#ifndef REGISTER_HPP
#define REGISTER_HPP

#include <exception>
#include <string>
#include "Word.hpp"

/**
 * @class Register
 * @brief A class that simulates a CPU register with a fixed length.
 */
class Register final {
    static constexpr size_t DEFAULT_SIZE = 16;

 public:
    /**
     * @brief Constructs a Register object with the specified length.
     * @param size The size of the register.
     */
    explicit Register(const size_t& size);

    /**
     * @brief Loads a Word into the register.
     * @param word The Word object to be loaded into the register.
     * @throws LoadException if the size of the word does not match the register size.
     */
    void load(const Word& word);

    /**
     * @brief Reads the Word from the register.
     * @return The Word stored in the register.
     */
    [[nodiscard]] Word read() const;

    /**
     * @class LoadException
     * @brief An exception class thrown when the size of the word to load is not equal to the size
     * of the register.
     */
    class LoadException final : public std::exception {
     public:
        /**
         * @brief Constructs a LoadException with the given sizes.
         * @param word_size The size of the word to be loaded.
         * @param register_size The size of the register.
         */
        LoadException(const size_t& word_size, const size_t& register_size);

        /**
         * @brief Returns the exception message.
         * @return The exception message.
         */
        [[nodiscard]] const char* what() const noexcept override;

     private:
        /**
         * @brief The size of the word to be loaded.
         */
        size_t word_size_;

        /**
         * @brief The size of the register.
         */
        size_t register_size_;

        /**
         * @brief The exception message.
         */
        std::string message_;
    };

 private:
    /**
     * @brief The word stored in the register.
     */
    Word word_;

    /**
     * @brief The size of the register.
     */
    size_t size_;
};

#endif  // REGISTER_HPP
