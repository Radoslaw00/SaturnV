#pragma once
#include <cstdint>
#include <string>

// LVDC Register
// Represents a 26-bit hardware register.
// Values are stored in 32-bit integers but masked to 26 bits (0x3FFFFFF) on specific operations.

class Register {
public:
    Register(std::string name) : name(std::move(name)), value(0) {}

    // Write a value to the register. 
    // In strict simulation, this might have a delay, but for the primitive class, it's instant.
    void write(uint32_t new_value) {
        value = new_value & MASK_26BIT;
    }

    // Read the current value.
    uint32_t read() const {
        return value;
    }

    // Direct access for arithmetic operations (bypassing some checks if needed, but usually we use write).
    // Returns true if overflow occurred (basic example, refinement needed for specific flags).
    bool add(uint32_t operand) {
        uint64_t result = (uint64_t)value + operand;
        value = result & MASK_26BIT;
        return (result > MASK_26BIT); // Carry
    }

    std::string get_name() const { return name; }

    static constexpr uint32_t MASK_26BIT = 0x3FFFFFF;

private:
    std::string name;
    uint32_t value;
};
