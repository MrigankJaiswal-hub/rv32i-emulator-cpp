#include "elf_loader.h"
#include "memory.h"   // Make sure to include Memory definitions
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdint>

// 32-bit ELF header structure
struct Elf32_Ehdr {
    unsigned char e_ident[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint32_t e_entry;
    uint32_t e_phoff;
    uint32_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
};

// 32-bit program header
struct Elf32_Phdr {
    uint32_t p_type;
    uint32_t p_offset;
    uint32_t p_vaddr;
    uint32_t p_paddr;
    uint32_t p_filesz;
    uint32_t p_memsz;
    uint32_t p_flags;
    uint32_t p_align;
};

constexpr uint32_t PT_LOAD = 1;

bool load_elf(const std::string& path, Memory& mem, uint32_t& entry_point) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open ELF file: " << path << "\n";
        return false;
    }

    Elf32_Ehdr eh{};
    file.read(reinterpret_cast<char*>(&eh), sizeof(eh));

    // Check ELF magic
    if (std::memcmp(eh.e_ident, "\x7F""ELF", 4) != 0) {
        std::cerr << "Not a valid ELF file\n";
        return false;
    }

    // Check RISC-V architecture
    if (eh.e_machine != 243) { // EM_RISCV
        std::cerr << "Not a RISC-V ELF\n";
        return false;
    }

    entry_point = eh.e_entry;

    // Iterate over program headers
    file.seekg(eh.e_phoff, std::ios::beg);
    for (int i = 0; i < eh.e_phnum; i++) {
        Elf32_Phdr ph{};
        file.read(reinterpret_cast<char*>(&ph), sizeof(ph));

        if (ph.p_type != PT_LOAD) continue;

        // Ensure segment fits in RAM
        if (ph.p_vaddr < Memory::BASE || ph.p_vaddr + ph.p_memsz > Memory::BASE + Memory::SIZE) {
           std::cerr << "Segment out of memory bounds: VA=0x"
                     << std::hex << ph.p_vaddr
                     << " size=0x" << ph.p_memsz << "\n";
           return false;
        }

        // Load segment bytes from file
        file.seekg(ph.p_offset, std::ios::beg);
        file.read(reinterpret_cast<char*>(mem.raw_ptr(ph.p_vaddr)), ph.p_filesz);

        // Zero-fill BSS if needed
        if (ph.p_memsz > ph.p_filesz) {
            std::memset(mem.raw_ptr(ph.p_vaddr + ph.p_filesz),
                        0,
                        ph.p_memsz - ph.p_filesz);
        }

        std::cout << "Loaded segment: VA=0x" << std::hex << ph.p_vaddr
                  << " size=0x" << ph.p_memsz << "\n";
    }

    std::cout << "ELF entry point: 0x" << std::hex << entry_point << "\n";
    return true;
}
