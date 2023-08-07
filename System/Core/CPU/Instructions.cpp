#include "CPU.h"

// CPU Control Instructions
void CPU::CCF() {
    // Complement Carry Flag (CCF) - CY=CY xor 1
    reg->flagC(!reg->flagC());
    reg->flagN(false);
    reg->flagH(false);
}
void CPU::SCF() {
    // Set Carry Flag (SCF)
    reg->flagC(true);
    reg->flagN(false);
    reg->flagH(false);
}
void CPU::NOP() {
    // No Operation
    // lol ඞ
}
void CPU::HALT() {
    // Halt CPU
    // TODO
    // Logic to halt CPU until interrupt occrus
}
void CPU::STOP() {
    // Stop CPU
    // TODO
    // Implement logic to put CPU in standby mode
}
void CPU::DI() {
    // Disable Interrupt
    // TODO
}
void CPU::EI() {
    // Enable Interrupt
    // TODO
}

// 8-Bit Load Instruction Set
void CPU::LD_r_r(uint8_t& r, uint8_t& r2) {
    r = r2;
}
void CPU::LD_r_n(uint8_t& r, uint8_t n) {
    r = n;
}
void CPU::LD_r_HL(uint8_t& r) {
    uint16_t address = reg->HL();
    r = memory->readByte(address);
}
void CPU::LD_HL_r(uint8_t& r) {
    uint16_t address = reg->HL();
    memory->writeByte(address, r);
}
void CPU::LD_HL_n(uint8_t n) {
    uint16_t address = reg->HL();
    memory->writeByte(address, n);
}
void CPU::LD_A_nn(uint16_t nn) {
    reg->A = memory->readByte(nn);
}
void CPU::LD_nn_A(uint16_t nn) {
    memory->writeByte(nn, reg->A);
}
void CPU::LD_A_FF00n(uint8_t offset) {
    uint16_t address = 0xFF00 + offset;
    memory->writeByte(address, reg->A);
}
void CPU::LD_FF00n_A(uint8_t offset) {
    uint16_t address = 0xFF00 + offset;
    reg->A = memory->readByte(address);
}
void CPU::LD_A_FF00C() {
    uint16_t address = 0xFF00 + reg->C;
    reg->A = memory->readByte(address);
}
void CPU::LD_FF00C_A() {
    uint16_t address = 0xFF00 + reg->C;
    memory->writeByte(address, reg->A);
}
void CPU::LD_HL_A_INC() {
    memory->writeByte(reg->HL(), reg->A);
    reg->HL(reg->HL() + 1);
}
void CPU::LD_HL_A_DEC() {
    memory->writeByte(reg->HL(), reg->A);
    reg->HL(reg->HL() - 1);
}
void CPU::LD_A_HL_INC() {
    reg->A = memory->readByte(reg->HL());
    reg->HL(reg->HL() + 1);
}
void CPU::LD_A_HL_DEC() {
    reg->A = memory->readByte(reg->HL());
    reg->HL(reg->HL() - 1);
}

// 16-Bit Load Instruction Set
void CPU::LD_rr_nn(uint16_t& rr, uint16_t nn) {
    rr = nn;
}
void CPU::LD_rr_nn(uint8_t& r, uint8_t& r1, uint16_t nn) {
    r = static_cast<uint8_t>(nn >> 8);
    r1 = static_cast<uint8_t>(nn & 0xFF);
}
void CPU::LD_nn_SP(uint16_t nn) {
    memory->writeWord(nn, reg->SP);
}
void CPU::LD_SP_HL() {
    reg->SP = reg->HL();
}
void CPU::PUSH_rr(uint16_t rr) {
    reg->SP -= 2;
    memory->writeWord(reg->SP, rr);
}
void CPU::POP_rr(uint8_t& r, uint8_t& r1) {
    r = memory->readByte(reg->SP++);
    r1 = memory->readByte(reg->SP++);
}
void CPU::POP_rf(uint8_t& r, uint8_t& r1) {
    r = memory->readByte(reg->SP++);
    r1 = memory->readByte(reg->SP++) & 0xF0;
}

