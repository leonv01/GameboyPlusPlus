#include "CPU.h"

CPU::CPU() {
    reg = std::make_unique<Register>();
    memory = std::make_unique<Memory>(&reg->SP);
    initCPU();
    memory->initMemory();
}

CPU::~CPU() = default;

void CPU::initCPU() {
    memory->initMemory();       // initializes main memory
    reg->init();                // initializes registers and PC/SP
    interruptMaster = false;    // disables interrupt master

}

uint8_t CPU::fetchOpCode() {
    return memory->readByte(reg->PC++);
}

void CPU::printStatus() {
    std::cout << reg->toString() << std::endl;
}

void CPU::updateTimer(int currentCycle) {
    uint8_t tac = memory->readByte(TAC);
    /*
     * If Bit 2 is set, timer is enabled
     */
    if(tac & 0x04){
        uint8_t value = memory->readByte(TIMA);
        timerCounter -= currentCycle;

        if(timerCounter <= 0) {
            switch (tac & 0x03) {
                case 0x00:
                    timerFrequency = 1024;
                    break;
                case 0x01:
                    timerFrequency = 16;
                    break;
                case 0x02:
                    timerFrequency = 64;
                    break;
                case 0x03:
                    timerFrequency = 256;
                    break;
            }

            if(value == 255){
                uint8_t tma = memory->readByte(TMA);
                memory->writeByte(TIMA, tma);
                requestInterrupt(IF_TIMER);
            }
            else{
                memory->writeByte(TIMA, value + 1);
            }
        }
    }
}

void CPU::updateDivider(int currentCycles) {
    dividerCounter += currentCycles;
    if(dividerCounter > 0xFF){
        dividerCounter = 0;
        uint8_t divValue = memory->readByte(DIV);
        memory->writeByte(DIV, divValue + 1);
    }
}

/*
 * Interrupt Request is written into Interrupt Flag address in Main Memory
 */
void CPU::requestInterrupt(uint8_t value) {
    uint8_t interrupt = memory->readByte(IF);
    interrupt |= value;
    memory->writeByte(IF, interrupt);
}

/*
 * Interrupt Execution is handled at Interrupt Enable address in Main Memory
 */
void CPU::handleInterrupt() {
    if(interruptMaster){
        uint8_t interrupt = memory->readByte(IF);

        // VBANK has the highest priority
        if(interrupt & IF_VBLANK){
            interruptServiceRoutine(IF_VBLANK);
            interrupt &= ~IF_VBLANK;
        }
        if(interrupt & IF_LCDSTAT){
            interruptServiceRoutine(IF_LCDSTAT);
            interrupt &= ~IF_LCDSTAT;
        }
        if(interrupt & IF_TIMER){
            interruptServiceRoutine(IF_TIMER);
            interrupt &= ~IF_TIMER;
        }
        if(interrupt & IF_SERIAL){
            interruptServiceRoutine(IF_SERIAL);
            interrupt &= ~IF_SERIAL;
        }
        if(interrupt & IF_JOYPAD){
            interruptServiceRoutine(IF_JOYPAD);
            interrupt &= ~IF_JOYPAD;
        }
    }
}

void CPU::interruptServiceRoutine(uint8_t value) {
    interruptMaster = false;
    memory->pushWord(reg->PC);

    switch(value){
        case IF_VBLANK:     reg->PC = 0x40; break;
        case IF_LCDSTAT:    reg->PC = 0x48; break;
        case IF_TIMER:      reg->PC = 0x50; break;
        case IF_SERIAL:     reg->PC = 0x58; break;
        case IF_JOYPAD:     reg->PC = 0x60; break;
        default:                            break;
    }
}
