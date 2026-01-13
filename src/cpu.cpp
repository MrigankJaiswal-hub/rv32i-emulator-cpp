#include "cpu.h"
#include "decoder.h"
#include <iostream>
#include <cstdint>

CPU::CPU(Memory& mem)
    : memory(mem), pc(0), halted(false) {
    for(auto &r : regs) r = 0;
    regs[2] = STACK_TOP; // sp
}

// ----------------------------
// Fetch
// ----------------------------
uint32_t CPU::fetch() {
    return memory.load_word(pc);
}

// ----------------------------
// Execute
// ----------------------------
void CPU::execute(uint32_t inst) {
    uint32_t opcode = inst & 0x7F;
    uint32_t rd     = (inst >> 7) & 0x1F;
    uint32_t funct3 = (inst >> 12) & 0x7;
    uint32_t rs1    = (inst >> 15) & 0x1F;
    uint32_t rs2    = (inst >> 20) & 0x1F;
    uint32_t funct7 = inst >> 25;

    auto sign_extend = [](uint32_t val,int bits){ return int32_t(val<<(32-bits))>>(32-bits); };

    switch(opcode) {

        // OP-IMM
        case 0x13: {
            int32_t imm = sign_extend(inst>>20,12);
            if(funct3 == 0x0) regs[rd] = regs[rs1]+imm;       // ADDI
            else if(funct3==0x5 && funct7==0x20) regs[rd] = int32_t(regs[rs1])>>(imm&0x1F); // SRAI
            else std::cerr<<"UNKNOWN OP-IMM\n";
            pc+=4;
            break;
        }

        // LOAD
        case 0x03: {
            int32_t imm = sign_extend(inst>>20,12);
            if(funct3==0x2) regs[rd] = memory.load_word(regs[rs1]+imm); // LW
            pc+=4;
            break;
        }

        // STORE
        case 0x23: {
            int32_t imm = ((inst>>7)&0x1F)|((inst>>25)<<5);
            imm = sign_extend(imm,12);
            if(funct3==0x2) memory.store_word(regs[rs1]+imm, regs[rs2]); // SW
            pc+=4;
            break;
        }

        // LUI
        case 0x37:
            regs[rd] = inst & 0xFFFFF000;
            pc+=4;
            break;

        // R-TYPE
        case 0x33: {
            if(funct7==0x01) { // M extension
                int64_t res = int64_t(int32_t(regs[rs1]))*int64_t(int32_t(regs[rs2]));
                if(funct3==0x0) regs[rd]=uint32_t(res);       // MUL
                else if(funct3==0x1) regs[rd]=uint32_t(res>>32); // MULH
            } else if(funct3==0x0 && funct7==0x20) regs[rd] = regs[rs1]-regs[rs2]; // SUB
            pc+=4;
            break;
        }

        // JAL
        case 0x6F: {
            int32_t imm = ((inst>>21)&0x3FF)<<1 |
                          ((inst>>20)&0x1)<<11 |
                          ((inst>>12)&0xFF)<<12 |
                          ((inst>>31)&0x1)<<20;
            imm = sign_extend(imm,21);
            regs[rd] = pc+4;
            pc+=imm;
            break;
        }

        // SYSTEM ECALL
        case 0x73:
            if(inst==0x00000073) { // ECALL
                uint32_t syscall = regs[17]; // a7
                if(syscall==93) { // exit
                    uint32_t code = regs[10]; // a0
                    std::cout<<"\nProgram exited with code "<<code<<"\n";
                    halted = true;
                }
            }
            pc+=4;
            break;

        default:
            std::cerr<<"UNKNOWN OPCODE 0x"<<std::hex<<opcode<<"\n";
            pc+=4;
    }

    regs[0]=0; // x0 always zero
}

// ----------------------------
// Step one instruction
// ----------------------------
void CPU::step() {
    if(halted) return;
    uint32_t inst = fetch();
    std::cout<<"PC=0x"<<std::hex<<pc<<" INST=0x"<<inst<<" "
             <<decode_inst(inst)<<"\n";
    execute(inst);
}

// ----------------------------
// Dump registers
// ----------------------------
void CPU::dump_regs() const {
    for(int i=0;i<32;i++)
        std::cout<<"x"<<i<<" = 0x"<<std::hex<<regs[i]<<"\n";
}
