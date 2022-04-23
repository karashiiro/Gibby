#pragma once

#include "cpu_registers.h"

class CPU
{
public:
	explicit CPU(unsigned char *external_memory);
private:
	register_set registers{};
	flag_register flags{};

	unsigned char *memory;
};
