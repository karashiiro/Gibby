#pragma once

#include "Clock.h"

class Memory
{
	// Used for casting references over regions of memory for
	// mapped sections that would normally be in other devices
	friend class Processor;
public:
	explicit Memory(Clock *external_clock);
	virtual ~Memory();

	unsigned char ReadByte(unsigned short p);
	unsigned char& ReadByteRef(unsigned short p);
	void WriteByte(unsigned short p, unsigned char v);
private:
	/*
	 * The SM83 only has 8KB of onboard RAM, but its memory
	 * bus gives access to 64KB of RAM in total. Rather than
	 * replicating the memory bus functionality in code, I'm
	 * just pretending it's all a contiguous block (as it
	 * appears to the CPU).
	 */
	unsigned char *mem;

	Clock *clock;
};
