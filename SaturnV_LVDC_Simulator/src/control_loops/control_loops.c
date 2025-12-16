#include "control_loops.h"
#include "../guidance/guidance.h"
#include "../navigation/navigation.h"
#include "../telemetry/telemetry.h"

void control_loops_init() {
    guidance_init();
    navigation_init();
}

void control_loops_step() {
    // 1. Navigation (Where are we?)
    navigation_step();
    
    // 2. Guidance (Where do we want to go?)
    guidance_step();
    
    // 3. Telemetry
    telemetry_update();
}
