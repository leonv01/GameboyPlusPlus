#include <cstdint>
#include <vector>
#include <memory>

constexpr uint16_t MEMORY_SIZE = 0xFFFF;

class Memory
{
private:
    std::vector<uint8_t> memory;
    std::unique_ptr<uint16_t> SP;

    static constexpr uint16_t romBankStart = 0x0000;
    static constexpr uint16_t romBankEnd = 0x3FFF;
    static constexpr uint16_t switchRomBankStart = 0x4000;
    static constexpr uint16_t switchRomBankEnd = 0x7FFF;
    static constexpr uint16_t VRAMstart = 0x8000;
    static constexpr uint16_t VRAMend = 0x9FFF;
    static constexpr uint16_t switchVRAMstart = 0xA000;
    static constexpr uint16_t switchVRAMend = 0xBFFF;
    static constexpr uint16_t internalRAMstart = 0xC000;
    static constexpr uint16_t internalRAMend = 0xDFFF;
    static constexpr uint16_t unusableStart = 0xE000;
    static constexpr uint16_t unusableEnd = 0xFDFF;
    static constexpr uint16_t spriteAttStart = 0xFE00;
    static constexpr uint16_t spriteAttEnd = 0xFE9F;
    static constexpr uint16_t unusable2Start = 0xFEA0;
    static constexpr uint16_t unusable2End = 0xFEFF;
    static constexpr uint16_t inputOutputStart = 0xFF00;
    static constexpr uint16_t inputOutputEnd = 0xFF4B;
    static constexpr uint16_t unusable3Start = 0xFF4C;
    static constexpr uint16_t unusable3End = 0xFF7F;
    static constexpr uint16_t highRAMstart = 0xFF80;
    static constexpr uint16_t highRAMend = 0xFFFE;
    static constexpr uint16_t interruptRegister = 0xFFFF;

public:
    Memory(uint16_t* address);
    ~Memory();

    void init();

    uint8_t readByte(uint16_t address) const;
    void writeByte(uint16_t address, uint8_t value);
    uint16_t readWord(uint16_t address) const;
    void writeWord(uint16_t address, uint16_t value);

    uint8_t popByte();
    void pushByte(uint8_t value);
    uint16_t popWord();
    void pushWord(uint16_t value);

    void loadROM(const uint8_t* romData, size_t romSize);

    uint8_t& operator[](uint16_t address);
    const uint8_t& operator[](uint16_t address) const;
};

