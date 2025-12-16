#include "lvdc_hardware/clock_timer/clock.h"
#include "lvdc_hardware/registers/register.h"
#include "lvdc_hardware/memory/memory.h"
#include "lvdc_hardware/instruction_set/cpu.h"
#include "lvdc_hardware/peripherals/sensors.h"
#include "lvdc_hardware/interrupts/interrupt_controller.h"
#include "ui/telemetry_sender.h"

int main() {
    std::cout << "Saturn V LVDC Simulator Starting..." << std::endl;

    // Initialize Hardware
    Clock master_clock;
    Memory main_memory(master_clock);
    Peripherals real_world_sensors;
    InterruptController int_controller;

    main_memory.attach_peripherals(&real_world_sensors);
    
    Register reg_A("Accumulator");
    Register reg_Q("Instruction");
    Register reg_IA("InstructionAddress"); // PC
    
    Cpu cpu(main_memory, master_clock, reg_A, reg_Q, reg_IA);

    // --- Test Peripherals (MMIO) ---
    // Simulate valid sensor data from environment
    real_world_sensors.gimbal_pitch.set_physical_value(55);
    
    // Read from LVDC Memory map (0x7F00 = Gimbal Pitch)
    uint32_t pitch_read = main_memory.read(0x7F00);
    std::cout << "MMIO Read Gimbal Pitch (Address 32512): " << pitch_read;
    if (pitch_read == 55) std::cout << " [PASS]" << std::endl;
    else std::cout << " [FAIL]" << std::endl;

    // --- Test Interrupts ---
    int_controller.request_interrupt(InterruptController::TIMER_INT);
    if (int_controller.has_interrupt()) {
         std::cout << "Interrupt Requested: [PASS]" << std::endl;
    }

    // --- Test CPU Loop ---
    // Create a simple program
    // Opcode map: 01=LOAD, 02=STORE, 03=ADD, 1F=HALT
    // Format: (Opcode << 21) | Operand
    
    // Address 100: Data 10
    // Address 101: Data 20
    main_memory.write(100, 10);
    main_memory.write(101, 20);

    // Program at Address 0
    // 0: LOAD 100	(A = 10)
    main_memory.write(0, (0x01 << 21) | 100);
    // 1: ADD 101	(A = 10 + 20 = 30)
    main_memory.write(1, (0x03 << 21) | 101);
    // 2: STORE 102	(Mem[102] = 30)
    main_memory.write(2, (0x02 << 21) | 102);
    // 3: HALT
    main_memory.write(3, (0x1F << 21) | 0);

    TelemetrySender telemetry;
    std::cout << "Running CPU Simulation..." << std::endl;
    int safety_break = 0;
    while(cpu.step() && safety_break++ < 1000) {
        telemetry.send_update(master_clock.get_current_tick(), reg_A.read(), reg_IA.read(), reg_Q.read());
    }

    std::cout << "CPU Halted." << std::endl;
    std::cout << "Final Clock: " << master_clock.get_current_tick() << std::endl;
    std::cout << "Register A: " << reg_A.read() << std::endl;
    std::cout << "Memory[102]: " << main_memory.read(102) << std::endl;

    if (main_memory.read(102) == 30) {
        std::cout << "Integration Test: [PASS]" << std::endl;
    } else {
        std::cout << "Integration Test: [FAIL]" << std::endl;
    }

    return 0;
}