// 8-Bit Arithmetic/Logic Instruction Set
void CPU::ADD_r(uint8_t& r) {
    uint16_t result = static_cast<uint16_t>(reg->A) + r;
    reg->setFlagsAddSub(reg->A, r, false, result);
    reg->A = static_cast<uint8_t>(result);
}
void CPU::ADD_n(uint8_t n) {
    uint16_t result = static_cast<uint16_t>(reg->A) + n;
    reg->setFlagsAddSub(reg->A, n, false, result);
    reg->A = static_cast<uint8_t>(result);
}
void CPU::ADD_HL() {
    uint8_t value = memory->readByte(reg->HL());
    uint16_t result = static_cast<uint16_t>(reg->A) + value;
    reg->setFlagsAddSub(reg->A, value, false, result);
    reg->A = static_cast<uint8_t>(result);
}
void CPU::ADC_r(uint8_t& r) {
    uint16_t result = static_cast<uint16_t>(reg->A) + r + (reg->flagC() ? 1 : 0);
    reg->setFlagsAddSub(reg->A, r, false, result);
    reg->A = static_cast<uint8_t>(result);
}
void CPU::ADC_n(uint8_t n) {
    uint16_t result = static_cast<uint16_t>(reg->A) + n + (reg->flagC() ? 1 : 0);
    reg->setFlagsAddSub(reg->A, n, false, result);
    reg->A = static_cast<uint8_t>(result);
}
void CPU::ADC_HL() {
    uint8_t value = memory->readByte(reg->HL());
    uint16_t result = static_cast<uint16_t>(reg->A) + value + (reg->flagC() ? 1 : 0);
    reg->setFlagsAddSub(reg->A, value, false, result);
    reg->A = static_cast<uint8_t>(result);
}
void CPU::SUB_r(uint8_t& r) {
    uint16_t result = static_cast<uint16_t>(reg->A) - r;
    reg->setFlagsAddSub(reg->A, r, true, result);
    reg->A = static_cast<uint8_t>(result);
}
void CPU::SUB_n(uint8_t n) {
    uint16_t result = static_cast<uint16_t>(reg->A) - n;
    reg->setFlagsAddSub(reg->A, n, true, result);
    reg->A = static_cast<uint8_t>(result);
}
void CPU::SUB_HL() {
    uint8_t value = memory->readByte(reg->HL());
    uint16_t result = static_cast<uint16_t>(reg->A) - value;
    reg->setFlagsAddSub(reg->A, value, true, result);
    reg->A = static_cast<uint8_t>(result);
}
void CPU::SBC_r(uint8_t& r) {
    uint16_t result = static_cast<uint16_t>(reg->A) - r - (reg->flagC() ? 1 : 0);
    reg->setFlagsAddSub(reg->A, r, true, result);
    reg->A = static_cast<uint8_t>(result);
}
void CPU::SBC_n(uint8_t n) {
    uint16_t result = static_cast<uint16_t>(reg->A) - n - (reg->flagC() ? 1 : 0);
    reg->setFlagsAddSub(reg->A, n, true, result);
    reg->A = static_cast<uint8_t>(result);
}
void CPU::SBC_HL() {
    uint8_t value = memory->readByte(reg->HL());
    uint16_t result = static_cast<uint16_t>(reg->A) - value - (reg->flagC() ? 1 : 0);
    reg->setFlagsAddSub(reg->A, value, true, result);
    reg->A = static_cast<uint8_t>(result);
}
void CPU::AND_r(uint8_t& r) {
    reg->A &= r;
    reg->setFlagsLogic(reg->A);
}
void CPU::AND_n(uint8_t n) {
    reg->A &= n;
    reg->setFlagsLogic(reg->A);
}
void CPU::AND_HL() {
    uint8_t value = memory->readByte(reg->HL());
    reg->A &= value;
    reg->setFlagsLogic(reg->A);
}
void CPU::XOR_r(uint8_t& r) {
    reg->A ^= r;
    reg->setFlagsLogic(reg->A);
}
void CPU::XOR_n(uint8_t n) {
    reg->A ^= n;
    reg->setFlagsLogic(reg->A);
}
void CPU::XOR_HL() {
    uint8_t value = memory->readByte(reg->HL());
    reg->A ^= value;
    reg->setFlagsLogic(reg->A);
}
void CPU::OR_r(uint8_t& r) {
    reg->A |= r;
    reg->setFlagsLogic(reg->A);
}
void CPU::OR_n(uint8_t n) {
    reg->A |= n;
    reg->setFlagsLogic(reg->A);
}
void CPU::OR_HL() {
    uint8_t value = memory->readByte(reg->HL());
    reg->A |= value;
    reg->setFlagsLogic(reg->A);
}
void CPU::CP_r(uint8_t& r) {
    reg->setFlagsCompare(reg->A, r);
}
void CPU::CP_n(uint8_t n) {
    reg->setFlagsCompare(reg->A, n);
}
void CPU::CP_HL() {
    uint8_t value = memory->readByte(reg->HL());
    reg->setFlagsCompare(reg->A, value);
}
void CPU::INC_r(uint8_t& r) {
    r++;
    reg->setFlagsIncDec(r);
}
void CPU::INC_HL() {
    uint8_t value = memory->readByte(reg->HL());
    value++;
    memory->writeByte(reg->HL(), value);
    reg->setFlagsIncDec(value);
}
void CPU::DEC_r(uint8_t& r) {
    r--;
    reg->setFlagsIncDec(r);
}
void CPU::DEC_HL() {
    uint8_t value = memory->readByte(reg->HL());
    value--;
    memory->writeByte(reg->HL(), value);
    reg->setFlagsIncDec(value);
}
void CPU::DAA() {
    uint8_t correction = 0;
    uint8_t lower_HalfWord = reg->A & 0x0F;

    if (reg->flagH() || (!reg->flagN() && lower_HalfWord > 9))
        correction |= 0x06;

    if (reg->flagC() || (!reg->flagN() && reg->A > 0x99)) {
        correction |= 0x60;
        reg->flagC(true);
    }

    if (reg->flagN())
        reg->A -= correction;
    else
        reg->A += correction;

    reg->flagZ(reg->A == 0);
    reg->flagH(false);
    reg->flagN(false);
}
void CPU::CPL() {
    reg->A = ~reg->A;
    reg->flagN(true);
    reg->flagH(true);
}

