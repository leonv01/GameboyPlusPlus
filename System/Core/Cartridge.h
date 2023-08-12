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
#include "Memory/MBC.h"

class Cartridge {
private:
    const int ROM_SIZE = 0x2000;
    const int TITLE_LENGTH = 0xF;

    MBC* mbc;

    uint8_t licenseCode{};
    std::vector<uint8_t> rom;
    int RAM_SIZE{};

    char* title;          //0x0134 - 0x0143
    //   uint16_t manufacturer;   //0x0144- 0x0145
    uint8_t cgbFlag{};        //0x143
    uint16_t newLicensee{};    //0x0144 - 0x0145
    uint8_t sgbFlag{};        //0x0146
    uint8_t cartridgeType{};  //0x0147
    uint8_t romSize{};        //0x0148
    uint8_t ramSize{};        //0x0149
    uint8_t destinationCode{};//0x014A
    uint8_t oldLicensee{};    //0x014B
    uint8_t maskRom{};        //0x014C
    uint8_t headerChecksum{}; //0x014D
    uint8_t globalChecksum{}; //0x014E - 0x014F

    std::string cartridgeTypeString{};
    std::string path = "/home/leon/Documents/GameboyPlusPlus/GameROM/SuperRC.gb";
public:

    Cartridge();
    ~Cartridge();

    void loadROM();

    void printCartridgeInfo();

    [[nodiscard]] uint8_t readByte(uint16_t address) const;
    [[nodiscard]] uint16_t readWord(uint16_t address) const;

    std::string getTitle();
    void getCartridgeType();
    [[nodiscard]] std::string getRomSize() const;
    [[nodiscard]] std::string getRamSize() const;
    uint8_t getHeaderChecksum();

    void writeByte(uint16_t address, uint8_t value);
};


#endif //GAMEBOYPLUS_CARTRIDGE_H
