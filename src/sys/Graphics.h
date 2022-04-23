#pragma once

#include "Memory.h"
class Graphics
{
public:
	explicit Graphics(Memory *external_memory);
private:
	const int MEMORY_END = 0x2000;

	unsigned char *vram;
};
