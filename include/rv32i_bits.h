#pragma once
#include <cstdint>

// Register fields
inline uint32_t rd(uint32_t inst) {
    return (inst >> 7) & 0x1F;
}

inline uint32_t rs1(uint32_t inst) {
    return (inst >> 15) & 0x1F;
}

inline uint32_t rs2(uint32_t inst) {
    return (inst >> 20) & 0x1F;
}

// Immediate fields
inline int32_t imm_i(uint32_t inst) {
    return (int32_t)inst >> 20;
}

inline int32_t imm_s(uint32_t inst) {
    return ((inst >> 7) & 0x1F) |
           (((int32_t)inst >> 25) << 5);
}
