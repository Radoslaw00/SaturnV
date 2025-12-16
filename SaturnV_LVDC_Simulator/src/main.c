/*
 * Saturn V LVDC Simulator
 * Main Entry Point
 * 
 * Orchestrates the hardware simulation and software control loops.
 */

#include <stdio.h>
#include "control_loops/control_loops.h"
#include "telemetry/telemetry.h"

int main() {
    printf("Saturn V LVDC Simulator (C/ASM Edition) Starting...\n");

    // Initialize Subsystems
    telemetry_init();
    control_loops_init();

    // Main Simulation Loop
    // Cycle-accurate timing would be managed here or inside control_loops
    while (1) {
        control_loops_step();
        
        // Break condition for testing (e.g. key press or max ticks)
        // ...
    }

    return 0;
}
