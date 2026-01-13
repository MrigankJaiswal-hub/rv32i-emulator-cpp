# RV32IM Emulator in C++ (Windows)

A lightweight educational RISC-V RV32IM CPU emulator written in modern C++,
designed and tested on Windows using MinGW-w64.

## Supported Features
- RV32I base integer instruction set
- RV32M extension (MUL, DIV)
- ELF32 loader
- Instruction trace & disassembler
- Register-level execution
- Spike-compatible execution model

## Architecture

```mermaid
flowchart LR
    PC --> Fetch
    Fetch --> Decode
    Decode --> Execute
    Execute --> Writeback
    Writeback --> PC
# RV32IM Emulator in C++ (Windows)

A lightweight educational RISC-V RV32IM CPU emulator written in modern C++,
designed and tested on Windows using MinGW-w64.

## Supported Features
- RV32I base integer instruction set
- RV32M extension (MUL, DIV)
- ELF32 loader
- Instruction trace & disassembler
- Register-level execution
- Spike-compatible execution model

## Architecture

[![](https://mermaid.ink/img/pako:eNo9jc1ugzAQhF8F7ZkgDLaJfciFtKceol4qVVxcWH5UsCPXVtMi3r1g0uxp5pud3Rlq0yBIaEfzXffKuujltdLROpcyOhxO0TO6ut9JkAGecavtdNcBP92w9u7O7yYEb3Zw-KHqzz162BBeSoihs0MD0lmPMUxoJ7VZmLf9ClyPE1YgV9lgq_zoKqj0stauSr8bM_03rfFdD7JV49fq_LVRDs-D6qyaHtSibtCWxmsHsiDhBsgZbiAJL5JjIaigOWEiYymP4WfFlCc8z7koWC54mrIlht_wNU044UdGaSYySoVgZPkDvJlkzA?type=png)](https://mermaid.live/edit#pako:eNo9jc1ugzAQhF8F7ZkgDLaJfciFtKceol4qVVxcWH5UsCPXVtMi3r1g0uxp5pud3Rlq0yBIaEfzXffKuujltdLROpcyOhxO0TO6ut9JkAGecavtdNcBP92w9u7O7yYEb3Zw-KHqzz162BBeSoihs0MD0lmPMUxoJ7VZmLf9ClyPE1YgV9lgq_zoKqj0stauSr8bM_03rfFdD7JV49fq_LVRDs-D6qyaHtSibtCWxmsHsiDhBsgZbiAJL5JjIaigOWEiYymP4WfFlCc8z7koWC54mrIlht_wNU044UdGaSYySoVgZPkDvJlkzA)
