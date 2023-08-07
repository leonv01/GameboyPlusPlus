//
// Created by leon on 8/7/23.
//

#include "MBC.h"

MBC::MBC(uint8_t* rom){ this->rom = rom;}
MBC::MBC(uint8_t *rom, uint8_t *ram, int romBanks, int ramBanks) {
    this->rom = rom;
    this->ram = ram;
    this->ramBanks = ramBanks;
    this->romBanks = romBanks;
}

uint8_t MBC0::readByte(uint16_t address){
    return rom[address];
}
uint16_t MBC0::readWord(uint16_t address) {
    uint8_t lowByte = rom[address];
    uint8_t highByte = rom[address + 1];
    return static_cast<uint16_t>((highByte << 8) | lowByte);
}

uint8_t MBC1::readByte(uint16_t address) {
    //TODO
}

void MBC1::writeByte(uint16_t address, uint8_t value) {
    //TODO
}


MBC::~MBC() {
    delete rom;
    delete ram;
}

uint8_t MBC2::readByte(uint16_t address) {
    return MBC1::readByte(address);
}

void MBC2::writeByte(uint16_t address, uint8_t value) {
    MBC1::writeByte(address, value);
}

uint8_t MBC3::readByte(uint16_t address) {
    return MBC1::readByte(address);
}

void MBC3::writeByte(uint16_t address, uint8_t value) {
    MBC1::writeByte(address, value);
}

uint8_t MBC4::readByte(uint16_t address) {
    return MBC1::readByte(address);
}

void MBC4::writeByte(uint16_t address, uint8_t value) {
    MBC1::writeByte(address, value);
}

uint8_t MBC5::readByte(uint16_t address) {
    return MBC1::readByte(address);
}

void MBC5::writeByte(uint16_t address, uint8_t value) {
    MBC1::writeByte(address, value);
}
