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

void CPU::fetchOpCode() {
    uint8_t opcode = memory->readByte(reg->PC);
    std::cout << std::hex << static_cast<int>(opcode) << std::endl;
    reg->PC++;
    parseOpCode(opcode);
}

void CPU::printStatus() {
    std::cout << reg->toString() << std::endl;
}