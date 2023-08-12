//
// Created by leon on 8/2/23.
//

#include "Cartridge.h"

Cartridge::Cartridge() {
    mbc = nullptr;
    title = new char[0xF];
    loadROM();
}

Cartridge::~Cartridge() = default;

uint16_t Cartridge::readWord(uint16_t address) const {
    uint8_t highByte = mbc->readByte(address + 1);
    uint8_t lowByte = mbc->readByte(address);
    return static_cast<uint16_t>((highByte << 8) | lowByte);
}

uint8_t Cartridge::readByte(uint16_t address) const {
    return mbc->readByte(address);
}

void Cartridge::writeByte(uint16_t address, uint8_t value){
    mbc->writeByte(address, value);
}

void Cartridge::loadROM() {
    std::ifstream romFile(path, std::ios::binary);
    if(!romFile) {
        std::cerr << "Error opening file" << std::endl;
    }
    else{
        romFile.seekg(0, std::ios::end);
        std::streampos fileSize = romFile.tellg();
        romFile.seekg(0, std::ios::beg);

        rom = std::vector<uint8_t>(fileSize);
        romFile.read(reinterpret_cast<char*>(rom.data()), fileSize);

        if(!romFile) std::cerr << "Failed to read file" << std::endl;
        romFile.close();

        licenseCode = rom[0x0145];
        sgbFlag = rom[0x0146];
        cartridgeType = rom[0x0147];
        romSize = rom[0x0148];
        ramSize = rom[0x0149];
        newLicensee = static_cast<uint16_t>((rom[0x0144] << 8) | rom[0x0145]);
        destinationCode = rom[0x014A];
        oldLicensee = rom[0x014B];
        maskRom = rom[0x014C];
        headerChecksum = rom[0x014D];

        getCartridgeType();

        mbc->init(rom, ramSize);

        std::cout << static_cast<int>(mbc->readByte(0x0020)) << " " << static_cast<int>(rom[0x0020]) << std::endl;

        printCartridgeInfo();
    }
}

std::string Cartridge::getTitle() {
    for(size_t i = 0x134; i <= 0x0143; i++) {
        title [i - 0x134] = static_cast<char>(rom[i]);
    }
    return title;
}

uint8_t Cartridge::getHeaderChecksum(){
    uint8_t checkSum = 0;
    for(uint16_t address = 0x0134; address <= 0x014C; address++){
        checkSum = checkSum - rom[address] - 1;
    }
    return checkSum;
}

std::string Cartridge::getRamSize() const {
    std::string output;
    switch (romSize) {
        case 0x00:
            output = "0\tNo RAM";
            break;
        case 0x01:
            output = "-\tUnused";
            break;
        case 0x02:
            output = "8 KiB\t1 Bank";
            break;
        case 0x03:
            output = "32 KiB\t4 Banks of 8 KiB each";
            break;
        case 0x04:
            output = "128 KiB\t16 Banks of 8 KiB each";
            break;
        case 0x05:
            output = "64 KiB\t8 Banks of 8 KiB each";
            break;
        default:
            output = "ERROR";
            break;
    }
    return output;
}
std::string Cartridge::getRomSize() const {
    std::string output;
    switch(romSize){
        case 0x00: output = "32 KiB\t2 ROM Banks (no banking)"; break;
        case 0x01: output = "64 KiB\t4 ROM Banks"; break;
        case 0x02: output = "128 KiB\t8 ROM Banks"; break;
        case 0x03: output = "256 KiB\t16 ROM Banks"; break;
        case 0x04: output = "512 KiB\t32 ROM Banks"; break;
        case 0x05: output = "1 MiB\t64 ROM Banks"; break;
        case 0x06: output = "2 MiB\t128 ROM Banks"; break;
        case 0x07: output = "4 MiB\t256 ROM Banks"; break;
        case 0x08: output = "8 MiB\t512 ROM Banks"; break;
        case 0x52: output = "1.1 MiB\t72 ROM Banks"; break;
        case 0x53: output = "1.2 MiB\t80 ROM Banks"; break;
        case 0x54: output = "1.5 MiB\t96 ROM Banks"; break;
        default: output = "ERROR"; break;
    }
    return output;
}

