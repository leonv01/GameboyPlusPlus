#ifndef GAMEBOYPLUS_CPU_H
#define GAMEBOYPLUS_CPU_H

#include <sstream>
#include <iostream>

#include "Register.h"
#include "../Memory/Memory.h"

class CPU {
private:
    /*
     * Timer Addresses
     */
    const uint16_t TAC  = 0xFF07;   // Timer Control
    const uint16_t TMA  = 0xFF06;   // Timer Modulo
    const uint16_t TIMA = 0xFF05;   // Timer Counter
    const uint16_t DIV  = 0xFF04;   // Divider Register

    const uint16_t IF   = 0xFF0F;   // Interrupt Flag
    const uint16_t IE   = 0xFFFF;   // Interrupt Enable

    const int CLOCK_SPEED = 4194304;
    bool interruptMaster{};

    std::unique_ptr<Register> reg;

public:
    /*
     * Interrupt constants
     */
    constexpr static uint8_t IF_VBLANK     = 0x01;
    constexpr static uint8_t IF_LCDSTAT    = 0x02;
    constexpr static uint8_t IF_TIMER      = 0x04;
    constexpr static uint8_t IF_SERIAL     = 0x08;
    constexpr static uint8_t IF_JOYPAD     = 0x10;

    uint8_t interruptEnableRegister{};
    uint8_t interruptRequestRegister{};
    void handleInterrupt();
    void requestInterrupt(uint8_t value);
    void interruptServiceRoutine(uint8_t value);

    /*
     * Timer
     */
    uint8_t timerModulo{};
    uint16_t timerCounter{};
    uint16_t timerFrequency{};
    void updateTimer(int currentCycle);

    /*
     * Divider
     */
    uint16_t dividerFrequency{};
    uint16_t dividerCounter{};
    void updateDivider(int currentCycles);

    int cycle{};

    std::shared_ptr<Memory> memory;     //Main Memory

    explicit CPU();
    ~CPU();

    void initCPU();
    uint8_t fetchOpCode();
    void parseOpCode(uint8_t opcode);
    void prefixOpCode(uint8_t opcode);

    void printStatus();

    // 8-Bit Load Instruction Set
    static void LD_r_r(uint8_t &r, uint8_t &r2);    // LD r, r2 (Load reference 8-bit value (r2) into register (r))
    static void LD_r_n(uint8_t &r, uint8_t n);    // LD r, n (Load immediate 8-bit value (n) into register (r))
    void LD_r_HL(uint8_t &r);    // LD r, HL (Load value from memory location specified by HL register pair into register (r))
    void LD_HL_r(uint8_t &r);    // LD r (Load value from register (r) into memory location specified by HL register pair)
    void LD_HL_n(uint8_t n);    // LD HL, n (Load immediate 8-bit value (n) into memory location specified by HL register pair)
    void LD_A_nn(uint16_t nn);    // LD A, n (Load 8-bit value from memory location specified by 16-bit immediate value (nn) into Accumulator (A))
    void LD_nn_A(uint16_t nn);    // LD nn, A (Load value of Accumulator (A) into memory location specified by 16-bit immediate value (nn))
    void LD_A_FF00n(uint8_t offset);    // LD A, FF00n (Load 8-bit value from I/O port at address 0xFF00 + offset (n) into Accumulator (A))
    void LD_FF00n_A(uint8_t offset);    // LD FF00n, A (Load value of Accumulator (A) into I/O port at address 0xFF00 + offset (n))
    void LD_A_FF00C();    // LD A, FF00C (Load 8-bit value from I/O port at address 0xFF00 + register C into Accumulator (A))
    void LD_FF00C_A();    // LD FF00C, A (Load value of Accumulator (A) into I/O port at address 0xFF00 + register C)
    void LD_HL_A_INC();
    void LD_HL_A_DEC();
    void LD_A_HL_INC();
    void LD_A_HL_DEC();

    // 16-Bit Load Instruction Set
    static void LD_rr_nn(uint16_t &rr, uint16_t nn);    // LD rr, nn (Load 16-bit register with immediate 16-bit value)
    static void LD_rr_nn(uint8_t &r, uint8_t &r1, uint16_t nn);

