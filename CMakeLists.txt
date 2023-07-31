cmake_minimum_required(VERSION 3.25)
project(GameboyPlus)

set(CMAKE_CXX_STANDARD 20)

add_executable(GameboyPlus main.cpp CPU.cpp CPU.h Memory.cpp Memory.h OpCode.cpp Emulator.cpp Emulator.h Instructions.cpp)
