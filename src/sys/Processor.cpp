#include "Processor.h"

Processor::Processor()
{
	memory = new Memory();
	cpu = new CPU(memory->GetMemory());
	timer = new Timer(*(timer_registers *)(void *)(memory->GetMemory() + 0xFF05));
	ppu = new Graphics(memory->GetMemory() + 0x8000);
	apu = new Audio(
			*(sound_mode_1_registers *)(void *)(memory->GetMemory() + 0xFF12),
			*(sound_mode_2_registers *)(void *)(memory->GetMemory() + 0xFF16),
			*(sound_mode_3_registers *)(void *)(memory->GetMemory() + 0xFF1A),
			*(sound_mode_4_registers *)(void *)(memory->GetMemory() + 0xFF20),
			*(sound_control_registers *)(void *)(memory->GetMemory() + 0xFF24),
			*(wave_sample_memory *)(void *)(memory->GetMemory() + 0xFF30));
}

Processor::~Processor()
{
	delete apu;
	delete ppu;
	delete timer;
	delete cpu;
	delete memory;
}