#include <sstream>
#include "decoder.h"
#include "rv32i_bits.h"

// ---------------------------
// Instruction decoder
// ---------------------------
std::string decode_inst(uint32_t inst) {
    std::ostringstream os;

    uint32_t opcode = inst & 0x7F;
    uint32_t funct3 = (inst >> 12) & 0x7;
    uint32_t funct7 = inst >> 25;

    switch(opcode) {
        // OP-IMM
        case 0x13:
            if(funct3 == 0x0) os << "addi x" << rd(inst) << ",x" << rs1(inst) << "," << imm_i(inst);
            else if(funct3 == 0x5 && funct7 == 0x20) os << "srai x" << rd(inst) << ",x" << rs1(inst) << "," << (imm_i(inst)&0x1F);
            else os << "op-imm";
            break;

        // LOAD
        case 0x03:
            if(funct3 == 0x2) os << "lw x" << rd(inst) << "," << imm_i(inst) << "(x" << rs1(inst) << ")";
            else os << "load";
            break;

        // STORE
        case 0x23:
            if(funct3 == 0x2) os << "sw x" << rs2(inst) << "," << imm_s(inst) << "(x" << rs1(inst) << ")";
            else os << "store";
            break;

        // LUI
        case 0x37:
            os << "lui x" << rd(inst) << "," << (inst & 0xFFFFF000);
            break;

        // R-TYPE (ADD, SUB, MUL, MULH)
        case 0x33:
            if(funct7 == 0x00 && funct3 == 0x0) os << "add x" << rd(inst) << ",x" << rs1(inst) << ",x" << rs2(inst);
            else if(funct7 == 0x20 && funct3 == 0x0) os << "sub x" << rd(inst) << ",x" << rs1(inst) << ",x" << rs2(inst);
            else if(funct7 == 0x01 && funct3 == 0x0) os << "mul x" << rd(inst) << ",x" << rs1(inst) << ",x" << rs2(inst);
            else if(funct7 == 0x01 && funct3 == 0x1) os << "mulh x" << rd(inst) << ",x" << rs1(inst) << ",x" << rs2(inst);
            else os << "r-type";
            break;

        // JAL
        case 0x6F:
            os << "jal x" << rd(inst) << "," << 
                  (int32_t)(((inst >> 21) & 0x3FF)<<1 |
                            ((inst >> 20)&0x1)<<11 |
                            ((inst >> 12)&0xFF)<<12 |
                            ((inst >> 31)&0x1)<<20);
            break;

        // SYSTEM (ECALL)
        case 0x73:
            if(inst == 0x00000073) os << "ecall";
            else os << "system";
            break;

        default:
            os << "unknown";
    }

    return os.str();
}
