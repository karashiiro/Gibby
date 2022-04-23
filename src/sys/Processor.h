#pragma once

#include "registers.h"

class Processor
{
	/*
	 * A simulation of a Sharp LR35902.
	 * References:
	 * - https://www.copetti.org/writings/consoles/game-boy/
	 * - http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf
	 * - https://www.alldatasheet.com/view.jsp?sField=0&Searchword=SM83&list=142
	 */
public:
	Processor();
	virtual ~Processor();
private:
	register_set registers{};
	flag_register flags{};

	/*
	 * The SM83 only has 8KB of onboard RAM, but its memory
	 * bus gives access to 64KB of RAM in total. Rather than
	 * replicating the memory bus functionality in code, I'm
	 * just pretending it's all a contiguous block (as it
	 * appears to the CPU).
	 */
	unsigned char *mem;
};
