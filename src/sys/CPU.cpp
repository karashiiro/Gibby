#include "CPU.h"

CPU::CPU(interrupt_register &mapped_register, unsigned char *external_memory) : interrupts(mapped_register)
{
	memory = external_memory;
}
