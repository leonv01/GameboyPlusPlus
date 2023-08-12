#ifndef GAMEBOYPLUS_MBC_H
#define GAMEBOYPLUS_MBC_H

#include <cstdint>
#include <vector>
#include <memory>

class MBC {
public:
    std::vector<uint8_t> rom;
    std::vector<uint8_t> ram;

    int romBankID{};
    int ramBankID{};

    int romBankCount{};
    int ramBankCount{};

    MBC() = default;
    virtual ~MBC() = default;

    void init(std::vector<uint8_t> cartridgeRom, size_t ramSize);

    virtual uint8_t readByte(uint16_t address) = 0;
    virtual void writeByte(uint16_t address, uint8_t value) = 0;

   // virtual uint16_t readWord(uint16_t address) = 0;
   // virtual void writeWord(uint16_t address, uint16_t value) = 0;
};

class MBC0 : public MBC{
public:
    uint8_t readByte(uint16_t address) override;
    void writeByte(uint16_t address, uint8_t value) override;
};

class MBC1: public MBC{
public:
    bool ramEnabled;
    bool ramAccess;
    bool mode;

    uint8_t readByte(uint16_t address) override;
    void writeByte(uint16_t address, uint8_t value) override;
};

class MBC2: public MBC1{
    uint8_t readByte(uint16_t address) override;
    void writeByte(uint16_t address, uint8_t value) override;
};

class MBC3: public MBC1{
    uint8_t readByte(uint16_t address) override;
    void writeByte(uint16_t address, uint8_t value) override;
};

class MBC4: public MBC1{
    uint8_t readByte(uint16_t address) override;
    void writeByte(uint16_t address, uint8_t value) override;
};

class MBC5: public MBC1{
    uint8_t readByte(uint16_t address) override;
    void writeByte(uint16_t address, uint8_t value) override;
};


#endif //GAMEBOYPLUS_MBC_H
