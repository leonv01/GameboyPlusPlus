#include "CPU.h"

#include <iostream>

uint8_t CPU::parseOpCode(uint8_t opcode) {
    uint8_t byte;
    uint16_t word;
    bool condition;
    uint8_t cycle = 0;

    switch (opcode) {
        //No Operation
        case 0x00:
            cycle += 4;
            NOP(); break;
            //STOP
        case 0x10:
            cycle += 4;
            STOP(); break;
            //HALT
        case 0x76:
            cycle += 4;
            HALT(); break;
            //Disable Interrupts
        case 0xF3:
            cycle += 4;
            DI(); break;
            //Prefix CB
        case 0xCB:
            cycle += 4;
            byte = memory->readByte(reg->PC);
            prefixOpCode(byte);
            break;
            //Enable Interrupts
        case 0xFB:
            cycle += 4;
            EI(); break;

            //LD
        case 0x40:
            cycle += 4;
            LD_r_r(reg->B, reg->B); break;
        case 0x50:
            cycle += 4;
            LD_r_r(reg->D, reg->B); break;
        case 0x60:
            cycle += 4;
            LD_r_r(reg->H, reg->B); break;
        case 0x70:
            cycle += 8;
            LD_HL_r(reg->B); break;
        case 0xE0:
            cycle += 12;
            byte = memory->readByte(reg->PC);
            LD_FF00n_A(byte);
            break;
        case 0xF0:
            cycle += 12;
            byte = memory->readByte(reg->PC);
            LD_A_FF00n(byte);
            break;
        case 0x41:
            cycle += 4;
            LD_r_r(reg->B, reg->C); break;
        case 0x51:
            cycle += 4;
            LD_r_r(reg->D, reg->C); break;
        case 0x61:
            cycle += 4;
            LD_r_r(reg->H, reg->C); break;
        case 0x71:
            cycle += 8;
            LD_HL_r(reg->C); break;
        case 0x02:
            cycle += 8;
            LD_nn_A(reg->BC()); break;
        case 0x12:
            cycle += 8;
            LD_nn_A(reg->BC()); break;
        case 0x22:
            cycle += 8;
            LD_HL_A_INC();  break;
        case 0x32:
            cycle += 8;
            LD_HL_A_DEC(); break;
        case 0x42:
            cycle += 4;
            LD_r_r(reg->B, reg->D); break;
        case 0x52:
            cycle += 4;
            LD_r_r(reg->D, reg->D); break;
        case 0x62:
            cycle += 4;
            LD_r_r(reg->H, reg->D); break;
        case 0x72:
            cycle += 8;
            LD_HL_r(reg->D); break;
        case 0xE2:
            cycle += 8;
            LD_A_FF00C(); break;
        case 0xF2:
            cycle += 8;
            LD_FF00C_A(); break;
        case 0x43:
            cycle += 4;
            LD_r_r(reg->B, reg->E); break;
        case 0x53:
            cycle += 4;
            LD_r_r(reg->D, reg->E); break;
        case 0x63:
            cycle += 4;
            LD_r_r(reg->H, reg->E); break;
        case 0x73:
            cycle += 8;
            LD_HL_r(reg->E); break;
        case 0x44:
            cycle += 4;
            LD_r_r(reg->B, reg->H); break;
        case 0x54:
            cycle += 4;
            LD_r_r(reg->D, reg->H); break;
        case 0x64:
            cycle += 4;
            LD_r_r(reg->H, reg->H); break;
        case 0x74:
            cycle += 8;
            LD_HL_r(reg->H); break;
        case 0x45:
            cycle += 4;
            LD_r_r(reg->B, reg->L); break;
        case 0x55:
            cycle += 4;
            LD_r_r(reg->D, reg->L); break;
        case 0x65:
            cycle += 4;
            LD_r_r(reg->H, reg->L); break;
        case 0x75:
            cycle += 8;
            LD_HL_r(reg->L); break;
        case 0x06:
            cycle += 8;
            byte = memory->readByte(reg->PC);
            LD_r_n(reg->B, byte);
            break;
        case 0x16:
            cycle += 8;
            byte = memory->readByte(reg->PC);
            LD_r_n(reg->D, byte);
            break;
        case 0x26:
            cycle += 8;
            byte = memory->readByte(reg->PC);
            LD_HL_n(byte);
            break;
        case 0x36:
            cycle += 12;
            word = memory->readWord(reg->PC);
            reg->PC++;
            LD_HL_n(word); break;
        case 0x46:
            cycle += 8;
            LD_r_HL(reg->B); break;
        case 0x56:
            cycle += 8;
            LD_r_HL(reg->D); break;
        case 0x66:
            cycle += 8;
            LD_r_HL(reg->H); break;
        case 0x47:
            cycle += 4;
            LD_r_r(reg->B, reg->A); break;
        case 0x57:
            cycle += 4;
            LD_r_r(reg->D, reg->A); break;
        case 0x67:
            cycle += 4;
            LD_r_r(reg->H, reg->A); break;
        case 0x77:
            cycle += 8;
            LD_HL_r(reg->A); break;
        case 0x48:
            cycle += 4;
            LD_r_r(reg->C, reg->B); break;
        case 0x58:
            cycle += 4;
            LD_r_r(reg->E, reg->B); break;
        case 0x68:
            cycle += 4;
            LD_r_r(reg->L, reg->B); break;
        case 0x78:
            cycle += 4;
            LD_r_r(reg->A, reg->B); break;
        case 0x49:
            cycle += 4;
            LD_r_r(reg->C, reg->C); break;
        case 0x59:
            cycle += 4;
            LD_r_r(reg->E, reg->C); break;
        case 0x69:
            cycle += 4;
            LD_r_r(reg->L, reg->C); break;
        case 0x79:
            cycle += 4;
            LD_r_r(reg->A, reg->C); break;
        case 0x0A:
            cycle += 8;
            LD_A_nn(reg->BC()); break;
        case 0x1A:
            cycle += 8;
            LD_A_nn(reg->DE()); break;
        case 0x2A:
            cycle += 8;
            LD_A_HL_INC(); break;
        case 0x3A:
            cycle += 8;
            LD_A_HL_DEC(); break;
        case 0x4A:
            cycle += 4;
            LD_r_r(reg->C, reg->D); break;
        case 0x5A:
            cycle += 4;
            LD_r_r(reg->E, reg->D); break;
        case 0x6A:
            cycle += 4;
            LD_r_r(reg->L, reg->D); break;
        case 0x7A:
            cycle += 4;
            LD_r_r(reg->A, reg->D); break;
        case 0x4B:
            cycle += 4;
            LD_r_r(reg->C, reg->E); break;
        case 0x5B:
            cycle += 4;
            LD_r_r(reg->E, reg->E); break;
        case 0x6B:
            cycle += 4;
            LD_r_r(reg->L, reg->E); break;
        case 0x7B:
            cycle += 4;
            LD_r_r(reg->A, reg->E); break;
        case 0x4C:
            cycle += 4;
            LD_r_r(reg->C, reg->H); break;
        case 0x5C:
            cycle += 4;
            LD_r_r(reg->E, reg->H); break;
        case 0x6C:
            cycle += 4;
            LD_r_r(reg->L, reg->H); break;
        case 0x7C:
            cycle += 4;
            LD_r_r(reg->A, reg->H); break;
        case 0x4D:
            cycle += 4;
            LD_r_r(reg->C, reg->L); break;
        case 0x5D:
            cycle += 4;
            LD_r_r(reg->E, reg->L); break;
        case 0x6D:
            cycle += 4;
            LD_r_r(reg->L, reg->L); break;
        case 0x7D:
            cycle += 4;
            LD_r_r(reg->A, reg->L); break;
        case 0x0E:
            cycle += 8;
            byte = memory->readByte(reg->PC);
            LD_r_n(reg->C, byte);
            break;
        case 0x1E:
            cycle += 8;
            byte = memory->readByte(reg->PC);
            LD_r_n(reg->E, byte);
            break;
        case 0x2E:
            cycle += 8;
            byte = memory->readByte(reg->PC);
            LD_r_n(reg->L, byte);
            break;
        case 0x3E:
            cycle += 8;
            byte = memory->readByte(reg->PC);
            LD_r_n(reg->A, byte);
            break;
        case 0x4E:
            cycle += 8;
            LD_r_HL(reg->C); break;
        case 0x5E:
            cycle += 8;
            LD_r_HL(reg->E); break;
        case 0x6E:
            cycle += 8;
            LD_r_HL(reg->L); break;
        case 0x7E:
            cycle += 8;
            LD_r_HL(reg->A); break;
        case 0x4F:
            cycle += 4;
            LD_r_r(reg->C, reg->A); break;
        case 0x5F:
            cycle += 4;
            LD_r_r(reg->E, reg->A); break;
        case 0x6F:
            cycle += 4;
            LD_r_r(reg->L, reg->A); break;
        case 0x7F:
            cycle += 4;
            LD_r_r(reg->A, reg->A); break;
        case 0xFA:
            cycle += 16;
            word = memory->readWord(reg->PC);
            reg->PC++;
            LD_A_nn(word);
            break;
        case 0xEA:
            cycle += 16;
            word = memory->readWord(reg->PC);
            reg->PC++;
            LD_nn_A(word);
            break;

            //ADD
        case 0x80:
            cycle += 4;
            ADD_r(reg->B); break;
        case 0x81:
            cycle += 4;
            ADD_r(reg->C); break;
        case 0x82:
            cycle += 4;
            ADD_r(reg->D); break;
        case 0x83:
            cycle += 4;
            ADD_r(reg->E); break;
        case 0x84:
            cycle += 4;
            ADD_r(reg->H); break;
        case 0x85:
            cycle += 4;
            ADD_r(reg->L); break;
        case 0x86:
            cycle += 8;
            ADD_HL(); break;
        case 0x87:
            cycle += 4;
            ADD_r(reg->A); break;
        case 0xC6:
            cycle += 8;
            byte = memory->readByte(reg->PC);
            ADD_n(byte);
            break;

            //ADC
        case 0x88:
            cycle += 4;
            ADC_r(reg->B); break;
        case 0x89:
            cycle += 4;
            ADC_r(reg->C); break;
        case 0x8A:
            cycle += 4;
            ADC_r(reg->D); break;
        case 0x8B:
            cycle += 4;
            ADC_r(reg->E); break;
        case 0x8C:
            cycle += 4;
            ADC_r(reg->H); break;
        case 0x8D:
            cycle += 4;
            ADC_r(reg->L); break;
        case 0x8E:
            cycle += 8;
            ADC_HL(); break;
        case 0x8F:
            cycle += 4;
            ADC_r(reg->A); break;
        case 0xCE:
            cycle += 8;
            byte = memory->readByte(reg->PC);
            ADC_n(byte);
            break;

            //SUB
        case 0x90:
            cycle += 4;
            SUB_r(reg->B); break;
        case 0x91:
            cycle += 4;
            SUB_r(reg->C); break;
        case 0x92:
            cycle += 4;
            SUB_r(reg->D); break;
        case 0x93:
            cycle += 4;
            SUB_r(reg->E); break;
        case 0x94:
            cycle += 4;
            SUB_r(reg->H); break;
        case 0x95:
            cycle += 4;
            SUB_r(reg->L); break;
        case 0x96:
            cycle += 8;
            SUB_HL(); break;
        case 0x97:
            cycle += 4;
            SUB_r(reg->A); break;
        case 0xD6:
            cycle += 8;
            byte = memory->readByte(reg->PC);
            SUB_n(byte);
            break;

            //SBC
        case 0x98:
            cycle += 4;
            SBC_r(reg->B); break;
        case 0x99:
            cycle += 4;
            SBC_r(reg->C); break;
        case 0x9A:
            cycle += 4;
            SBC_r(reg->D); break;
        case 0x9B:
            cycle += 4;
            SBC_r(reg->E); break;
        case 0x9C:
            cycle += 4;
            SBC_r(reg->H); break;
        case 0x9D:
            cycle += 4;
            SBC_r(reg->L); break;
        case 0x9E:
            cycle += 8;
            SBC_HL(); break;
        case 0x9F:
            cycle += 4;
            SBC_r(reg->A); break;
        case 0xDE:
            cycle += 8;
            byte = memory->readByte(reg->PC);
            SBC_n(byte);
            break;

            //AND
        case 0xA0:
            cycle += 4;
            AND_r(reg->B); break;
        case 0xA1:
            cycle += 4;
            AND_r(reg->C); break;
        case 0xA2:
            cycle += 4;
            AND_r(reg->D); break;
        case 0xA3:
            cycle += 4;
            AND_r(reg->E); break;
        case 0xA4:
            cycle += 4;
            AND_r(reg->H); break;
        case 0xA5:
            cycle += 4;
            AND_r(reg->L); break;
        case 0xA6:
            cycle += 8;
            AND_HL(); break;
        case 0xA7:
            cycle += 4;
            AND_r(reg->A); break;
        case 0xE6:
            cycle += 8;
            byte = memory->readByte(reg->PC);
            AND_n(byte);
            break;

            //XOR
        case 0xA8:
            cycle += 4;
            XOR_r(reg->B); break;
        case 0xA9:
            cycle += 4;
            XOR_r(reg->C); break;
        case 0xAA:
            cycle += 4;
            XOR_r(reg->D); break;
        case 0xAB:
            cycle += 4;
            XOR_r(reg->E); break;
        case 0xAC:
            cycle += 4;
            XOR_r(reg->H); break;
        case 0xAD:
            cycle += 4;
            XOR_r(reg->L); break;
        case 0xAE:
            cycle += 8;
            XOR_HL(); break;
        case 0xAF:
            cycle += 4;
            XOR_r(reg->A); break;
        case 0xEE:
            cycle += 8;
            byte = memory->readByte(reg->PC);
            XOR_n(byte);
            break;

            //OR
        case 0xB0:
            cycle += 4;
            OR_r(reg->B); break;
        case 0xB1:
            cycle += 4;
            OR_r(reg->C); break;
        case 0xB2:
            cycle += 4;
            OR_r(reg->D); break;
        case 0xB3:
            cycle += 4;
            OR_r(reg->E); break;
        case 0xB4:
            cycle += 4;
            OR_r(reg->H); break;
        case 0xB5:
            cycle += 4;
            OR_r(reg->L); break;
        case 0xB6:
            cycle += 8;
            OR_HL(); break;
        case 0xB7:
            cycle += 4;
            OR_r(reg->A); break;
        case 0xF6:
            cycle += 8;
            byte = memory->readByte(reg->PC);
            OR_n(byte);
            break;

            //CP
        case 0xB8:
            cycle += 4;
            CP_r(reg->B); break;
        case 0xB9:
            cycle += 4;
            CP_r(reg->C); break;
        case 0xBA:
            cycle += 4;
            CP_r(reg->D); break;
        case 0xBB:
            cycle += 4;
            CP_r(reg->E); break;
        case 0xBC:
            cycle += 4;
            CP_r(reg->H); break;
        case 0xBD:
            cycle += 4;
            CP_r(reg->L); break;
        case 0xBE:
            cycle += 8;
            CP_HL(); break;
        case 0xBF:
            cycle += 4;
            CP_r(reg->A); break;
        case 0xFE:
            cycle += 8;
            byte = memory->readByte(reg->PC);
            CP_n(byte);
            break;
        case 0x2F:
            cycle += 4;
            CPL();
            break;
        case 0x3F:
            cycle += 4;
            CCF();
            break;

            //INC
        case 0x04:
            cycle += 4;
            INC_r(reg->B); break;
        case 0x14:
            cycle += 4;
            INC_r(reg->D); break;
        case 0x24:
            cycle += 4;
            INC_r(reg->H); break;
        case 0x34:
            cycle += 12;
            INC_HL(); break;
        case 0x0C:
            cycle += 4;
            INC_r(reg->C); break;
        case 0x1C:
            cycle += 4;
            INC_r(reg->E); break;
        case 0x2C:
            cycle += 4;
            INC_r(reg->L); break;
        case 0x3C:
            cycle += 4;
            INC_r(reg->A); break;

            //DEC
        case 0x05:
            cycle += 4;
            DEC_r(reg->B); break;
        case 0x15:
            cycle += 4;
            DEC_r(reg->D); break;
        case 0x25:
            cycle += 4;
            DEC_r(reg->H); break;
        case 0x35:
            cycle += 12;
            DEC_HL(); break;
        case 0x0D:
            cycle += 4;
            DEC_r(reg->C); break;
        case 0x1D:
            cycle += 4;
            DEC_r(reg->E); break;
        case 0x2D:
            cycle += 4;
            DEC_r(reg->L); break;
        case 0x3D:
            cycle += 4;
            DEC_r(reg->A); break;

            //POP
        case 0xC1:
            cycle += 12;
            POP_rr(reg->B, reg->C); break;
        case 0xD1:
            cycle += 12;
            POP_rr(reg->D, reg->E); break;
        case 0xE1:
            cycle += 12;
            POP_rr(reg->H, reg->L); break;
        case 0xF1:
            cycle += 12;
            POP_rf(reg->A, flags->F); break;

            //PUSH
        case 0xC5:
            cycle += 16;
            PUSH_rr(reg->BC()); break;
        case 0xD5:
            cycle += 16;
            PUSH_rr(reg->DE()); break;
        case 0xE5:
            cycle += 16;
            PUSH_rr(reg->HL()); break;
        case 0xF5:
            cycle += 16;
            word = static_cast<uint16_t>((reg->A << 8) | flags->F);
            PUSH_rr(word);
            break;

            //LD 16-Bit
        case 0x01:
            cycle += 12;
            word = memory->readWord(reg->PC);
            reg->PC++;
            LD_rr_nn(reg->B, reg->C, word);
            break;
        case 0x11:
            cycle += 12;
            word = memory->readWord(reg->PC);
            reg->PC++;
            LD_rr_nn(reg->D, reg->E, word);
            break;
        case 0x21:
            cycle += 12;
            word = memory->readWord(reg->PC);
            reg->PC++;
            LD_rr_nn(reg->H, reg->L, word);
            break;
        case 0x31:
            cycle += 12;
            word = memory->readWord(reg->PC);
            reg->PC++;
            LD_rr_nn(reg->SP, word);
            break;
        case 0x08:
            cycle += 20;
            word = memory->readWord(reg->PC);
            reg->PC++;
            LD_nn_SP(word);
            break;
        case 0xF8:
            cycle += 12;
            word = memory->readWord(reg->PC);
            reg->PC++;
            LD_HL_SP_dd(word);
            break;
        case 0xF9:
            cycle += 8;
            LD_SP_HL(); break;

            //DEC 16-Bit
        case 0x0B:
            cycle += 8;
            DEC_rr(reg->B, reg->C); break;
        case 0x1B:
            cycle += 8;
            DEC_rr(reg->D, reg->E); break;
        case 0x2B:
            cycle += 8;
            DEC_rr(reg->H, reg->L); break;
        case 0x3B:
            cycle += 8;
            DEC_rr(reg->SP); break;

            //INC 16-Bit
        case 0x03:
            cycle += 8;
            INC_rr(reg->B, reg->C); break;
        case 0x13:
            cycle += 8;
            INC_rr(reg->D, reg->E); break;
        case 0x23:
            cycle += 8;
            INC_rr(reg->H, reg->L); break;
        case 0x33:
            cycle += 8;
            INC_rr(reg->SP); break;

            //DAA
        case 0x27:
            cycle += 4;
            DAA(); break;

            //SCF
        case 0x37:
            cycle += 4;
            SCF(); break;

            //JR
        case 0x20:
            condition = !(flags->Z());
            cycle += condition ? 12 : 8;
            word = memory->readWord(reg->PC);
            reg->PC++;
            JR_f_PC_dd(condition, word);
            break;
        case 0x30:
            condition = !(flags->C());
            cycle += condition ? 12 : 8;
            word = memory->readWord(reg->PC);
            reg->PC++;
            JR_f_PC_dd(condition, word);
            break;
        case 0x18:
            cycle += 12;
            word = memory->readWord(reg->PC);
            reg->PC++;
            JR_PC_dd(word);
            break;
        case 0x28:
            condition = flags->Z();
            cycle += condition ? 12 : 8;
            word = memory->readWord(reg->PC);
            reg->PC++;
            JR_f_PC_dd(condition, word);
            break;
        case 0x38:
            condition = flags->C();
            cycle += condition ? 12 : 8;
            word = memory->readWord(reg->PC);
            reg->PC++;
            JR_f_PC_dd(condition, word);
            break;

            //RET
        case 0xC0:
            condition = !flags->Z();
            cycle += condition ? 20 : 8;
            RET_f(condition); break;
        case 0xD0:
            condition = !flags->C();
            cycle += condition ? 20 : 8;
            RET_f(condition); break;
        case 0xC9:
            cycle += 16;
            RET(); break;
        case 0xD9:
            cycle += 16;
            RETI(); break;
        case 0xC8:
            condition = flags->Z();
            cycle += condition ? 20 : 8;
            RET_f(condition);
            break;
        case 0xD8:
            condition = flags->Z();
            cycle += condition ? 20 : 8;
            RET_f(condition);
            break;

            //JP
        case 0xC2:
            condition = !flags->Z();
            cycle += condition ? 16 : 12;
            word = memory->readWord(reg->PC);
            reg->PC++;
            JP_f_nn(condition, word);
            break;
        case 0xD2:
            condition = !flags->C();
            cycle += condition ? 16 : 12;
            word = memory->readWord(reg->PC);
            reg->PC++;
            JP_f_nn(condition, word);
            break;
        case 0xCA:
            condition = flags->Z();
            cycle += condition ? 16 : 12;
            word = memory->readWord(reg->PC);
            reg->PC++;
            JP_f_nn(condition, word);
            break;
        case 0xDA:
            condition = flags->C();
            cycle += condition ? 16 : 12;
            word = memory->readWord(reg->PC);
            reg->PC++;
            JP_f_nn(condition, word);
            break;
        case 0xC3:
            cycle += 16;
            word = memory->readWord(reg->PC);
            reg->PC++;
            JP_nn(word);
            break;
        case 0xE9:
            cycle += 4;
            JP_HL();
            break;

            //CALL
        case 0xC4:
            condition = !flags->Z();
            cycle += condition ? 24 : 12;
            word = memory->readWord(reg->PC);
            reg->PC++;
            CALL_f_nn(condition, word);
            break;
        case 0xD4:
            condition = !flags->C();
            cycle += condition ? 24 : 12;
            word = memory->readWord(reg->PC);
            reg->PC++;
            CALL_f_nn(condition, word);
            break;
        case 0xCC:
            condition = flags->Z();
            cycle += condition ? 24 : 12;
            word = memory->readWord(reg->PC);
            reg->PC++;
            CALL_f_nn(condition, word);
            break;
        case 0xDC:
            condition = flags->C();
            cycle += condition ? 24 : 12;
            word = memory->readWord(reg->PC);
            reg->PC++;
            CALL_f_nn(condition, word);
            break;
        case 0xCD:
            cycle += 24;
            word = memory->readWord(reg->PC);
            reg->PC++;
            CALL_nn(word);
            break;

            //RST
        case 0xC7:
            cycle += 16;
            RST_n(0x00); break;
        case 0xD7:
            cycle += 16;
            RST_n(0x10); break;
        case 0xE7:
            cycle += 16;
            RST_n(0x20); break;
        case 0xF7:
            cycle += 16;
            RST_n(0x30); break;
        case 0xCF:
            cycle += 16;
            RST_n(0x80); break;
        case 0xDF:
            cycle += 16;
            RST_n(0x18); break;
        case 0xEF:
            cycle += 16;
            RST_n(0x28); break;
        case 0xFF:
            cycle += 16;
            RST_n(0x38); break;

            //ADD 16-Bit
        case 0x09:
            cycle += 8;
            ADD_HL_rr(reg->B, reg->C); break;
        case 0x19:
            cycle += 8;
            ADD_HL_rr(reg->D, reg->E); break;
        case 0x29:
            cycle += 8;
            ADD_HL_rr(reg->H, reg->L); break;
        case 0x39:
            cycle += 8;
            ADD_HL_rr(reg->SP); break;
        case 0xE8:
            cycle += 16;
            word = memory->readWord(reg->PC);
            reg->PC++;
            ADD_SP_dd(word);
            break;

            //SHIFT
        case 0x07:
            cycle += 4;
            RLCA();
            break;
        case 0x17:
            cycle += 4;
            RLA();
            break;
        case 0x0F:
            cycle += 4;
            RRCA();
            break;
        case 0x1F:
            cycle += 4;
            RRA();
            break;

        default: std::cout << opcode << std::endl; break;
    }
    reg->PC++;
    return cycle;
}