// 16-Bit Arithmetic/Logic Instruction Set
void CPU::ADD_HL_rr(uint16_t& rr) {
    uint32_t result = reg->HL() + rr;
    reg->setFlagsAddSub(reg->HL(), rr, false, result);
    reg->HL(static_cast<uint16_t>(result));
    reg->flagH((reg->HL() & 0xFFF) < (rr & 0xFFF));
}
//TODO
void CPU::ADD_HL_rr(uint8_t& r, uint8_t& r1) {
    auto value = static_cast<uint16_t>((r << 8) | r1);
    uint16_t result = reg->HL() + value;
    reg->setFlagsAddSub(reg->HL(), value, false, result);
    reg->HL(static_cast<uint16_t>(result));
    reg->flagH((reg->HL() & 0xFFF) < (value & 0xFFF));
}
void CPU::INC_rr(uint16_t& rr) {
    rr++;
}
void CPU::INC_rr(uint8_t& r, uint8_t& r1) {
    auto value = static_cast<uint16_t>((r << 8) | r1);
    value++;
    r = static_cast<uint8_t>(value >> 8);
    r1 = static_cast<uint8_t>(value & 0xFF);
}
void CPU::DEC_rr(uint16_t& rr) {
    rr--;
}
void CPU::DEC_rr(uint8_t& r, uint8_t& r1) {
    auto value = static_cast<uint16_t>((r << 8) | r1);
    value--;
    r = static_cast<uint8_t>(value >> 8);
    r1 = static_cast<uint8_t>(value & 0xFF);
}
void CPU::ADD_SP_dd(int8_t dd) {
    int result = reg->SP + dd;
    reg->setFlagsAddSub(reg->SP, dd, false, result);
    reg->flagC((result & 0xFFFF0000) != 0);
    reg->flagH((reg->SP & 0x0F) + (dd & 0x0F) > 0x0F);
    reg->SP = static_cast<uint16_t>(result);
}
void CPU::LD_HL_SP_dd(int8_t dd) {
    int result = reg->SP + dd;
    reg->setFlagsAddSub(reg->SP, dd, false, result);
    reg->flagC((result & 0xFFFF0000) != 0);
    reg->flagH((reg->SP & 0x0F) + (dd & 0x0F) > 0x0F);
    reg->SP = static_cast<uint16_t>(result);
}

