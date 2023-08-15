#include "Memory.h"

Memory::Memory(uint16_t *address) {
    SP = std::make_unique<uint16_t>(*address);

    cartridge = nullptr;

    vram = std::vector<uint8_t>(VRAM_SIZE, 0);
    externalRam = std::vector<uint8_t>(RAM_SIZE, 0);
    wramBank0 = std::vector<uint8_t>(WRAM_BANK, 0);
    wramBank1 = std::vector<uint8_t>(WRAM_BANK, 0);
    echo = std::vector<uint8_t>(ECHO_RAM, 0);
    oam = std::vector<uint8_t>(OAM_RAM, 0);
    io = std::vector<uint8_t>(IO, 0);
    hram = std::vector<uint8_t>(H_RAM, 0);

    interrupt = 0;
}

Memory::~Memory() = default;

bool inline inRange(uint16_t address, uint16_t lowerBound, uint16_t upperBound) {
    return address >= lowerBound && address <= upperBound;
}

uint8_t Memory::readByte(uint16_t address) const {
    if (inRange(address, 0x0000, 0x7FFF)) {
        return cartridge->readByte(address);
    } else if (inRange(address, 0x8000, 0x9FFF)) return vram[address - 0x8000];
    else if (inRange(address, 0xA000, 0xBFFF)) return externalRam[address - 0xA000];
    else if (inRange(address, 0xC000, 0xCFFF)) return wramBank1[address - 0xC000];
    else if (inRange(address, 0xD000, 0xDFFF)) return wramBank1[address - 0xD000];
    else if (inRange(address, 0xE000, 0xFDFF)) return echo[address - 0xE000];
    else if (inRange(address, 0xFE00, 0xFE9F)) return oam[address - 0xFE00];
    else if (inRange(address, 0xFF00, 0xFF7F)) return io[address - 0xFF00];
    else if (inRange(address, 0xFF80, 0xFFFE)) return hram[address - 0xFF80];
    else if (address == 0xFFFF) return interrupt;
    else{return 0;}
}

void Memory::writeByte(uint16_t address, uint8_t value) {
    if (inRange(address, 0x0000, 0x7FFF)) {
        cartridge->writeByte(address, value);
    }
    else if (inRange(address, 0x8000, 0x9FFF)) {
        std::cout << "Accessing VRAM" << std::endl;
        vram[address - 0x8000] = value;
    }
    else if (inRange(address, 0xA000, 0xBFFF)) externalRam[address - 0xA000] = value;
    else if (inRange(address, 0xC000, 0xCFFF)) wramBank1[address - 0xC000] = value;
    else if (inRange(address, 0xD000, 0xDFFF)) wramBank1[address - 0xD000] = value;
    else if (inRange(address, 0xE000, 0xFDFF)) echo[address - 0xE000] = value;
    else if (inRange(address, 0xFE00, 0xFE9F)) oam[address - 0xFE00] = value;
    else if (inRange(address, 0xFF00, 0xFF7F)) io[address - 0xFF00] = value;
    else if (inRange(address, 0xFF80, 0xFFFE)) hram[address - 0xFF80] = value;
    else if (address == 0xFFFF) interrupt = value;
    else
        std::cout << "Invalid Address" << std::endl;
}

