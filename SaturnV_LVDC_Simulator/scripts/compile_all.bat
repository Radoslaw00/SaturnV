@echo off
echo Compiling Saturn V LVDC Simulator (C/ASM)...

if not exist build mkdir build

gcc -std=c11 -Isrc src\main.c src\guidance\guidance.c src\navigation\navigation.c src\control_loops\control_loops.c src\flight_plan\flight_plan.c src\telemetry\telemetry.c src\utils\math_utils.c src\utils\io_utils.c -o build\LVDC_Simulator.exe

if %ERRORLEVEL% EQU 0 (
    echo Compilation Successful.
    echo Running Simulation...
    build\LVDC_Simulator.exe
) else (
    echo Compilation Failed.
)
