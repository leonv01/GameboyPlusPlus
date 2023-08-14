//
// Created by leon on 8/6/23.
//

#include "Emulator.h"

Emulator::Emulator() {
    cpu = std::make_unique<CPU>();
    ppu = std::make_unique<PPU>();;
    timer = nullptr;
}

Emulator::~Emulator() = default;

void Emulator::start() {

    while(true){
        int currentCycle{};
        cpu->handleInterrupt();

        while(currentCycle < cyclesPerFrame){
            uint8_t opcode = cpu->fetchOpCode();
            std::cout << std::hex << static_cast<int>(opcode) << std::endl;
            cpu->parseOpCode(opcode);
            currentCycle += cpu->cycle;

            ppu->updatePPU();
            cpu->updateTimer(currentCycle);



            cpu->cycle = 0;
        }
    }
}