#include "Processor.h"

Processor::Processor()
{
	clock = new Clock();
	memory = new Memory(clock);
	cpu = new CPU(clock, *(interrupt_register *)(void *)(memory->mem + 0xFFFF), memory);
	timer = new Timer(*(timer_registers *)(void *)(memory->mem + 0xFF05));
	ppu = new Graphics(*(lcd_registers *)(void *)(memory->mem + 0xFF40), memory->mem + 0x8000);
	apu = new Audio(
			*(sound_mode_1_registers *)(void *)(memory->mem + 0xFF12),
			*(sound_mode_2_registers *)(void *)(memory->mem + 0xFF16),
			*(sound_mode_3_registers *)(void *)(memory->mem + 0xFF1A),
			*(sound_mode_4_registers *)(void *)(memory->mem + 0xFF20),
			*(sound_control_registers *)(void *)(memory->mem + 0xFF24),
			*(wave_sample_memory *)(void *)(memory->mem + 0xFF30));
}

Processor::~Processor()
{
	delete apu;
	delete ppu;
	delete timer;
	delete cpu;
	delete memory;
	delete clock;
}