#ifndef ATTITUDE_CONTROL_H
#define ATTITUDE_CONTROL_H

#include <stdint.h>

typedef struct {
    float roll;      // degrees
    float pitch;     // degrees
    float yaw;       // degrees
} Attitude;

typedef struct {
    float roll_rate;   // degrees/second
    float pitch_rate;  // degrees/second
    float yaw_rate;    // degrees/second
} AngularVelocity;

typedef struct {
    Attitude current_attitude;
    AngularVelocity angular_velocity;
    Attitude desired_attitude;
    float control_output[3];  // roll, pitch, yaw control commands
} AttitudeControlState;

// Initialize attitude control system
void attitude_control_init(void);

// Update attitude estimates from IMU data
void attitude_update(float ax, float ay, float az, float gx, float gy, float gz);

// Compute attitude control commands
void attitude_control_compute(void);

// Get current attitude state
AttitudeControlState* attitude_get_state(void);

// Set desired attitude target
void attitude_set_target(float desired_roll, float desired_pitch, float desired_yaw);

#endif // ATTITUDE_CONTROL_H
