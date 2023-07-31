//
// Created by leonv on 31/07/2023.
//

#include "Emulator.h"

Emulator::Emulator() {
    cyclesRemaining = CYCLES_PER_FRAME;
    cpu = new CPU();
}

Emulator::~Emulator() {
    delete cpu;
}

void Emulator::start() {
    cpu->init();

    while (1) {
        int8_t currentCycle = 0;

        uint8_t cycle;

        while (currentCycle < CYCLES_PER_FRAME) {
            std::cout << static_cast<int>(currentCycle) << std::endl;
            cpu->fetchOpCode(cycle);
            currentCycle += cycle;
            cycle = 0;
            cpu->handleInterrupts();
        }
    }
}

void Emulator::debug() {
    uint8_t cycle = 0;
    //cpu->fetchOpCode(cycle);

    cyclesRemaining -= cycle;

    uint16_t address = 0x0100;
    uint16_t data = 0xC005;
    uint16_t readData = 0xC010;

    // Write data into accumulator
    cpu->writeByte(address++, 0xFA);
    cpu->writeByte(data, static_cast<uint8_t>(210));
    cpu->writeWord(address, data);
    address += 2;

    // Add data with accumulator
    cpu->writeByte(address++, 0xDE);
    cpu->writeByte(address++, static_cast<uint8_t>(110));

    // Store result in memory address 0x0001
    cpu->writeByte(address++, 0xEA);
    cpu->writeWord(address, readData);
    address += 2;

    std::cout << "Cycle: " << static_cast<int>(cycle) << "\t Remaining Cycles: " << static_cast<int>(cyclesRemaining) << std::endl;

    // Execute instructions
    cpu->fetchOpCode(cycle);
    cpu->printStatus();

    cyclesRemaining -= cycle;
    std::cout << "Cycle: " << static_cast<int>(cycle) << "\t Remaining Cycles: " << static_cast<int>(cyclesRemaining) << std::endl;

    cpu->fetchOpCode(cycle);
    cpu->printStatus();

    cyclesRemaining -= cycle;
    std::cout << "Cycle: " << static_cast<int>(cycle) << "\t Remaining Cycles: " << static_cast<int>(cyclesRemaining) << std::endl;

    cpu->fetchOpCode(cycle);
    cpu->printStatus();

    cyclesRemaining -= cycle;
    std::cout << "Cycle: " << static_cast<int>(cycle) << "\t Remaining Cycles: " << static_cast<int>(cyclesRemaining) << std::endl;

    int value = static_cast<int>(cpu->readByte(readData));

    std::cout << "Result: " << value << std::endl;
}

void Emulator::init() {

}

void Emulator::restart() {
}

void Emulator::poweroff() {
}

