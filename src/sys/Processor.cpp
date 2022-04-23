#include "Processor.h"

Processor::Processor()
{
	memory = new Memory();
	cpu = new CPU(memory);
}

Processor::~Processor()
{
	delete cpu;
	delete memory;
}