#pragma once
#include "memory.h"
#include <cstdint>

struct CPU {
    Memory& memory;

    uint32_t pc = 0;
    uint32_t regs[32] = {0};

    bool halted = false;   // ✅ belongs to CPU

    CPU(Memory& mem);

    uint32_t fetch();
    void execute(uint32_t inst);
    void step();
    void dump_regs() const;

    void load_elf(uint32_t entry) {
        pc = entry;
        halted = false;
    }
};
