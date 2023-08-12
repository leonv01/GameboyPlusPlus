#include "CPU.h"

CPU::CPU() {
    reg = std::make_unique<Register>();
    memory = std::make_unique<Memory>(&reg->SP);
    initCPU();
    //memory->initMemory();
}

CPU::~CPU() = default;

void CPU::initCPU() {
    reg = std::make_unique<Register>();
    //interrupt = std::make_unique<Interrupt>();
    memory->initMemory();
    reg->init();
}

uint8_t CPU::fetchOpCode() {
    return memory->readByte(reg->PC++);
}

void CPU::printStatus() {
    std::cout << reg->toString() << std::endl;
}

void CPU::handleInterrupt() {

}

void CPU::updateTimer(int currentCycle) {
    uint8_t tac = memory->readByte(0xFF07);
    /*
     * Check if Timer is enabled with Bit 2
     */
    if (tac & 0x04) {
        int freq{};
        /*
         * Determine clock frequency based on Bit 0 and 1
         */
        switch (tac & 0x3) {
            case 0x00:
                freq = 1024;
                break;
            case 0x01:
                freq = 16;
                break;
            case 0x02:
                freq = 64;
                break;
            case 0x03:
                freq = 256;
                break;
        }

        uint8_t timerEnabled = memory->readByte(0xFF07);
        if (timerEnabled & 0x2) {
            if (true) {
                uint8_t timerVal = memory->readByte(0xFF05);

                if (false) {
                    uint8_t temp = memory->readByte(0xFF06);
                    memory->writeByte(0xFF05, temp);
                } else {
                    memory->writeByte(0xFF05, timerVal + 1);
                }
            }
        }
    }

}

void CPU::updateDivider(int currentCycles) {

}
