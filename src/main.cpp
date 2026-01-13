#include <iostream>
#include <iomanip>
#include "cpu.h"
#include "elf_loader.h"
#include "memory.h"

int main() {
    Memory memory;
    CPU cpu(memory);

    uint32_t entry_point = 0;

    if (!load_elf("programs/test.elf", memory, entry_point)) {
        std::cerr << "ELF load failed!\n";
        return 1;
    }

    cpu.load_elf(entry_point);

    std::cout << "Loaded ELF successfully\n";
    std::cout << "Starting CPU at PC = 0x"
              << std::hex << entry_point << std::dec << "\n";

    // Run until ECALL sets cpu.halted = true
    while (!cpu.halted) {
        cpu.step();
    }

    std::cout << "\nCPU halted. Final register state:\n";
    cpu.dump_regs();

    return 0;
}
