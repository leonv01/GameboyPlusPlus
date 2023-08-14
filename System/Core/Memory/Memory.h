#include <cstdint>
#include <vector>
#include <memory>
#include <iostream>

#include "Cartridge.h"

class Memory
{
private:
    //Interrupt Flags (IF) Register
    const uint8_t IF_VBLANK = 0x01; // Vertical Blank Interrupt
    const uint8_t IF_LCDSTAT = 0x02; // LCD Status Interrupt
    const uint8_t IF_TIMER = 0x04; // Timer Interrupt
    const uint8_t IF_SERIAL = 0x08; // Serial Transfer Interrupt
    const uint8_t IF_JOYPAD = 0x10;	// Joypad Interrupt

    //const int ROM_SIZE = 0x8000;
    const int RAM_SIZE = 0x2000;
    const int VRAM_SIZE = 0x2000;
    const int WRAM_BANK = 0x1000;
    const int ECHO_RAM = 0x1E00;
    const int OAM_RAM = 0x00A0;
    const int IO = 0x0080;
    const int H_RAM = 0x007F;

    std::unique_ptr<Cartridge> cartridge;

    std::vector<uint8_t> vram;
    std::vector<uint8_t> externalRam;
    std::vector<uint8_t> wramBank0;
    std::vector<uint8_t> wramBank1;
    std::vector<uint8_t> echo;
    std::vector<uint8_t> oam;
    std::vector<uint8_t> ram;
    std::vector<uint8_t> hram;
    std::vector<uint8_t> io;

    uint8_t interrupt;

    std::unique_ptr<uint16_t> SP;

public:
    explicit Memory(uint16_t* address);
    ~Memory();

    std::vector<uint8_t>* getVram();

    void initMemory();
    void loadROM(std::string path);
    void resetMemory();

    [[nodiscard]] uint8_t readByte(uint16_t address) const;
    void writeByte(uint16_t address, uint8_t value);
    [[nodiscard]] uint16_t readWord(uint16_t address) const;
    void writeWord(uint16_t address, uint16_t value);

    uint8_t popByte();
    void pushByte(uint8_t value);
    uint16_t popWord();
    void pushWord(uint16_t value);
};

