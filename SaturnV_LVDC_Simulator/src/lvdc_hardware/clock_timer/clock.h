#pragma once
#include <cstdint>
#include <atomic>

// LVDC Master Clock
// Frequency: 2.048 MHz
// Maintains the global cycle count for the simulation.

class Clock {
public:
    Clock() : current_tick(0) {}

    // Increment the clock by one cycle.
    void tick() {
        current_tick++;
    }

    // Get the current cycle count.
    uint64_t get_current_tick() const {
        return current_tick;
    }

    // Reset clock (system reset).
    void reset() {
        current_tick = 0;
    }

    // Constants
    static constexpr double FREQUENCY_HZ = 2048000.0;

private:
    std::atomic<uint64_t> current_tick;
};
