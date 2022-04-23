#pragma once

#include "Memory.h"

struct lcd_control_register {
	unsigned char bg_window_enabled   : 1;
	unsigned char sprites_enabled     : 1;
	unsigned char sprite_size         : 1;
	unsigned char bg_tile_map         : 1;
	unsigned char bg_window_tile_data : 1;
	unsigned char window_enabled      : 1;
	unsigned char window_tile_map     : 1;
	unsigned char enabled             : 1;
};

struct lcd_status_register {
	unsigned char mode        : 2;
	unsigned char coincidence : 1;
	unsigned char interrupt_mode_0      : 1;
	unsigned char interrupt_mode_1      : 1;
	unsigned char interrupt_mode_2      : 1;
	unsigned char interrupt_coincidence : 1;
	unsigned char : 1;
};

struct lcd_palette_register {
	unsigned char dot_0 : 2;
	unsigned char dot_1 : 2;
	unsigned char dot_2 : 2;
	unsigned char dot_3 : 2;
};

struct lcd_registers {
	lcd_control_register control;
	lcd_status_register status;
	unsigned char scroll_y;
	unsigned char scroll_x;
	unsigned char lcd_y;
	unsigned char lcd_y_compare;
	unsigned char dma;
	lcd_palette_register bg_window_palette;
	lcd_palette_register obj_palette_0;
	lcd_palette_register obj_palette_1;
	unsigned char window_y;
	unsigned char window_x;
};

class Graphics
{
public:
	explicit Graphics(lcd_registers &mapped_registers, unsigned char *external_memory);
private:
	const int MEMORY_END = 0x2000;

	lcd_registers &registers;
	unsigned char *vram;
};

// Size assertions
static_assert(sizeof(lcd_control_register) == 1, "LCD control register must span 1 byte.");
static_assert(sizeof(lcd_status_register) == 1, "LCD status register must span 1 byte.");
static_assert(sizeof(lcd_palette_register) == 1, "LCD palette register must span 1 byte.");
static_assert(sizeof(lcd_registers) == 12, "Graphics registers must span 12 bytes.");