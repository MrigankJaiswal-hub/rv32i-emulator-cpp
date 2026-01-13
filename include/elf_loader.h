#pragma once
#include <string>
#include <cstdint>
#include "memory.h"

bool load_elf(const std::string& path, Memory& mem, uint32_t& entry_point);
