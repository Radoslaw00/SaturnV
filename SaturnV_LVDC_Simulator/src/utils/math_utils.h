#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <stdint.h>

// fast x86 assembly addition with overflow check
int32_t asm_add(int32_t a, int32_t b);

#endif
