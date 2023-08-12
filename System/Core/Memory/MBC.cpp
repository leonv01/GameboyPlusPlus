//
// Created by leon on 8/7/23.
//

#include "MBC.h"

#include <utility>

void MBC::init(std::vector<uint8_t> cartridgeRom, size_t ramSize){
    rom = std::move(cartridgeRom);
    ram = std::vector<uint8_t>(ramSize);
}

uint8_t MBC0::readByte(uint16_t address) {
    if (address < 0x8000) return rom[address];
    else if(address >= 0xA000 && address <= 0xBFFF) return ram[address - 0xA000];
    else return 0xFF;
}

void MBC0::writeByte(uint16_t address, uint8_t value) {
    if (address >= 0xA000 && address <= 0xBFFF) ram[address] = value;
}

uint8_t MBC1::readByte(uint16_t address) {
    /*
     * Reading from ROM Bank 0
     * Read only
     */
    if(address < 0x4000) return rom[address];
    /*
     * Reading from ROM-Banks 0x01 - 0x1F
     * Read only
     */
    else if(address < 0x8000){
        uint16_t bankNumber;
        if(romBankID == 0) bankNumber = 0x01;
        else bankNumber = romBankID;

        uint16_t romAddress = (bankNumber - 1) * 0x4000 + (address - 0x4000);
        return rom[romAddress];
    }
    /*
     * Reading from RAM-Banks 0x00 - 0x03
     * Read/Write
     */
    else if(address >= 0xA000 && address <= 0xBFFF){
        if(ramEnabled){
            uint16_t ramBankNumber = ramBankID & 0x03;
            uint16_t ramAddress = ramBankNumber * 0x2000 + (address - 0xA000);
            return ram[ramAddress];
        }
    }
    return 0xFF;
}

void MBC1::writeByte(uint16_t address, uint8_t value) {
    /*
     * RAM Enabling/Disabling
     * Writing Byte allows (de-)activation of RAM
     * Enabling: value >= 0x0A | Disabling: value < 0x0A
     */
    if(address < 0x2000)
        ramEnabled = ((value & 0x0A) > 0);
    /*
     * ROM Bank Selection
     * Writing to this area selects ROM-Bank-Number for Memory Area 0x4000 - 0x7FFF
     * Lower 5 Bits from value are used to determine ROM-Bank
     */
    else if(address < 0x4000){
        uint8_t bankID = value & 0x1F;

        // ROM-Bank 0x00 is used like 0x01
        if(bankID == 0x00) bankID = 0x01;

        romBankID = (romBankID & 0xE0) | bankID;

        //TODO
        switch(romBankID){
            case 0x00:
            case 0x20:
            case 0x40:
            case 0x60:
                romBankID++;
                break;
        }
    }
    else if(address < 0x6000){
        uint8_t bankID = value & 0x03;
        if(ramEnabled) ramBankID = bankID;
        else{
            romBankID |= (bankID << 5);

            switch(romBankID){
                case 0x00:
                case 0x20:
                case 0x40:
                case 0x60:
                    romBankID++;
                    break;
            }
        }
    }
    else if(address < 0x8000){
        ramEnabled = value & 0x1;
    }
    else if(address >= 0xA000 && address <= 0xBFFF){
        if(ramAccess){
            int offset = address - 0xA000;
            int newAddress = (ramBankID * 0x2000) + offset;
            ram[newAddress] = value;
        }
    }
}

uint8_t MBC2::readByte(uint16_t address) {
    /*
     * Reading from ROM Bank 0
     * Read only
     */
    if(address < 0x4000) return rom[address];
    /*
     * Reading from ROM-Banks 0x01 - 0x0F
     * Read only
     */
    else if(address < 0x8000){
        uint16_t bankNumber;
        if(romBankID == 0) bankNumber = 0x01;
        else bankNumber = romBankID;

        uint16_t romAddress = (bankNumber - 1) * 0x4000 + (address - 0x4000);
        return rom[romAddress];
    }
    else if(address >= 0xA000 && address <= 0xC000){
        if(ramEnabled){
            uint16_t ramAddress = ramBankID * 0x2000 + address - 0xA000;
            return ram[ramAddress];
        }
    }
    return 0x00;
}

void MBC2::writeByte(uint16_t address, uint8_t value) {
    if(address < 0x2000){
        if(!(address & 0x0100))
            ramEnabled = value == 0x0A;
    }
    else if(address < 0x4000){
        if((address & 0x0100))
            romBankID = value;
    }
    else if(address >= 0xA000 && address < 0xC000){
        if(ramEnabled) {
            int ramAddress = ramBankID * 0x2000 + address - 0xA000;
            ram[ramAddress] = value;
        }
    }
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
