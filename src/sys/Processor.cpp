#include "Processor.h"

Processor::Processor()
{
	memory = new Memory();
	cpu = new CPU(memory);
	ppu = new Graphics(memory);
	apu = new Audio();
}

Processor::~Processor()
{
	delete apu;
	delete ppu;
	delete cpu;
	delete memory;
}