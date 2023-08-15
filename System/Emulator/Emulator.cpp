//
// Created by leon on 8/6/23.
//

#include "Emulator.h"

#include <utility>
#include <thread>

Emulator::Emulator() {
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    cpu = std::make_unique<CPU>();
    ppu = std::make_unique<PPU>(window);

}

Emulator::~Emulator() = default;

void Emulator::start() {
    /*
     * Equation:    1000ms / 60 FPS ~= 16.67 ms
     * Sets the limit for the time per frame
     */
    int targetFrameDuration = 1000 / FPS;
    while (true) {
        auto start = std::chrono::high_resolution_clock::now();
        int currentCycle{};
        cpu->handleInterrupt();

        while (currentCycle < cyclesPerFrame) {
            uint8_t opcode = cpu->fetchOpCode();
            // std::cout << std::hex << static_cast<int>(opcode) << std::endl;
            cpu->parseOpCode(opcode);
            currentCycle += cpu->cycle;
            ppu->updatePPU();
            cpu->updateTimer(currentCycle);
            cpu->cycle = 0;
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        int remainingTime = targetFrameDuration - duration.count();

        if (remainingTime > 0) {
            /*
             * If time remains, the program sleeps for the time difference
             * e.g.: Target Frames = 16ms; Current Frame = 12ms
             * Remaining time = 16ms - 12ms = 4ms
             * The program thread would need to sleep for 4 ms to keep the time sync up
             */
            std::this_thread::sleep_for(std::chrono::milliseconds(remainingTime));
        }
    }
}

void Emulator::loadROM(std::string path) {
    cpu->memory->loadROM(std::move(path));
}