uint16_t Memory::readWord(uint16_t address) const {
    uint8_t lowByte = 0;
    uint8_t highByte = 0;

    if (inRange(address, 0x0000, 0x7FFF)) {
        lowByte = cartridge->readByte(address);
        highByte = cartridge->readByte(address + 1);
    } else if (inRange(address, 0x8000, 0x9FFF)) {
        address -= 0x8000;
        lowByte = vram[(address)];
        highByte = vram[(address) + 1];
    } else if (inRange(address, 0xA000, 0xBFFF)) {
        address -= 0xA000;
        lowByte = externalRam[(address)];
        highByte = externalRam[(address) + 1];
    } else if (inRange(address, 0xC000, 0xCFFF)) {
        address -= 0xC000;
        lowByte = wramBank0[(address)];
        highByte = wramBank0[(address) + 1];
    } else if (inRange(address, 0xD000, 0xDFFF)) {
        address -= 0xD000;
        lowByte = wramBank1[(address)];
        highByte = wramBank1[(address) + 1];
    } else if (inRange(address, 0xE000, 0xFDFF)) {
        address -= 0xE000;
        lowByte = echo[address];
        highByte = echo[(address) + 1];
    } else if (inRange(address, 0xFE00, 0xFE9F)) {
        address -= 0xFE00;
        lowByte = oam[address];
        highByte = oam[(address) + 1];
    } else if (inRange(address, 0xFF00, 0xFF7F)) {
        address -= 0xFF00;
        lowByte = io[address];
        highByte = io[(address) + 1];
    } else if (inRange(address, 0xFF80, 0xFFFE)) {
        address -= 0xFF80;
        lowByte = hram[address];
        highByte = hram[(address) + 1];
    } else if (address == 0xFFFF) return interrupt;
    else
        std::cout << "Invalid Address" << std::endl;
    return static_cast<uint16_t>((highByte << 8) | lowByte);
}

void Memory::writeWord(uint16_t address, uint16_t value) {
    uint8_t lowByte = value & 0xFF;
    uint8_t highByte = value >> 8;

    if (inRange(address, 0x0000, 0x7FFF)) {
    } else if (inRange(address, 0x8000, 0x9FFF)) {
        address -= 0x8000;
        vram[address] = lowByte;
        vram[address + 1] = highByte;
    } else if (inRange(address, 0xA000, 0xBFFF)) {
        address -= 0xA000;
        externalRam[address] = lowByte;
        externalRam[address + 1] = highByte;
    } else if (inRange(address, 0xC000, 0xCFFF)) {
        address -= 0xC000;
        wramBank0[address] = lowByte;
        wramBank0[address + 1] = highByte;
    } else if (inRange(address, 0xD000, 0xDFFF)) {
        address -= 0xD000;
        wramBank1[address] = lowByte;
        wramBank1[address + 1] = highByte;
    } else if (inRange(address, 0xE000, 0xFDFF)) {
        address -= 0xE000;
        echo[address] = lowByte;
        echo[address + 1] = highByte;
    } else if (inRange(address, 0xFE00, 0xFE9F)) {
        address -= 0xFE00;
        oam[address] = lowByte;
        oam[(address) + 1] = highByte;
    } else if (inRange(address, 0xFF00, 0xFF7F)) {
        address -= 0xFF00;
        io[address] = lowByte;
        io[(address) + 1] = highByte;
    } else if (inRange(address, 0xFF80, 0xFFFE)) {
        address -= 0xFF80;
        hram[address - 0xFF80] = lowByte;
        hram[(address) + 1] = highByte;
    } else std::cout << "Invalid Address" << std::endl;
}

std::vector<uint8_t> *Memory::getVram() {
    return &vram;
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

void Memory::initMemory() {
    writeByte(0xFF0F, 0x00);    // resets Interrupt Flag (IF) register
    writeByte(0xFFFF, 0x00);    // resets Interrupt Enable (IE) register
    writeByte(0xFF04, 0x00);    // resets Divider Register
    writeByte(0xFF05, 0x00);    // resets Timer Counter
    writeByte(0xFF06, 0x00);    // resets Timer Modulo
    writeByte(0xFF07, 0x00);    // resets Timer control
}

void Memory::resetMemory() {
    std::fill(vram.begin(), vram.end(), 0);
    std::fill(externalRam.begin(), externalRam.end(), 0);
    std::fill(wramBank0.begin(), wramBank0.end(),0);
    std::fill(wramBank1.begin(), wramBank0.end(),0);
    std::fill(echo.begin(), echo.end(),0);
    std::fill(oam.begin(), oam.end(),0);
    std::fill(ram.begin(), ram.end(),0);
    std::fill(hram.begin(), hram.end(),0);
    std::fill(io.begin(), io.end(),0);

    interrupt = 0;
    *SP = 0;
}

void Memory::loadROM(std::string path) {
    cartridge = std::make_unique<Cartridge>(path);
}


