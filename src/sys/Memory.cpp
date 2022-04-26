#include "Memory.h"

Memory::Memory(Clock *external_clock)
{
	mem = new unsigned char[0x10000];
	clock = external_clock;
}

Memory::~Memory()
{
	delete[] mem;
}

unsigned char Memory::ReadMemory(unsigned short p)
{
	auto v = mem[p];
	clock->Wait(4);
	return v;
}

unsigned char& Memory::ReadMemoryRef(unsigned short p)
{
	auto &v = mem[p];
	clock->Wait(4);
	return v;
}

void Memory::WriteMemory(unsigned short p, unsigned char v)
{
	mem[p] = v;
	clock->Wait(4);
}