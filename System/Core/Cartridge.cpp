//
// Created by leon on 8/2/23.
//

#include "Cartridge.h"

Cartridge::Cartridge() {
    rom = new char[ROM_SIZE];
    title = new char[TITLE_LENGTH];

    loadROM();
}

Cartridge::~Cartridge() {
    delete rom;
    delete title;
}

uint16_t Cartridge::readWord(uint16_t address) const {
    uint8_t highByte = rom[address+ 1];
    uint8_t lowByte = rom[address ];
    return static_cast<uint16_t>((highByte << 8) | lowByte);
}

uint8_t Cartridge::readByte(uint16_t address) const {
    return rom[address];
}

void Cartridge::loadROM() {
    std::ifstream romFile(path, std::ios::binary);
    if(!romFile) {
        std::cerr << "Error opening file" << std::endl;
    }
    else{
        romFile.read(rom, ROM_SIZE);
        romFile.close();

        for(size_t i = 0x134; i <= 0x0143; i++) {
            title [i - 0x134] = rom[i];
            std::cout << title[i - 0x134] << " ";
        }
        std:: cout << std::endl;

        licenseCode = rom[0x0145];

        romSize = rom[0x0147];

        std::cout << static_cast<unsigned int>(licenseCode) << std::endl;
        std::cout << static_cast<unsigned int>(romSize) << std::endl;




        //for(size_t i = 0; i < ROM_SIZE; i++) std::cout << static_cast<unsigned int>(rom[i]) << " ";

    }
}

