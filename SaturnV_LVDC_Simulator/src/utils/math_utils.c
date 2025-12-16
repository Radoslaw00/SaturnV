#include "math_utils.h"

int32_t asm_add(int32_t a, int32_t b) {
    int32_t res;
    // Basic x86 inline assembly example
    // AT&T syntax (default for GCC)
    __asm__ (
        "addl %2, %0;"
        : "=r" (res)     // output
        : "0" (a), "r" (b) // inputs: 0 (same as output for accumulator), r (register)
    );
    return res;
}