    void LD_nn_SP(uint16_t nn);    // LD (nn), SP (Store Stack Pointer to Memory)
    void LD_SP_HL();    // LD SP, HL (Load Stack Pointer from HL)
    void PUSH_rr(uint16_t rr);    // PUSH rr (Push 16-bit register onto the Stack)
    void POP_rr(uint8_t &r, uint8_t &r1);    // POP rr (Pop 16-bit register from the Stack)
    void POP_rf(uint8_t &r, uint8_t &r1);    // POP rf (Pop 16-bit register from the Stack (flags))

    // 8-Bit Arithmetic/Logic Instruction Set
    void ADD_r(uint8_t &r);    // ADD A, r (Add register to accumulator)
    void ADD_n(uint8_t n);    // ADD A, n (Add immediate value to accumulator)
    void ADD_HL();    // ADD A, (HL) (Add value at memory address HL to accumulator)
    void ADC_r(uint8_t &r);    // ADC A, r (Add register and carry flag to accumulator)
    void ADC_n(uint8_t n);    // ADC A, n (Add immediate value and carry flag to accumulator)
    void ADC_HL();    // ADC A, (HL) (Add value at memory address HL and carry flag to accumulator)
    void SUB_r(uint8_t &r);    // SUB r (Subtract register from accumulator)
    void SUB_n(uint8_t n);    // SUB n (Subtract immediate value from accumulator)
    void SUB_HL();    // SUB (HL) (Subtract value at memory address HL from accumulator)
    void SBC_r(uint8_t &r);    // SBC A, r (Subtract register and carry flag from accumulator)
    void SBC_n(uint8_t n);    // SBC A, n (Subtract immediate value and carry flag from accumulator)
    void SBC_HL();    // SBC A, (HL) (Subtract value at memory address HL and carry flag from accumulator)
    void AND_r(uint8_t &r);    // AND r (Bitwise AND register with accumulator)
    void AND_n(uint8_t n);    // AND n (Bitwise AND immediate value with accumulator)
    void AND_HL();    // AND (HL) (Bitwise AND value at memory address HL with accumulator)
    void XOR_r(uint8_t &r);    // XOR r (Bitwise XOR register with accumulator)
    void XOR_n(uint8_t n);    // XOR n (Bitwise XOR immediate value with accumulator)
    void XOR_HL();    // XOR (HL) (Bitwise XOR value at memory address HL with accumulator)
    void OR_r(uint8_t &r);    // OR r (Bitwise OR register with accumulator)
    void OR_n(uint8_t n);    // XOR n (Bitwise XOR immediate value with accumulator)
    void OR_HL();    // XOR (HL) (Bitwise XOR value at memory address HL with accumulator)
    void CP_r(uint8_t &r);    // CP r (Compare register with accumulator)
    void CP_n(uint8_t n);    // CP n (Compare immediate value with accumulator)
    void CP_HL();    // CP (HL) (Compare value at memory address HL with accumulator)
    void INC_r(uint8_t &r);    // INC r (Increment register)
    void INC_HL();    // INC (HL) (Increment value at memory address HL)
    void DEC_r(uint8_t &r);    // DEC r (Decrement register)
    static void DEC_rr(uint8_t &r, uint8_t &r1);

    void DEC_HL();    // DEC (HL) (Decrement value at memory address HL)
    void DAA();    // DAA (Decimal adjust accumulator)
    void CPL();    // CPL (Complement accumulator)

    // 16-Bit Arithmetic/Logic Instruction Set
    void ADD_HL_rr(uint16_t &rr);    // ADD HL, rr (Add register pair rr to HL)
    void ADD_HL_rr(uint8_t &r, uint8_t &r1);

    static void INC_rr(uint16_t &rr);    // INC rr (Increment register pair rr)
    static void INC_rr(uint8_t &r, uint8_t &r1);

    static void DEC_rr(uint16_t &rr);    // DEC rr (Decrement register pair rr)
    void ADD_SP_dd(int8_t dd);    // ADD SP, dd (Add 8-bit signed number dd to SP)
    void LD_HL_SP_dd(int8_t dd);    // LD HL, SP+dd (Load HL with SP plus 8-bit signed number dd)

