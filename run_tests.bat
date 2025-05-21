@echo off
echo === Compiling VehicleTest.cpp ===
g++ -std=c++17 -Iincludes -Isrc test/VehicleTest.cpp src/Vehicle.cpp src/Position.cpp src/catch_amalgamated.cpp -o VehicleTest.exe

if %errorlevel% neq 0 (
    echo === ? Compilation failed ===
    pause
    exit /b
)

echo === ? Compilation successful. Running tests... ===
.\VehicleTest.exe

echo === ? Done. Press any key to exit... ===
pause
