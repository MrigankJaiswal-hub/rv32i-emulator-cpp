#include "memory.h"

// =========================
// Load 32-bit little-endian word
// =========================
uint32_t Memory::load_word(uint32_t addr) {
    if (addr < BASE || addr + 3 >= BASE + SIZE) {
        std::cerr << "Memory read OOB at addr 0x" << std::hex << addr << "\n";
        throw std::out_of_range("Memory read OOB");
    }

    uint32_t off = addr - BASE;
    return data[off] |
           (data[off + 1] << 8) |
           (data[off + 2] << 16) |
           (data[off + 3] << 24);
}

// =========================
// Store 32-bit little-endian word
// =========================
void Memory::store_word(uint32_t addr, uint32_t val) {
    if (addr < BASE || addr + 3 >= BASE + SIZE) {
        std::cerr << "Memory write OOB at addr 0x" << std::hex << addr << "\n";
        throw std::out_of_range("Memory write OOB");
    }

    size_t off = addr - BASE;
    data[off]     = val & 0xFF;
    data[off + 1] = (val >> 8) & 0xFF;
    data[off + 2] = (val >> 16) & 0xFF;
    data[off + 3] = (val >> 24) & 0xFF;
}

// =========================
// Raw pointer access
// =========================
uint8_t* Memory::raw_ptr(uint32_t addr) {
    if (addr < BASE || addr >= BASE + SIZE)
        throw std::out_of_range("Memory raw_ptr OOB");
    return &data[addr - BASE];
}