//Rotate and Shift instructions
void CPU::RLCA() {
    reg->flagC((reg->A & 0x80) != 0);
    reg->A = (reg->A << 1) | (reg->A >> 7);
    reg->setFlagsLogic(reg->A);
}
void CPU::RLA() {
    bool c = reg->C;
    reg->flagC((reg->A & 0x80) != 0);
    reg->A = (reg->A << 1) | c;
    reg->setFlagsLogic(reg->A);
}
void CPU::RRCA() {
    reg->flagC((reg->A & 0x01) != 0);
    reg->A = (reg->A >> 1) | (reg->A << 7);
    reg->setFlagsLogic(reg->A);
}
void CPU::RRA() {
    bool c = reg->C;
    reg->flagC((reg->A & 0x01) != 0);
    reg->A = (reg->A >> 1) | (c << 7);
    reg->setFlagsLogic(reg->A);
}
void CPU::RLC_r(uint8_t& r) {
    reg->flagC((r & 0x80) != 0);
    r = (r << 1) | (r >> 7);
    reg->setFlagsLogic(r);
}
void CPU::RLC_HL() {
    uint8_t value = memory->readByte(reg->HL());
    reg->flagC((value & 0x80) != 0);
    value = (value << 1) | (value >> 7);
    reg->setFlagsLogic(value);
    memory->writeByte(reg->HL(), value);
}
void CPU::RL_r(uint8_t& r) {
    bool c = reg->flagC();
    reg->flagC((r & 0x80) != 0);
    r = (r << 1) | c;
    reg->setFlagsLogic(r);
}
void CPU::RL_HL() {
    bool c = reg->flagC();
    uint8_t value = memory->readByte(reg->HL());
    reg->flagC((value & 0x80) != 0);
    value = (value << 1) | c;
    reg->setFlagsLogic(value);
    memory->writeByte(reg->HL(), value);
}
void CPU::RRC_r(uint8_t& r) {
    reg->flagC((r & 0x01) != 0);
    r = (r >> 1) | (r << 7);
    reg->setFlagsLogic(r);
}
void CPU::RRC_HL() {
    uint8_t value = memory->readByte(reg->HL());
    reg->flagC((value & 0x01) != 0);
    value = (value >> 1) | (value << 7);
    reg->setFlagsLogic(value);
    memory->writeByte(reg->HL(), value);
}
void CPU::RR_r(uint8_t& r) {
    bool c = reg->flagC();
    reg->flagC((r & 0x01) != 0);
    r = (r >> 1) | (c << 7);
    reg->setFlagsLogic(r);
}
void CPU::RR_HL() {
    bool c = reg->flagC();
    uint8_t value = memory->readByte(reg->HL());
    reg->flagC((value & 0x01) != 0);
    value = (value >> 1) | (c << 7);
    reg->setFlagsLogic(value);
    memory->writeByte(reg->HL(), value);
}
void CPU::SLA_r(uint8_t& r) {
    reg->flagC((r & 0x80) != 0);
    r = r << 1;
    reg->setFlagsLogic(r);
}
void CPU::SLA_HL() {
    uint8_t value = memory->readByte(reg->HL());
    reg->flagC((value & 0x80) != 0);
    value = value << 1;
    reg->setFlagsLogic(value);
    memory->writeByte(reg->HL(), value);
}
void CPU::SWAP_r(uint8_t& r) {
    r = ((r & 0x0F) << 4) | ((r & 0xF0) >> 4);
    reg->setFlagsLogic(r);
}
void CPU::SWAP_HL() {
    uint8_t value = memory->readByte(reg->HL());
    value = ((value & 0x0F) << 4) | ((value & 0xF0) >> 4);
    reg->setFlagsLogic(value);
    memory->writeByte(reg->HL(), value);
}
void CPU::SRA_r(uint8_t& r) {
    reg->flagC((r & 0x01) != 0);
    r = (r >> 1) | (r & 0x80);
    reg->setFlagsLogic(r);
}
void CPU::SRA_HL() {
    uint8_t value = memory->readByte(reg->HL());
    reg->flagC(value & 0x01);
    value = (value >> 1) | (value & 0x80);
    reg->setFlagsLogic(value);
    memory->writeByte(reg->HL(), value);
}
void CPU::SRL_r(uint8_t& r) {
    reg->flagC(r & 0x01);
    r = r >> 1;
    reg->setFlagsLogic(r);
}
void CPU::SRL_HL() {
    uint8_t value = memory->readByte(reg->HL());
    reg->flagC(value & 0x01);
    value = value >> 1;
    reg->setFlagsLogic(value);
    memory->writeByte(reg->HL(), value);
}

