# Registers Design

## Specifications
- Word size: 26 bits (25 data + 1 sign/parity).
- Accumulator (A): 26-bit.
- Product-Quotient (Q): 26-bit.
- Instruction Address (IA): 13-bit? (Address space).
- Memory Address Register (MAR).
- Memory Buffer Register (MBR).

## Implementation
C++ class `Register` with `uint32_t` storage and `value & 0x3FFFFFF` masking.
