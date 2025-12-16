@echo off
echo Compiling Saturn V LVDC Simulator...

if not exist build mkdir build

g++ -std=c++17 -Isrc src\main.cpp -o build\LVDC_Simulator.exe

if %ERRORLEVEL% EQU 0 (
    echo Compilation Successful.
    echo Running Simulation...
    build\LVDC_Simulator.exe
) else (
    echo Compilation Failed.
)
