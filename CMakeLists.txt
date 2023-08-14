cmake_minimum_required(VERSION 3.24.2)
project(GameboyPlus)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(GameboyPlus System/main.cpp System/Core/CPU/CPU.cpp System/Core/CPU/CPU.h System/Core/Memory/Memory.cpp System/Core/Memory/Memory.h System/Core/CPU/OpCode.cpp System/Core/CPU/Instructions.cpp System/Core/CPU/Register.cpp System/Core/CPU/Register.h System/Core/Cartridge.cpp System/Core/Cartridge.h System/Emulator/Emulator.cpp System/Emulator/Emulator.h System/Core/CPU/Interrupts.cpp System/Core/PPU/PPU.cpp System/Core/PPU/PPU.h System/Core/Memory/MBC.cpp System/Core/Memory/MBC.h
        System/Core/Joypad/Joypad.cpp
        System/Core/Joypad/Joypad.h)

target_link_libraries(GameboyPlus ${SDL2_LIBRARIES})