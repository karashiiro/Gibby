#pragma once

#include "cpu_registers.h"

class CPU
{
public:
	explicit CPU(interrupt_register &mapped_register, unsigned char *external_memory);
private:
	register_set registers{};
	flag_register flags{};
	interrupt_register &interrupts;

	unsigned char *memory;
};
