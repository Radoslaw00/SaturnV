#pragma once
#include <vector>
#include <cstdint>
#include <stdexcept>
#include "../clock_timer/clock.h"
#include "../peripherals/sensors.h"

// LVDC Main Memory
// Size: 32K words (26-bit).
// Simulates read/write latency relative to the master clock.

class Memory {
public:
    Memory(Clock& system_clock) : clock(system_clock), data(SIZE_WORDS, 0) {}

    void attach_peripherals(Peripherals* p) {
        peripherals = p;
    }

    // Read a word from memory or peripheral.
    uint32_t read(uint16_t address) {
        // MMIO Range: 0x7F00 - 0x7F05
        if (address >= 0x7F00 && peripherals != nullptr) {
            switch(address) {
                case 0x7F00: return peripherals->gimbal_pitch.read();
                case 0x7F01: return peripherals->gimbal_yaw.read();
                case 0x7F02: return peripherals->gimbal_roll.read();
                case 0x7F03: return peripherals->accel_x.read();
                case 0x7F04: return peripherals->accel_y.read();
                case 0x7F05: return peripherals->accel_z.read();
                default: return 0;
            }
        }
        if (address >= SIZE_WORDS) {
            return 0; 
        }
        return data[address];
    }

    // Write a word to memory or peripheral.
    void write(uint16_t address, uint32_t value) {
        // MMIO Range
        if (address >= 0x7F00 && peripherals != nullptr) {
             // Sensors might be read-only or writable for config. 
             // Allowing write for now.
             switch(address) {
                case 0x7F00: peripherals->gimbal_pitch.write(value); break;
                // ... others ...
             }
             return;
        }

        if (address < SIZE_WORDS) {
            data[address] = value & 0x3FFFFFF;
        }
    }

    // Reset all memory to 0.
    void reset() {
        std::fill(data.begin(), data.end(), 0);
    }

    static constexpr size_t SIZE_WORDS = 32768; // 32K

private:
    Clock& clock;
    std::vector<uint32_t> data;
    Peripherals* peripherals = nullptr;
};
