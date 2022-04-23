#include "Memory.h"

Memory::Memory()
{
	mem = new unsigned char[0xFFFF];
}

Memory::~Memory()
{
	delete[] mem;
}

unsigned char* Memory::GetMemory()
{
	return mem;
}

unsigned char* Memory::GetVideoMemory()
{
	return mem + 0x8000;
}