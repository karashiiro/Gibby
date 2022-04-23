#pragma once

#include "cpu_registers.h"

class CPU
{
public:
	explicit CPU(interrupt_register &mapped_register, unsigned char *external_memory);
private:
	register_set registers{};
	interrupt_register &interrupts;

	unsigned char *memory;
};
