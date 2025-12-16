# UI and Telemetry

## Requirements
- CLI for headless operation.
- C# GUI for visualization.
- Telemetry stream.

## Protocol
Implemented using **Standard Output (Stdout) Piping**.
- The C++ Simulator prints telemetry strings (`TLM:Tick|RegA|RegQ|...`) to stdout.
- The C# Dashboard launches the C++ process, redirects stdout, and parses these lines in real-time.
- This ensures low latency and simple inter-process communication without complex networking stack.
