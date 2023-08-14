//
// Created by leon on 8/6/23.
//

#include "Emulator.h"

#include <utility>
#include <thread>

Emulator::Emulator() {
    cpu = std::make_unique<CPU>();
    ppu = std::make_unique<PPU>();

}

Emulator::~Emulator() = default;

void Emulator::start() {
    int targetFramDuration = 16;
    while(true){
        auto start = std::chrono::high_resolution_clock::now();
        int currentCycle{};
        cpu->handleInterrupt();

        while(currentCycle < cyclesPerFrame){
            uint8_t opcode = cpu->fetchOpCode();
         //   std::cout << std::hex << static_cast<int>(opcode) << std::endl;
            cpu->parseOpCode(opcode);
            currentCycle += cpu->cycle;

            ppu->updatePPU();
            cpu->updateTimer(currentCycle);



            cpu->cycle = 0;
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        int remainingTime = targetFramDuration - duration.count();

        if(remainingTime > 0){
            std::this_thread::sleep_for(std::chrono::milliseconds (remainingTime));
        }
    }
}

void Emulator::loadROM(std::string path) {
    cpu->memory->loadROM(std::move(path));
}