uint8_t CPU::prefixOpCode(uint8_t opcode) {
    uint8_t cycle = 0;
    switch (opcode) {
        //RLC
        case 0x00:
            cycle += 8;
            RLC_r(reg->B); break;
        case 0x01:
            cycle += 8;
            RLC_r(reg->C); break;
        case 0x02:
            cycle += 8;
            RLC_r(reg->D); break;
        case 0x03:
            cycle += 8;
            RLC_r(reg->E); break;
        case 0x04:
            cycle += 8;
            RLC_r(reg->H); break;
        case 0x05:
            cycle += 8;
            RLC_r(reg->L); break;
        case 0x06:
            cycle += 8;
            RLC_HL(); break;
        case 0x07:
            cycle += 8;
            RLCA(); break;

            //RRC
        case 0x08:
            cycle += 8;
            RRC_r(reg->B); break;
        case 0x09:
            cycle += 8;
            RRC_r(reg->C); break;
        case 0x0A:
            cycle += 8;
            RRC_r(reg->D); break;
        case 0x0B:
            cycle += 8;
            RRC_r(reg->E); break;
        case 0x0C:
            cycle += 8;
            RRC_r(reg->H); break;
        case 0x0D:
            cycle += 8;
            RRC_r(reg->L); break;
        case 0x0E:
            cycle += 8;
            RRC_HL(); break;
        case 0x0F:
            cycle += 8;
            RRCA(); break;

            //RL
        case 0x10:
            cycle += 8;
            RL_r(reg->B); break;
        case 0x11:
            cycle += 8;
            RL_r(reg->C); break;
        case 0x12:
            cycle += 8;
            RL_r(reg->D); break;
        case 0x13:
            cycle += 8;
            RL_r(reg->E); break;
        case 0x14:
            cycle += 8;
            RL_r(reg->H); break;
        case 0x15:
            cycle += 8;
            RL_r(reg->L); break;
        case 0x16:
            cycle += 8;
            RL_HL(); break;
        case 0x17:
            cycle += 8;
            RLA(); break;

            //RR
        case 0x18:
            cycle += 8;
            RR_r(reg->B); break;
        case 0x19:
            cycle += 8;
            RR_r(reg->C); break;
        case 0x1A:
            cycle += 8;
            RR_r(reg->D); break;
        case 0x1B:
            cycle += 8;
            RR_r(reg->E); break;
        case 0x1C:
            cycle += 8;
            RR_r(reg->H); break;
        case 0x1D:
            cycle += 8;
            RR_r(reg->L); break;
        case 0x1E:
            cycle += 8;
            RR_HL(); break;
        case 0x1F:
            cycle += 8;
            RRA(); break;

            //SLA
        case 0x20:
            cycle += 8;
            SLA_r(reg->B); break;
        case 0x21:
            cycle += 8;
            SLA_r(reg->C); break;
        case 0x22:
            cycle += 8;
            SLA_r(reg->D); break;
        case 0x23:
            cycle += 8;
            SLA_r(reg->E); break;
        case 0x24:
            cycle += 8;
            SLA_r(reg->H); break;
        case 0x25:
            cycle += 8;
            SLA_r(reg->L); break;
        case 0x26:
            cycle += 8;
            SLA_HL(); break;
        case 0x27:
            cycle += 8;
            SLA_r(reg->A); break;

            //SRA
        case 0x28:
            cycle += 8;
            SRA_r(reg->B); break;
        case 0x29:
            cycle += 8;
            SRA_r(reg->C); break;
        case 0x2A:
            cycle += 8;
            SRA_r(reg->D); break;
        case 0x2B:
            cycle += 8;
            SRA_r(reg->E); break;
        case 0x2C:
            cycle += 8;
            SRA_r(reg->H); break;
        case 0x2D:
            cycle += 8;
            SRA_r(reg->L); break;
        case 0x2E:
            cycle += 8;
            SRA_HL(); break;
        case 0x2F:
            cycle += 8;
            SRA_r(reg->A); break;

            //SWAP
        case 0x30:
            cycle += 8;
            SWAP_r(reg->B); break;
        case 0x31:
            cycle += 8;
            SWAP_r(reg->C); break;
        case 0x32:
            cycle += 8;
            SWAP_r(reg->D); break;
        case 0x33:
            cycle += 8;
            SWAP_r(reg->E); break;
        case 0x34:
            cycle += 8;
            SWAP_r(reg->H); break;
        case 0x35:
            cycle += 8;
            SWAP_r(reg->L); break;
        case 0x36:
            cycle += 8;
            SWAP_HL(); break;
        case 0x37:
            cycle += 8;
            SWAP_r(reg->A); break;

            //SRL
        case 0x38:
            cycle += 8;
            SRL_r(reg->B); break;
        case 0x39:
            cycle += 8;
            SRL_r(reg->C); break;
        case 0x3A:
            cycle += 8;
            SRL_r(reg->D); break;
        case 0x3B:
            cycle += 8;
            SRL_r(reg->E); break;
        case 0x3C:
            cycle += 8;
            SRL_r(reg->H); break;
        case 0x3D:
            cycle += 8;
            SRL_r(reg->L); break;
        case 0x3E:
            cycle += 8;
            SRL_HL(); break;
        case 0x3F:
            cycle += 8;
            SRL_r(reg->A); break;

            //BIT 0
        case 0x40:
            cycle += 8;
            BIT_n_r(0, reg->B); break;
        case 0x41:
            cycle += 8;
            BIT_n_r(0, reg->C); break;
        case 0x42:
            cycle += 8;
            BIT_n_r(0, reg->D); break;
        case 0x43:
            cycle += 8;
            BIT_n_r(0, reg->E); break;
        case 0x44:
            cycle += 8;
            BIT_n_r(0, reg->H); break;
        case 0x45:
            cycle += 8;
            BIT_n_r(0, reg->L); break;
        case 0x46:
            cycle += 8;
            BIT_n_HL(0); break;
        case 0x47:
            cycle += 8;
            BIT_n_r(1, reg->A); break;

            //BIT 1
        case 0x48:
            cycle += 8;
            BIT_n_r(1, reg->B); break;
        case 0x49:
            cycle += 8;
            BIT_n_r(1, reg->C); break;
        case 0x4A:
            cycle += 8;
            BIT_n_r(1, reg->D); break;
        case 0x4B:
            cycle += 8;
            BIT_n_r(1, reg->E); break;
        case 0x4C:
            cycle += 8;
            BIT_n_r(1, reg->H); break;
        case 0x4D:
            cycle += 8;
            BIT_n_r(1, reg->L); break;
        case 0x4E:
            cycle += 8;
            BIT_n_HL(1); break;
        case 0x4F:
            cycle += 8;
            BIT_n_r(1, reg->A); break;

            //BIT 2
        case 0x50:
            cycle += 8;
            BIT_n_r(2, reg->B); break;
        case 0x51:
            cycle += 8;
            BIT_n_r(2, reg->C); break;
        case 0x52:
            cycle += 8;
            BIT_n_r(2, reg->D); break;
        case 0x53:
            cycle += 8;
            BIT_n_r(2, reg->E); break;
        case 0x54:
            cycle += 8;
            BIT_n_r(2, reg->H); break;
        case 0x55:
            cycle += 8;
            BIT_n_r(2, reg->L); break;
        case 0x56:
            cycle += 8;
            BIT_n_HL(2); break;
        case 0x57:
            cycle += 8;
            BIT_n_r(2, reg->A); break;

            //BIT 3
        case 0x58:
            cycle += 8;
            BIT_n_r(3, reg->B); break;
        case 0x59:
            cycle += 8;
            BIT_n_r(3, reg->C); break;
        case 0x5A:
            cycle += 8;
            BIT_n_r(3, reg->D); break;
        case 0x5B:
            cycle += 8;
            BIT_n_r(3, reg->E); break;
        case 0x5C:
            cycle += 8;
            BIT_n_r(3, reg->H); break;
        case 0x5D:
            cycle += 8;
            BIT_n_r(3, reg->L); break;
        case 0x5E:
            cycle += 8;
            BIT_n_HL(3); break;
        case 0x5F:
            cycle += 8;
            BIT_n_r(3, reg->A); break;

            //BIT 4
        case 0x60:
            cycle += 8;
            BIT_n_r(4, reg->B); break;
        case 0x61:
            cycle += 8;
            BIT_n_r(4, reg->C); break;
        case 0x62:
            cycle += 8;
            BIT_n_r(4, reg->D); break;
        case 0x63:
            cycle += 8;
            BIT_n_r(4, reg->E); break;
        case 0x64:
            cycle += 8;
            BIT_n_r(4, reg->H); break;
        case 0x65:
            cycle += 8;
            BIT_n_r(4, reg->L); break;
        case 0x66:
            cycle += 8;
            BIT_n_HL(4); break;
        case 0x67:
            cycle += 8;
            BIT_n_r(4, reg->A); break;

            //BIT 5
        case 0x68:
            cycle += 8;
            BIT_n_r(5, reg->B); break;
        case 0x69:
            cycle += 8;
            BIT_n_r(5, reg->C); break;
        case 0x6A:
            cycle += 8;
            BIT_n_r(5, reg->D); break;
        case 0x6B:
            cycle += 8;
            BIT_n_r(5, reg->E); break;
        case 0x6C:
            cycle += 8;
            BIT_n_r(5, reg->H); break;
        case 0x6D:
            cycle += 8;
            BIT_n_r(5, reg->L); break;
        case 0x6E:
            cycle += 8;
            BIT_n_HL(5); break;
        case 0x6F:
            cycle += 8;
            BIT_n_r(5, reg->A); break;

            //BIT 6
        case 0x70:
            cycle += 8;
            BIT_n_r(6, reg->B); break;
        case 0x71:
            cycle += 8;
            BIT_n_r(6, reg->C); break;
        case 0x72:
            cycle += 8;
            BIT_n_r(6, reg->D); break;
        case 0x73:
            cycle += 8;
            BIT_n_r(6, reg->E); break;
        case 0x74:
            cycle += 8;
            BIT_n_r(6, reg->H); break;
        case 0x75:
            cycle += 8;
            BIT_n_r(6, reg->L); break;
        case 0x76:
            cycle += 8;
            BIT_n_HL(6); break;
        case 0x77:
            cycle += 8;
            BIT_n_r(6, reg->A); break;

            //BIT 7
        case 0x78:
            cycle += 8;
            BIT_n_r(7, reg->B); break;
        case 0x79:
            cycle += 8;
            BIT_n_r(7, reg->C); break;
        case 0x7A:
            cycle += 8;
            BIT_n_r(7, reg->D); break;
        case 0x7B:
            cycle += 8;
            BIT_n_r(7, reg->E); break;
        case 0x7C:
            cycle += 8;
            BIT_n_r(7, reg->H); break;
        case 0x7D:
            cycle += 8;
            BIT_n_r(7, reg->L); break;
        case 0x7E:
            cycle += 8;
            BIT_n_HL(7); break;
        case 0x7F:
            cycle += 8;
            BIT_n_r(7, reg->A); break;

            //RES 0
        case 0x80:
            cycle += 8;
            RES_n_r(0, reg->B); break;
        case 0x81:
            cycle += 8;
            RES_n_r(0, reg->C); break;
        case 0x82:
            cycle += 8;
            RES_n_r(0, reg->D); break;
        case 0x83:
            cycle += 8;
            RES_n_r(0, reg->E); break;
        case 0x84:
            cycle += 8;
            RES_n_r(0, reg->H); break;
        case 0x85:
            cycle += 8;
            RES_n_r(0, reg->L); break;
        case 0x86:
            cycle += 8;
            RES_n_HL(0); break;
        case 0x87:
            cycle += 8;
            RES_n_r(0, reg->A); break;

            //RES 1
        case 0x88:
            cycle += 8;
            RES_n_r(1, reg->B); break;
        case 0x89:
            cycle += 8;
            RES_n_r(1, reg->C); break;
        case 0x8A:
            cycle += 8;
            RES_n_r(1, reg->D); break;
        case 0x8B:
            cycle += 8;
            RES_n_r(1, reg->E); break;
        case 0x8C:
            cycle += 8;
            RES_n_r(1, reg->H); break;
        case 0x8D:
            cycle += 8;
            RES_n_r(1, reg->L); break;
        case 0x8E:
            cycle += 8;
            RES_n_HL(1); break;
        case 0x8F:
            cycle += 8;
            RES_n_r(1, reg->A); break;

            //RES 2
        case 0x90:
            cycle += 8;
            RES_n_r(2, reg->B); break;
        case 0x91:
            cycle += 8;
            RES_n_r(2, reg->C); break;
        case 0x92:
            cycle += 8;
            RES_n_r(2, reg->D); break;
        case 0x93:
            cycle += 8;
            RES_n_r(2, reg->E); break;
        case 0x94:
            cycle += 8;
            RES_n_r(2, reg->H); break;
        case 0x95:
            cycle += 8;
            RES_n_r(2, reg->L); break;
        case 0x96:
            cycle += 8;
            RES_n_HL(2); break;
        case 0x97:
            cycle += 8;
            RES_n_r(2, reg->A); break;

            //RES 3
        case 0x98:
            cycle += 8;
            RES_n_r(3, reg->B); break;
        case 0x99:
            cycle += 8;
            RES_n_r(3, reg->C); break;
        case 0x9A:
            cycle += 8;
            RES_n_r(3, reg->D); break;
        case 0x9B:
            cycle += 8;
            RES_n_r(3, reg->E); break;
        case 0x9C:
            cycle += 8;
            RES_n_r(3, reg->H); break;
        case 0x9D:
            cycle += 8;
            RES_n_r(3, reg->L); break;
        case 0x9E:
            cycle += 8;
            RES_n_HL(3); break;
        case 0x9F:
            cycle += 8;
            RES_n_r(3, reg->A); break;

            //RES 4
        case 0xA0:
            cycle += 8;
            RES_n_r(4, reg->B); break;
        case 0xA1:
            cycle += 8;
            RES_n_r(4, reg->C); break;
        case 0xA2:
            cycle += 8;
            RES_n_r(4, reg->D); break;
        case 0xA3:
            cycle += 8;
            RES_n_r(4, reg->E); break;
        case 0xA4:
            cycle += 8;
            RES_n_r(4, reg->H); break;
        case 0xA5:
            cycle += 8;
            RES_n_r(4, reg->L); break;
        case 0xA6:
            cycle += 8;
            RES_n_HL(4); break;
        case 0xA7:
            cycle += 8;
            RES_n_r(4, reg->A); break;

            //RES 5
        case 0xA8:
            cycle += 8;
            RES_n_r(5, reg->B); break;
        case 0xA9:
            cycle += 8;
            RES_n_r(5, reg->C); break;
        case 0xAA:
            cycle += 8;
            RES_n_r(5, reg->D); break;
        case 0xAB:
            cycle += 8;
            RES_n_r(5, reg->E); break;
        case 0xAC:
            cycle += 8;
            RES_n_r(5, reg->H); break;
        case 0xAD:
            cycle += 8;
            RES_n_r(5, reg->L); break;
        case 0xAE:
            cycle += 8;
            RES_n_HL(5); break;
        case 0xAF:
            cycle += 8;
            RES_n_r(5, reg->A); break;

            //RES 6
        case 0xB0:
            cycle += 8;
            RES_n_r(6, reg->B); break;
        case 0xB1:
            cycle += 8;
            RES_n_r(6, reg->C); break;
        case 0xB2:
            cycle += 8;
            RES_n_r(6, reg->D); break;
        case 0xB3:
            cycle += 8;
            RES_n_r(6, reg->E); break;
        case 0xB4:
            cycle += 8;
            RES_n_r(6, reg->H); break;
        case 0xB5:
            cycle += 8;
            RES_n_r(6, reg->L); break;
        case 0xB6:
            cycle += 8;
            RES_n_HL(6); break;
        case 0xB7:
            cycle += 8;
            RES_n_r(6, reg->A); break;

            //RES 7
        case 0xB8:
            cycle += 8;
            RES_n_r(7, reg->B); break;
        case 0xB9:
            cycle += 8;
            RES_n_r(7, reg->C); break;
        case 0xBA:
            cycle += 8;
            RES_n_r(7, reg->D); break;
        case 0xBB:
            cycle += 8;
            RES_n_r(7, reg->E); break;
        case 0xBC:
            cycle += 8;
            RES_n_r(7, reg->H); break;
        case 0xBD:
            cycle += 8;
            RES_n_r(7, reg->L); break;
        case 0xBE:
            cycle += 8;
            RES_n_HL(7); break;
        case 0xBF:
            cycle += 8;
            RES_n_r(7, reg->A); break;

            //SET 0
        case 0xC0:
            cycle += 8;
            SET_n_r(0, reg->B); break;
        case 0xC1:
            cycle += 8;
            SET_n_r(0, reg->C); break;
        case 0xC2:
            cycle += 8;
            SET_n_r(0, reg->D); break;
        case 0xC3:
            cycle += 8;
            SET_n_r(0, reg->E); break;
        case 0xC4:
            cycle += 8;
            SET_n_r(0, reg->H); break;
        case 0xC5:
            cycle += 8;
            SET_n_r(0, reg->L); break;
        case 0xC6:
            cycle += 8;
            SET_n_HL(0); break;
        case 0xC7:
            cycle += 8;
            SET_n_r(0, reg->A); break;

            //SET 1
        case 0xC8:
            cycle += 8;
            SET_n_r(1, reg->B); break;
        case 0xC9:
            cycle += 8;
            SET_n_r(1, reg->C); break;
        case 0xCA:
            cycle += 8;
            SET_n_r(1, reg->D); break;
        case 0xCB:
            cycle += 8;
            SET_n_r(1, reg->E); break;
        case 0xCC:
            cycle += 8;
            SET_n_r(1, reg->H); break;
        case 0xCD:
            cycle += 8;
            SET_n_r(1, reg->L); break;
        case 0xCE:
            cycle += 8;
            SET_n_HL(1); break;
        case 0xCF:
            cycle += 8;
            SET_n_r(1, reg->A); break;

            //SET 2
        case 0xD0:
            cycle += 8;
            SET_n_r(2, reg->B); break;
        case 0xD1:
            cycle += 8;
            SET_n_r(2, reg->C); break;
        case 0xD2:
            cycle += 8;
            SET_n_r(2, reg->D); break;
        case 0xD3:
            cycle += 8;
            SET_n_r(2, reg->E); break;
        case 0xD4:
            cycle += 8;
            SET_n_r(2, reg->H); break;
        case 0xD5:
            cycle += 8;
            SET_n_r(2, reg->L); break;
        case 0xD6:
            cycle += 8;
            SET_n_HL(2); break;
        case 0xD7:
            cycle += 8;
            SET_n_r(2, reg->A); break;

            //SET 3
        case 0xD8:
            cycle += 8;
            SET_n_r(3, reg->B); break;
        case 0xD9:
            cycle += 8;
            SET_n_r(3, reg->C); break;
        case 0xDA:
            cycle += 8;
            SET_n_r(3, reg->D); break;
        case 0xDB:
            cycle += 8;
            SET_n_r(3, reg->E); break;
        case 0xDC:
            cycle += 8;
            SET_n_r(3, reg->H); break;
        case 0xDD:
            cycle += 8;
            SET_n_r(3, reg->L); break;
        case 0xDE:
            cycle += 8;
            SET_n_HL(3); break;
        case 0xDF:
            cycle += 8;
            SET_n_r(3, reg->A); break;

            //SET 4
        case 0xE0:
            cycle += 8;
            SET_n_r(4, reg->B); break;
        case 0xE1:
            cycle += 8;
            SET_n_r(4, reg->C); break;
        case 0xE2:
            cycle += 8;
            SET_n_r(4, reg->D); break;
        case 0xE3:
            cycle += 8;
            SET_n_r(4, reg->E); break;
        case 0xE4:
            cycle += 8;
            SET_n_r(4, reg->H); break;
        case 0xE5:
            cycle += 8;
            SET_n_r(4, reg->L); break;
        case 0xE6:
            cycle += 8;
            SET_n_HL(4); break;
        case 0xE7:
            cycle += 8;
            SET_n_r(4, reg->A); break;

            //SET 5
        case 0xE8:
            cycle += 8;
            SET_n_r(5, reg->B); break;
        case 0xE9:
            cycle += 8;
            SET_n_r(5, reg->C); break;
        case 0xEA:
            cycle += 8;
            SET_n_r(5, reg->D); break;
        case 0xEB:
            cycle += 8;
            SET_n_r(5, reg->E); break;
        case 0xEC:
            cycle += 8;
            SET_n_r(5, reg->H); break;
        case 0xED:
            cycle += 8;
            SET_n_r(5, reg->L); break;
        case 0xEE:
            cycle += 8;
            SET_n_HL(5); break;
        case 0xEF:
            cycle += 8;
            SET_n_r(5, reg->A); break;

            //SET 6
        case 0xF0:
            cycle += 8;
            SET_n_r(6, reg->B); break;
        case 0xF1:
            cycle += 8;
            SET_n_r(6, reg->C); break;
        case 0xF2:
            cycle += 8;
            SET_n_r(6, reg->D); break;
        case 0xF3:
            cycle += 8;
            SET_n_r(6, reg->E); break;
        case 0xF4:
            cycle += 8;
            SET_n_r(6, reg->H); break;
        case 0xF5:
            cycle += 8;
            SET_n_r(6, reg->L); break;
        case 0xF6:
            cycle += 8;
            SET_n_HL(6); break;
        case 0xF7:
            cycle += 8;
            SET_n_r(6, reg->A); break;

            //SET 7
        case 0xF8:
            cycle += 8;
            SET_n_r(7, reg->B); break;
        case 0xF9:
            cycle += 8;
            SET_n_r(7, reg->C); break;
        case 0xFA:
            cycle += 8;
            SET_n_r(7, reg->D); break;
        case 0xFB:
            cycle += 8;
            SET_n_r(7, reg->E); break;
        case 0xFC:
            cycle += 8;
            SET_n_r(7, reg->H); break;
        case 0xFD:
            cycle += 8;
            SET_n_r(7, reg->L); break;
        case 0xFE:
            cycle += 8;
            SET_n_HL(7); break;
        case 0xFF:
            cycle += 8;
            SET_n_r(7, reg->A); break;
    }
    return cycle;
}