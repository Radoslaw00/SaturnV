# Architecture Design

## Overview
The simulation uses a tick-based architecture where the Master Clock drives all components.

## Components
- **CPU**: Handles instruction fetch/decode/execute.
- **Memory**: 32K words, magnetic core simulation.
- **IO**: Memory Mapped IO for sensors.
- **Bus**: Interconnects.

## Cycle Accuracy
The main loop will execute one "Major Cycle" or "Minor Cycle" step per tick.
2.048 MHz = 1 tick every ~488 ns.
Software simulation will likely run faster; we can throttle it or run as fast as possible for testing.