    //Rotate and Shift instructions
    void RLCA();    // RLCA (Rotate A left)
    void RLA();    // RLA (Rotate A left through carry)
    void RRCA();    // RRCA (Rotate A right)
    void RRA();    // RRA (Rotate A right through carry)
    void RLC_r(uint8_t &r);    // RLC r (Rotate left through carry)
    void RLC_HL();    // RLC (HL) (Rotate left through carry)
    void RL_r(uint8_t &r);    // RL r (Rotate left through carry)
    void RL_HL();    // RL (HL) (Rotate left through carry)
    void RRC_r(uint8_t &r);    // RRC r (Rotate right through carry)
    void RRC_HL();    // RRC (HL) (Rotate right through carry)
    void RR_r(uint8_t &r);    // RR r (Rotate right through carry)
    void RR_HL();    // SLA r (Shift left arithmetic, b0=0)
    void SLA_r(uint8_t &r);    // SLA (HL) (Shift left arithmetic, b0=0)
    void SLA_HL();    // SWAP r (Exchange low/hi-nibble)
    void SWAP_r(uint8_t &r);    // SWAP (HL) (Exchange low/hi-nibble)
    void SWAP_HL();    // SRA r (Shift right arithmetic, b7=b7)
    void SRA_r(uint8_t &r);

    void SRA_HL();    // SRA (HL) (Shift right arithmetic, b7=b7)
    void SRL_r(uint8_t &r);    // SRL r (Shift right logical, b7=0)
    void SRL_HL();    // SRL (HL) (Shift right logical, b7=0)

    // Single-Bit Operation Instruction Set
    void BIT_n_r(uint8_t n, uint8_t &r);    // BIT n, r (Test bit n in register r)
    void BIT_n_HL(uint8_t n);    // BIT n, (HL) (Test bit n in memory at address HL)
    static void SET_n_r(uint8_t n, uint8_t &r);    // SET n, r (Set bit n in register r)
    void SET_n_HL(uint8_t n);    // SET n, (HL) (Set bit n in memory at address HL)
    static void RES_n_r(uint8_t n, uint8_t &r);    // RES n, r (Reset bit n in register r)
    void RES_n_HL(uint8_t n);    // RES n, (HL) (Reset bit n in memory at address HL)

    // CPU Control Instructions
    void CCF();    // CCF (Complement carry flag)
    void SCF();    // SCF (Set carry flag)
    void NOP();    // NOP (No operation)
    void HALT();    // HALT (Halt until interrupt occurs)
    void STOP();    // STOP (Low power standby mode)
    void DI();    // DI (Disable interrupts, IME = 0)
    void EI();    // EI (Enable interrupts, IME = 1)

    // Jump Instructions
    void JP_nn(uint16_t nn);    // JP nn (Jump to 16-bit immediate address nn)
    void JP_HL();    // JP HL (Jump to the address held in the HL register)
    void JP_f_nn(bool f, uint16_t nn);    // JP f, nn (Conditional jump to 16-bit immediate address nn based on flag f)
    void JR_PC_dd(uint8_t dd);    // JR PC+dd (Relative jump to PC+8-bit signed displacement dd)
    void JR_f_PC_dd(bool f,
                    uint8_t dd);    // JR f, PC+dd (Conditional relative jump to PC+8-bit signed displacement dd based on flag f)
    void CALL_nn(uint16_t nn);    // CALL nn (Call subroutine at 16-bit immediate address nn)
    void CALL_f_nn(bool f,
                   uint16_t nn);    // CALL f, nn (Conditional call to subroutine at 16-bit immediate address nn based on flag f)
    void RET();    // RET (Return from subroutine)
    void RET_f(bool f);    // RET f (Conditional return from subroutine based on flag f)
    void RETI();    // RETI (Return from subroutine and enable interrupts, IME = 1)
    void RST_n(uint8_t n);    // RST n (Restart at address 00h, 08h, 10h, 18h, 20h, 28h, 30h, 38h)
};


#endif //GAMEBOYPLUS_CPU_H
