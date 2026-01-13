#pragma once

#include <cstdint>
#include <vector>
#include <stdexcept>
#include <iostream>

constexpr uint32_t STACK_TOP = 0x80000000 + 1024*1024; // 1MB RAM top

struct Memory {
    static constexpr uint32_t BASE = 0x80000000;
    static constexpr uint32_t SIZE = 1024 * 1024; // 1MB

    std::vector<uint8_t> data;

    Memory() : data(SIZE) {}

    // Load/store helpers
    uint32_t load_word(uint32_t addr);
    void store_word(uint32_t addr, uint32_t val);

    // Optional: get raw pointer for advanced memory ops
    uint8_t* raw_ptr(uint32_t addr);
};
