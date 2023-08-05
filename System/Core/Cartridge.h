//
// Created by leon on 8/2/23.
//

#ifndef GAMEBOYPLUS_CARTRIDGE_H
#define GAMEBOYPLUS_CARTRIDGE_H


#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class Cartridge {
private:

    const int ROM_SIZE = 0x2000;
    const int TITLE_LENGTH = 0xF;
    char licenseCode{};
    char romSize{};
    char* rom;
    char* title;

    std::string path = "/home/leon/Documents/GameboyPlusPlus/GameROM/SuperMario.gb";
public:

    Cartridge();
    ~Cartridge();

    void loadROM();

    [[nodiscard]] uint8_t readByte(uint16_t address) const;
    [[nodiscard]] uint16_t readWord(uint16_t address) const;
};


#endif //GAMEBOYPLUS_CARTRIDGE_H
