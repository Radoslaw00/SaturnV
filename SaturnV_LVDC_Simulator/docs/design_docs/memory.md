# Memory Design

## Specifications
- 32K words (approx 4K x 8 pages or contiguous).
- Random Access.
- Cycle time: ~? microseconds.

## Interface
`read(address)` -> returns value after latency.
`write(address, value)` -> stores value after latency.
