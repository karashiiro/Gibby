#pragma once

#include "registers.h"
#include "Memory.h"

class CPU
{
public:
	explicit CPU(Memory *external_memory);
private:
	register_set registers{};
	flag_register flags{};

	Memory *memory;
};
