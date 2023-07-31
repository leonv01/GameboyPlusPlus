cmake_minimum_required(VERSION 3.25)
project(GameboyPlus)

set(CMAKE_CXX_STANDARD 20)

add_executable(GameboyPlus System/main.cpp System/Core/CPU.cpp System/Core/CPU.h System/Core/Memory.cpp System/Core/Memory.h System/Core/OpCode.cpp System/Emulator/Emulator.cpp System/Emulator/Emulator.h System/Core/Instructions.cpp)
