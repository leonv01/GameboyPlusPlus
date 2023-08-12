//
// Created by leon on 8/6/23.
//

#include "Emulator.h"

Emulator::Emulator() {
    cpu = new CPU();
    ppu = new PPU();
    timer = nullptr;
}

Emulator::~Emulator() {
    delete timer;
    delete ppu;
    delete cpu;

}

void Emulator::start() {
    timer = new clock_t;

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