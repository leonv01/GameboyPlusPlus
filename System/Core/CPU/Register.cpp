//
// Created by leonv on 31/07/2023.
//

#include "Register.h"

Register::Register() : SP(0xFFFE), PC(0x0100){
    A = F = B = C = D = E = H = L = 0;
}

uint16_t Register::AF() const{
    return static_cast<uint16_t>((A << 8) | F);
}
void Register::AF(uint16_t value){
    A = static_cast<uint8_t>(value >> 8);
    F = static_cast<uint8_t>(value);
}

uint16_t Register::BC() const{
    return static_cast<uint16_t>((B << 8) | C);
}
void Register::BC(uint16_t value) {
    B = static_cast<uint8_t>(value >> 8);
    C = static_cast<uint8_t>(value);
}

uint16_t Register::DE() const {
    return static_cast<uint16_t>((D << 8) | E);
}
void Register::DE(uint16_t value) {
    D = static_cast<uint8_t>(value >> 8);
    E = static_cast<uint8_t>(value);
}

uint16_t Register::HL() const {
    return static_cast<uint16_t>((H << 8) | L);
}
void Register::HL(uint16_t value) {
    H = static_cast<uint8_t>(value >> 8);
    L = static_cast<uint8_t>(value);
}

std::string Register::toString() const {
    std::ostringstream oss;
    oss << "\nRegister:\n"
        << "A: " << std::hex << static_cast<int>(A) << ' '
        << "B: " << std::hex << static_cast<int>(B) << ' '
        << "C: " <<std::hex <<  static_cast<int>(C) << ' '
        << "D: "  << std::hex << static_cast<int>(D) << ' '
        << "E: " << std::hex << static_cast<int>(E) << ' '
        << "H: " << std::hex << static_cast<int>(H) << ' '
        << "L: " << std::hex << static_cast<int>(L) << ' '
        << "BC: " << std::hex << static_cast<int>(BC()) << ' '
        << "DE: " << std::hex << static_cast<int>(DE()) << ' '
        << "HL: " << std::hex << static_cast<int>(HL()) << ' '
        << "SP: " << std::hex << static_cast<int>(SP) << ' '
        << "PC: " << std::hex << static_cast<int>(PC) << '\n'
        << "Flags:\n"
        << "Z: " << std::hex <<static_cast<int>(flagZ()) << ' '
        << "N: " << std::hex <<static_cast<int>(flagN()) << ' '
        << "H: " << std::hex <<static_cast<int>(flagH()) << ' '
        << "C: " << std::hex <<static_cast<int>(flagC()) << '\n';
    return oss.str();
}

bool Register::flagZ() const {
    return (F & FLAG_Z);
}
void Register::flagZ(bool value) {
    if (value)
        F |= FLAG_Z;
    else
        F &= ~FLAG_Z;
}

bool Register::flagN() const {
    return (F & FLAG_N);
}
void Register::flagN(bool value) {
    if (value)
        F |= FLAG_N;
    else
        F &= ~FLAG_N;
}


bool Register::flagH() const {
    return (F & FLAG_H);
}
void Register::flagH(bool value) {
    if (value)
        F |= FLAG_H;
    else
        F &= ~FLAG_H;
}

bool Register::flagC() const {
    return (F & FLAG_C);
}
void Register::flagC(bool value) {
    if (value)
        F |= FLAG_C;
    else
        F &= ~FLAG_C;
}

void Register::setFlagsAddSub(uint8_t a, uint8_t b, bool isSubtraction, uint16_t result) {
    flagZ((result & 0xFF) == 0);
    flagN(isSubtraction);
    flagH((((a & 0x0F) + (isSubtraction ? (~b) : b) & 0x0F) > 0x0F));
    flagC((result & 0x100) != 0);
}

void Register::setFlagsLogic(uint8_t result) {
    flagZ(result == 0);
    flagN(true);
    flagH(true);
    flagC(false);
}

void Register::setFlagsCompare(uint8_t a, uint8_t b) {
    uint16_t result = static_cast<uint8_t>(a) - b;
    flagZ((result & 0xFF) == 0);
    flagN(true);
    flagH((a & 0x0F) < (b & 0x0F));
    flagC(a < b);
}

void Register::setFlagsIncDec(uint8_t value) {
    flagZ(value == 0);
    flagN(false);
    flagH((value & 0x0F) == 0);
}

void Register::init() {
    PC = 0x100;
    AF(0x01B0);
    BC(0x0013);
    DE(0x00D8);
    HL(0x014D);
    SP = 0xFFFE;
    PC = 0x0100;
}
