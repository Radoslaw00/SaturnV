#pragma once
#include <vector>
#include <queue>
#include <iostream>

// LVDC Interrupt Controller
// Manages interrupt requests and priorities.

class InterruptController {
public:
    enum InterruptType {
        TIMER_INT = 1,
        SENSOR_INT = 2,
        UI_INT = 3
    };

    void request_interrupt(InterruptType type) {
        // Simple priority: Lower ID = Higher Priority? Or just generic queue.
        // Let's assume generic for simulation.
        pending_interrupts.push(type);
    }

    bool has_interrupt() const {
        return !pending_interrupts.empty();
    }

    InterruptType get_next_interrupt() {
        if (pending_interrupts.empty()) return (InterruptType)0;
        InterruptType t = pending_interrupts.front();
        pending_interrupts.pop();
        return t;
    }

private:
    std::queue<InterruptType> pending_interrupts;
};
