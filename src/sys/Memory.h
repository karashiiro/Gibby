#pragma once

class Memory
{
public:
	Memory();
	virtual ~Memory();

	unsigned char* GetMemory();
	unsigned char* GetVideoMemory();
private:
	/*
	 * The SM83 only has 8KB of onboard RAM, but its memory
	 * bus gives access to 64KB of RAM in total. Rather than
	 * replicating the memory bus functionality in code, I'm
	 * just pretending it's all a contiguous block (as it
	 * appears to the CPU).
	 */
	unsigned char *mem;
};
