#include "CPU.h"

CPU::CPU(Clock *external_clock, interrupt_register &mapped_register, unsigned char *external_memory) : interrupts(mapped_register)
{
	clock = external_clock;
	memory = external_memory;
}

void CPU::ExecuteText(unsigned char* text)
{
}
