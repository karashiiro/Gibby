#include "Processor.h"

Processor::Processor()
{
	mem = new unsigned char[0xFFFF];
}

Processor::~Processor()
{
	delete[] mem;
}