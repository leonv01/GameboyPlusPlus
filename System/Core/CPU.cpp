//
// Created by leonv on 31/07/2023.
//

#include "CPU.h"

CPU::CPU() {
    init();
}

CPU::~CPU() = default;

void CPU::init() {
    reg = std::make_unique<Register>();
    memory = std::make_unique<Memory>(&reg->SP);
    interrupt = std::make_unique<Interrupt>();

    reg->init();
    memory->init();
}

void CPU::handleInterrupts() {
    uint8_t enabledInterrupts = interrupt->enabled_interrupts();

    if (enabledInterrupts > 0) {
        if (enabledInterrupts & interrupt->IF_VBLANK) {
            //push program counter on stack for context switch
            reg->PC -= 2;
            memory->pushWord(reg->PC);
            reg->PC = 0x40;
            vBlankInterruptHandler();
        }
        else if (enabledInterrupts & interrupt->IF_LCDSTAT) {
            reg->PC -= 2;
            memory->pushWord(reg->PC);
            reg->PC = 0x48;
            lcdStatInterruptHandler();
        }
        else if (enabledInterrupts & interrupt->IF_TIMER) {
            reg->PC -= 2;
            memory->pushWord(reg->PC);
            reg->PC = 0x50;
            timerInterruptHandler();

        }
        else if (enabledInterrupts & interrupt->IF_SERIAL) {
            reg->PC -= 2;
            memory->pushWord(reg->PC);
            reg->PC = 0x58;
            serialInterruptHandler();
        }
        else if (enabledInterrupts & interrupt->IF_JOYPAD) {
            reg->PC -= 2;
            memory->pushWord(reg->PC);
            reg->PC = 0x60;
            joypadInterruptHandler();
        }
    }
}

void CPU::vBlankInterruptHandler() {
    interrupt->disableInterrupt(interrupt->IF_VBLANK);
}
void CPU::lcdStatInterruptHandler() {
    interrupt->disableInterrupt(interrupt->IF_LCDSTAT);
}
void CPU::timerInterruptHandler() {
    interrupt->disableInterrupt(interrupt->IF_TIMER);
}
void CPU::serialInterruptHandler() {
    interrupt->disableInterrupt(interrupt->IF_SERIAL);
}
void CPU::joypadInterruptHandler() {
    interrupt->disableInterrupt(interrupt->IF_JOYPAD);
}

void CPU::triggerVBlankInterrupt() {
    interrupt->enableInterrupt(interrupt->IF_VBLANK);
}
void CPU::triggerLcdStatInterrupt() {
    interrupt->enableInterrupt(interrupt->IF_LCDSTAT);
}
void CPU::triggerTimerInterrupt() {
    interrupt->enableInterrupt(interrupt->IF_TIMER);
}
void CPU::triggerSerialInterrupt() {
    interrupt->enableInterrupt(interrupt->IF_SERIAL);
}
void CPU::triggerJoypadInterrupt() {
    interrupt->enableInterrupt(interrupt->IF_JOYPAD);
}


void CPU::writeByte(uint16_t address, uint8_t value) {
    memory->writeByte(address, value);
}
uint8_t CPU::readByte(uint16_t address){
    return memory->readByte(address);
}
void CPU::writeWord(uint16_t address, uint16_t value) {
    memory->writeWord(address, value);
}
uint16_t CPU::readWord(uint16_t address) {
    return memory->readWord(address);
}

void CPU::fetchOpCode() {
    uint8_t opcode = memory->readByte(reg->PC);
    reg->PC++;
    parseOpCode(opcode);
}

void CPU::printStatus() {
    std::cout << reg->toString() << std::endl;
}