// Single-Bit Operation Instruction Set
void CPU::BIT_n_r(uint8_t n, uint8_t& r) {
    reg->flagZ((r & (1 << n)) == 0);
    reg->flagN(false);
    reg->flagH(true);
}
void CPU::BIT_n_HL(uint8_t n) {
    uint8_t value = memory->readByte(reg->HL());
    reg->flagZ((value & (1 << n)) == 0);
    reg->flagN(false);
    reg->flagH(true);
}
void CPU::SET_n_r(uint8_t n, uint8_t& r) {
    r |= (1 << n);
}
void CPU::SET_n_HL(uint8_t n) {
    uint8_t value = memory->readByte(reg->HL());
    value |= (1 << n);
    memory->writeByte(reg->HL(), value);
}
void CPU::RES_n_r(uint8_t n, uint8_t& r) {
    r &= ~(1 << n);
}
void CPU::RES_n_HL(uint8_t n) {
    uint8_t value = memory->readByte(reg->HL());
    value &= ~(1 << n);
    memory->writeByte(reg->HL(), value);
}

// Jump Instructions
void CPU::JP_nn(uint16_t nn) {
    reg->PC = nn;
}
void CPU::JP_HL() {
    reg->PC = reg->HL();
}
void CPU::JP_f_nn(bool f, uint16_t nn) {
    // TODO
    if (f)
        reg->PC = nn;
}
void CPU::JR_PC_dd(uint8_t dd) {
    reg->PC += dd;
}
void CPU::JR_f_PC_dd(bool f, uint8_t dd) {
    // TODO
    if (f) {
        reg->PC += dd;
    }
}
void CPU::CALL_nn(uint16_t nn) {
    reg->SP -= 2;
    memory->writeWord(reg->SP, reg->PC);
    reg->PC = nn;
}
void CPU::CALL_f_nn(bool f, uint16_t nn) {
    if (f) {
        reg->SP -= 2;
        memory->writeWord(reg->SP, reg->PC);
        reg->PC = nn;
    }
}
void CPU::RET() {
    reg->PC = reg->SP;
    reg->SP += 2;
}
void CPU::RET_f(bool f) {
    if (f) {
        reg->PC = reg->SP;
        reg->SP += 2;
    }
}
void CPU::RETI() {
    RET();
    EI();
}
void CPU::RST_n(uint8_t n) {
    reg->SP -= 2;
    memory->writeWord(reg->SP, reg->PC);
    reg->PC = n << 8;
}