void Cartridge::getCartridgeType() {
    std::string output;
    switch(cartridgeType){
        case 0x00:
            output = "ROM ONLY";
            mbc = new MBC0();
            break;
        case 0x01:
            output = "MBC1";
            mbc = new MBC1();
            break;
        case 0x02:
            output = "MBC1+RAM"; break;
        case 0x03:
            output = "MBC1+RAM+BATTERY"; break;
        case 0x05:
            output = "MBC2";
            mbc = new MBC2();
            break;
        case 0x06:
            output = "MBC2+BATTERY"; break;
        case 0x08:
            output = "ROM+RAM"; break;
        case 0x09:
            output = "ROM+RAM+BATTERY"; break;
        case 0x0B:
            output = "MMM01"; break;
        case 0x0C:
            output = "MMM01+RAM"; break;
        case 0x0D:
            output = "MMM01+RAM+BATTERY"; break;
        case 0x0F:
            output = "MBC3+TIMER+BATTERY"; break;
        case 0x10:
            output = "MBC3+TIMER+RAM+BATTERY"; break;
        case 0x11:
            output = "MBC3";
            mbc = new MBC3();
            break;
        case 0x12:
            output = "MBC3+RAM"; break;
        case 0x13:
            output = "MBC3+RAM+BATTERY"; break;
        case 0x19:
            output = "MBC5"; break;
        case 0x1A:
            output = "MBC5+RAM"; break;
        case 0x1B:
            output = "MBC5+RAM+BATTERY"; break;
        case 0x1C:
            output = "MBC5+RUMBLE"; break;
        case 0x1D:
            output = "MBC5+RUMBLE+RAM"; break;
        case 0x1E:
            output = "MBC5+RUMBLE+RAM+BATTERY"; break;
        case 0x20:
            output = "MBC6"; break;
        case 0x22:
            output = "MBC7+SENSOR+RUMBLE+RAM+BATTERY"; break;
        case 0xFC:
            output = "POCKET CAMERA"; break;
        case 0xFD:
            output = "BANDAI TAMA5"; break;
        case 0xFE:
            output = "HuC3"; break;
        case 0xFF:
            output = "HuC1+RAM+BATTERY"; break;
        default:
            output = "ERROR"; break;
    }
    cartridgeTypeString = output;
}

void Cartridge::printCartridgeInfo() {
    std::cout << static_cast<unsigned int>(licenseCode) << std::endl;
    std::cout << static_cast<unsigned int>(romSize) << std::endl;
    std::cout
            << "Title: " << getTitle() << std::endl
            << "New Licensee: " << "0x" << std::hex << static_cast<int>(newLicensee) << " " << static_cast<int>(newLicensee) << std::endl
            << "Old Licensee: " << "0x" << std::hex << static_cast<int>(oldLicensee) << " " << static_cast<int>(oldLicensee) << std::endl
            << "Cartridge Type: " << cartridgeTypeString << std::endl
            << "ROM Size: " << "0x" << std::hex << static_cast<int>(romSize) << " " << static_cast<int>(romSize) << " | " << getRomSize() << std::endl
            << "RAM Size: " << "0x" << std::hex << static_cast<int>(ramSize) << " " << static_cast<int>(ramSize) << " | " << getRamSize() << std::endl
            << "Destination Code: " << std::hex << static_cast<int>(destinationCode) << std::endl
            << "SGB Flag: " << std::hex << static_cast<int>(sgbFlag) << std::endl
            << "Mask ROM Version Number: " << std::hex << static_cast<int>(maskRom) << std::endl
            << "Header Checksum: " << std::hex << static_cast<int>(headerChecksum) << " | " << std::hex << static_cast<int>(getHeaderChecksum()) << std::endl
            ;
}

