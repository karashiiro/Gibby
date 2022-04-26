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

unsigned char Memory::ReadByte(unsigned short p)
{
	auto v = mem[p];
	clock->Wait(4);
	return v;
}

unsigned char& Memory::ReadByteRef(unsigned short p)
{
	auto &v = mem[p];
	clock->Wait(4);
	return v;
}

void Memory::WriteByte(unsigned short p, unsigned char v)
{
	mem[p] = v;
	clock->Wait(4);
}