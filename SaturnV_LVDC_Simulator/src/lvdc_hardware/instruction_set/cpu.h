#pragma once
#include <iostream>
#include <iomanip>
#include "../memory/memory.h"
#include "../registers/register.h"
#include "../clock_timer/clock.h"

// LVDC CPU / Instruction Set Architecture
// Handles Fetch-Decode-Execute cycle.

class Cpu {
public:
    Cpu(Memory& mem, Clock& clk, Register& acc, Register& instr_reg, Register& instr_addr)
        : memory(mem), clock(clk), A(acc), IR(instr_reg), IA(instr_addr) {}

    // Execute one instruction cycle.
    // Returns true if running, false if HALT encountered.
    bool step() {
        // 1. FETCH
        // Read instruction from memory at address IA
        uint16_t pc = (uint16_t)IA.read();
        uint32_t instruction = memory.read(pc);
        IR.write(instruction);

        // Advance PC (IA)
        IA.write(pc + 1);

        // Simulate Fetch Cycles
        clock.tick(); // Minimal cost

        // 2. DECODE
        // Opcode: Top 5 bits (25-21)
        // Operand: Bottom 21 bits (20-0)
        uint32_t opcode = (instruction >> 21) & 0x1F; 
        uint32_t operand = instruction & 0x1FFFFF; // 21-bit address/value

        // 3. EXECUTE
        // Simulate execution cycles. 
        // Note: Real LVDC opcodes are different, these are placeholders for the simulation architecture.
        switch (opcode) {
            case 0x00: // NOP
                break;
            case 0x01: // LOAD Address -> A
                // Memory Access Latency
                clock.tick();
                A.write(memory.read((uint16_t)operand));
                break;
            case 0x02: // STORE A -> Address
                clock.tick();
                memory.write((uint16_t)operand, A.read());
                break;
            case 0x03: // ADD Address -> A
                clock.tick();
                {
                    uint32_t val = memory.read((uint16_t)operand);
                    A.add(val); 
                }
                break;
            case 0x04: // SUB Address -> A
                clock.tick();
                {
                    uint32_t val = memory.read((uint16_t)operand);
                    // 2's complement negation simplified
                    // Actually Register should have 'sub' method
                     // A.value = (A.value - val) & Mask
                    uint32_t current = A.read();
                    A.write(current - val); 
                }
                break;
            case 0x05: // MUL Address -> A (Simplified)
                clock.tick(); clock.tick(); // Multi-cycle
                {
                    uint64_t val = memory.read((uint16_t)operand);
                    uint64_t res = (uint64_t)A.read() * val;
                    // Store Upper in A, Lower in Q? Or just A.
                    // Let's store truncated in A for now.
                    A.write((uint32_t)res);
                }
                break;
            case 0x06: // DIV Address -> A
                clock.tick(); clock.tick();
                {
                    uint32_t val = memory.read((uint16_t)operand);
                    if(val != 0) A.write(A.read() / val);
                }
                break;
            case 0x10: // AND Address -> A
                clock.tick();
                A.write(A.read() & memory.read((uint16_t)operand));
                break;
            case 0x11: // OR Address -> A
                clock.tick();
                A.write(A.read() | memory.read((uint16_t)operand));
                break;
            case 0x15: // JUMP Address
                clock.tick();
                IA.write(operand);
                break;
            case 0x16: // JAM (Jump if A Minus)
                clock.tick();
                // Check bit 25 (Sign bit in 26-bit 2's complement usually, or just if > Max/2)
                // Assuming simple signed interpretation:
                if ((A.read() & 0x2000000) != 0) { // Bit 25 set -> Negative
                     IA.write(operand);
                }
                break;
            case 0x1F: // HALT
                return false;
            default:
                std::cout << "Unknown Opcode: " << std::hex << opcode << std::dec << " at PC=" << pc << std::endl;
                break;
        }

        // More cycle accounting
        clock.tick();
        return true;
    }

private:
    Memory& memory;
    Clock& clock;
    Register& A;  // Accumulator
    Register& IR; // Instruction Register
    Register& IA; // Instruction Address (Program Counter)
};
