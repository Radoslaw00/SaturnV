#pragma once
#include <iostream>
#include <iomanip>
#include <cstdint>

class TelemetrySender {
public:
    void send_update(uint64_t tick, uint32_t reg_a, uint32_t reg_ia, uint32_t reg_q) {
        // Simple structured output for parsing
        // T:<tick>|A:<val>|Q:<val>|IA:<val>
        std::cout << "TLM:" 
                  << tick << "|" 
                  << reg_a << "|" 
                  << reg_q << "|" 
                  << reg_ia << std::endl;
    }
};
