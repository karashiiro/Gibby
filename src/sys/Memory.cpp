#include "Memory.h"

Memory::Memory()
{
	mem = new unsigned char[0x10000];
}

Memory::~Memory()
{
	delete[] mem;
}

unsigned char* Memory::GetMemory()
{
	return mem;
}