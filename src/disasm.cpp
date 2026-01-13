#include "disasm.h"
#include <sstream>

std::string disassemble(uint32_t inst) {
    uint32_t opcode = inst & 0x7F;
    std::stringstream ss;

    if (opcode == 0x33) {
        uint32_t funct3 = (inst >> 12) & 0x7;
        uint32_t funct7 = (inst >> 25) & 0x7F;
        if (funct7 == 0x01) {
            if (funct3 == 0x0) ss << "MUL";
            else if (funct3 == 0x4) ss << "DIV";
            else ss << "M-EXT";
        } else {
            ss << "R-TYPE";
        }
    } else {
        ss << "UNKNOWN";
    }
    return ss.str();
}
