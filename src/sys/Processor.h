#pragma once

#include "registers.h"
#include "CPU.h"
#include "Memory.h"
#include "Graphics.h"
#include "Audio.h"

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
	Memory *memory;
	CPU *cpu;
	Graphics *ppu;
	Audio*apu;
};
