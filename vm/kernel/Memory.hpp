#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <exception>
#include <string>
#include "Virtual.hpp"

/**
 * @class Memory
 * @brief A class that simulates a block of memory, allowing read and write operations.
 */
class Memory final {
 public:
    /**
     * @brief Constructs a Memory object with the specified size.
     * @param size The size of the memory block to be allocated.
     */
    explicit Memory(const size_t& size);

    /**
     * @brief Destructor for the Memory class, releases allocated memory.
     */
    ~Memory();

    /**
     * @brief Reads a byte from the specified address in memory.
     * @param address The address from which to read the byte.
     * @return The byte read from the specified address.
     */
    [[nodiscard]] byte read(const address_t& address) const;

    /**
     * @brief Writes a byte to the specified address in memory.
     * @param address The address to which the byte will be written.
     * @param value The byte value to be written to the specified address.
     */
    void write(const address_t& address, const byte& value) const;

    /**
     * @brief Returns the size of the memory block.
     * @return The size of the memory block in bytes.
     */
    [[nodiscard]] size_t size() const;

    /**
     * @class InvalidAddress
     * @brief An exception class thrown when users try to access to the memory with an invalid
     * address.
     */
    class InvalidAddress final : public std::exception {
     public:
        /**
         * @brief Constructs an InvalidAddress object.
         * @param address The address the user tries to access to.
         * @param size The size of the memory block.
         */
        InvalidAddress(const address_t& address, const size_t& size);

        /**
         * @brief Returns the exception message.
         * @return the exception message.
         */
        [[nodiscard]] const char* what() const noexcept override;

     private:
        /**
         * @brief The address the user tries to access to.
         */
        address_t address_;

        /**
         * @brief The size of the memory block.
         */
        size_t size_;

        /**
         * @brief The exception message.
         */
        std::string message;
    };

 private:
    /**
     * @brief Pointer to the allocated memory block.
     */
    byte* data_;

    /**
     * @brief The size of the allocated memory block.
     */
    size_t size_{};
};

#endif
