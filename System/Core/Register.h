//
// Created by leonv on 31/07/2023.
//

#ifndef GAMEBOYPLUS_REGISTER_H
#define GAMEBOYPLUS_REGISTER_H


#include <cstdint>
#include <string>
#include <sstream>

struct Register {
private:
    const uint8_t FLAG_Z = 0x80;
    const uint8_t FLAG_N = 0x40;
    const uint8_t FLAG_H = 0x20;
    const uint8_t FLAG_C = 0x10;

public:

    uint8_t A;		//Accumulator
    uint8_t F;      //Flags
    uint8_t B, C;	//General-Purpose Register
    uint8_t D, E;	//General-Purpose Register
    uint8_t H, L;	//General-Purpose Register

    uint16_t SP;	//Stackpointer
    uint16_t PC;	//Program Counter

    [[nodiscard]] uint16_t BC() const;
    void BC(uint16_t value);

    [[nodiscard]] uint16_t DE() const;
    void DE(uint16_t value);

    [[nodiscard]] uint16_t HL() const;
    void HL(uint16_t value);

    [[nodiscard]] std::string toString() const;

    [[nodiscard]] bool flagZ() const;
    void flagZ(bool value);

    [[nodiscard]] bool flagN() const;
    void flagN(bool value);

    [[nodiscard]] bool flagH() const;
    void flagH(bool value);

    [[nodiscard]] bool flagC() const;
    void flagC(bool value);

    // Helper function to set flags for ADD, ADC, SUB, and SBC operations
    void setFlagsAddSub(uint8_t a, uint8_t b, bool isSubtraction, uint16_t result);

    // Helper function to set flags for logical operations (AND, OR, XOR)
    void setFlagsLogic(uint8_t result);

    // Helper function to set flags for compare (CP) operation
    void setFlagsCompare(uint8_t a, uint8_t b);

    // Helper function to set flags for increment and decrement operations
    void setFlagsIncDec(uint8_t value);

    Register();
    ~Register() = default;
};


#endif //GAMEBOYPLUS_REGISTER_H
