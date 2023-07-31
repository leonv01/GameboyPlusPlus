#include "Memory.h"
#include <iostream>

Memory::Memory(uint16_t* address) {
    SP = std::make_unique<uint16_t>(*address);
    memory = std::vector<uint8_t>(MEMORY_SIZE, 0);
}

Memory::~Memory() {

}

bool inline inRange(uint16_t address, uint16_t lowerBound, uint16_t upperBound)  {
    return address >= lowerBound && address <= upperBound;
}

uint8_t Memory::readByte(uint16_t address) const {
    if (inRange(address, romBankStart, romBankEnd)) {
        //TODO
    }
    else if (inRange(address, switchRomBankStart, switchRomBankEnd)) {
        //TODO
    }
    else if (inRange(address, VRAMstart, VRAMend)) {
        //TODO
    }
    else if (inRange(address, internalRAMstart, internalRAMend)) {

    }
    else if (inRange(address, spriteAttEnd, spriteAttEnd)) {
        //TODO
    }
    else if (inRange(address, inputOutputStart, inputOutputEnd)) {
        //TODO
    }
    else if (inRange(address, highRAMstart, highRAMend)) {
        //TODO
    }
    else if (address == interruptRegister) {
        //TODO
    }
    return memory[address];
}

void Memory::writeByte(uint16_t address, uint8_t value) {
    memory[address] = value;
}

uint16_t Memory::readWord(uint16_t address) const {
    uint8_t lowByte = memory[address];
    uint8_t highByte = memory[address + 1];
    return static_cast<uint16_t>((highByte << 8) | lowByte);
}

void Memory::writeWord(uint16_t address, uint16_t value){
    uint8_t lowByte = value & 0xFF;
    uint8_t highByte = value >> 8;
    memory[address] = lowByte;
    memory[address + 1] = highByte;
}

void Memory::loadROM(const uint8_t* romData, size_t romSize) {
    if (romData && romSize <= (MEMORY_SIZE - 0x8000)) {
        memcpy(&memory[0x0000], romData, romSize);
    }
}

uint8_t Memory::popByte() {
    (*SP)++;
    return readByte(*SP);
}
void Memory::pushByte(uint8_t value) {
    writeByte(*SP, value);
    (*SP)--;
}
uint16_t Memory::popWord() {
    (*SP) += 2;
    uint16_t value = readWord(*SP);
    return value;

}
void Memory::pushWord(uint16_t value) {
    writeWord((*SP), value);
    (*SP) -= 2;
}

uint8_t& Memory::operator[](uint16_t address) {
    return memory[address];
}
const uint8_t& Memory::operator[](uint16_t address) const {
    return memory[address];
}