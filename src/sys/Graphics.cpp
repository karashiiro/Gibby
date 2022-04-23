#include "Graphics.h"

Graphics::Graphics(lcd_registers &mapped_registers, unsigned char* external_memory) : registers(mapped_registers)
{
	vram = external_memory;
}
