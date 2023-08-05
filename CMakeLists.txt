cmake_minimum_required(VERSION 3.24.2)
project(GameboyPlus)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(GameboyPlus System/main.cpp System/Core/CPU.cpp System/Core/CPU.h System/Core/Memory.cpp System/Core/Memory.h System/Core/OpCode.cpp System/Emulator/Emulator.cpp System/Emulator/Emulator.h System/Core/Instructions.cpp System/Core/Register.cpp System/Core/Register.h System/Core/Cartridge.cpp System/Core/Cartridge.h System/Core/PPU.cpp System/Core/PPU.h)

target_link_libraries(GameboyPlus ${SDL2_LIBRARIES})