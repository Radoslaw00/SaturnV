#pragma once
#include <string>
#include <cstdint>

// Generic Sensor Class
// Stores a value (simulating the physical sensor reading).
// Can be read by LVDC via Memory Mapped IO.

class Sensor {
public:
    Sensor(std::string name) : name(std::move(name)), value(0) {}

    // Called by Logic/Environment/User to update physical state
    void set_physical_value(uint32_t val) {
        value = val;
    }

    // Called by LVDC logic (read)
    uint32_t read() const {
        return value;
    }

    // Valid if sensor is writable (e.g. configuration)
    void write(uint32_t val) {
        value = val;
    }

    std::string get_name() const { return name; }

private:
    std::string name;
    uint32_t value; // Raw digital value (16-bit or 26-bit)
};

struct Peripherals {
    Sensor gimbal_pitch{"Gimbal Pitch"};
    Sensor gimbal_yaw{"Gimbal Yaw"};
    Sensor gimbal_roll{"Gimbal Roll"};
    Sensor accel_x{"Accel X"};
    Sensor accel_y{"Accel Y"};
    Sensor accel_z{"Accel Z"};
};
