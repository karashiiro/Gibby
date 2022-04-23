#pragma once

// We leave the frequency registers split instead of
// merging them into a short to avoid dealing with
// field alignment.

struct sound_mode_1_registers {
	struct {
		unsigned char shift : 3;
		unsigned char inc   : 1;
		unsigned char time  : 2;
		unsigned char : 1;
	} sweep;
	unsigned char length            : 6;
	unsigned char wave_pattern_duty : 2;
	struct {
		unsigned char sweep : 3;
		unsigned char inc   : 1;
		unsigned char initial_volume : 4;
	} envelope;
	unsigned char freq_lo;
	unsigned char freq_hi      : 3;
	unsigned char counter_mode : 1;
	unsigned char restart      : 1;
};

struct sound_mode_2_registers {
	unsigned char length            : 6;
	unsigned char wave_pattern_duty : 2;
	struct {
		unsigned char sweep : 3;
		unsigned char inc   : 1;
		unsigned char initial_volume : 4;
	} envelope;
	unsigned char freq_lo;
	unsigned char freq_hi      : 3;
	unsigned char counter_mode : 1;
	unsigned char restart      : 1;
};

struct sound_mode_3_registers {
	unsigned char : 7;
	unsigned char enabled : 1;
	unsigned char length;
	unsigned char : 5;
	unsigned char output_level : 2;
	unsigned char : 1;
	unsigned char freq_lo;
	unsigned char freq_hi      : 3;
	unsigned char counter_mode : 1;
	unsigned char restart      : 1;
};

struct sound_mode_4_registers {
	unsigned char length : 6;
	struct {
		unsigned char sweep : 3;
		unsigned char inc   : 1;
		unsigned char initial_volume : 4;
	} envelope;
	struct {
		unsigned char freq       : 3;
		unsigned char step       : 1;
		unsigned char shift_freq : 4;
	} poly;
	unsigned char : 6;
	unsigned char counter_mode    : 1;
	unsigned char restart         : 1;
};

struct sound_control_registers {
	struct {
		unsigned char so1_volume      : 3;
		unsigned char vin_so1_enabled : 1;
		unsigned char so2_volume      : 3;
		unsigned char vin_so2_enabled : 1;
	} channel_control;
	struct {
		unsigned char sound_1_so1 : 1;
		unsigned char sound_2_so1 : 1;
		unsigned char sound_3_so1 : 1;
		unsigned char sound_4_so1 : 1;
		unsigned char sound_1_so2 : 1;
		unsigned char sound_2_so2 : 1;
		unsigned char sound_3_so2 : 1;
		unsigned char sound_4_so2 : 1;
	} output_terminals;
	struct {
		unsigned char sound_1 : 1;
		unsigned char sound_2 : 1;
		unsigned char sound_3 : 1;
		unsigned char sound_4 : 1;
		unsigned char : 3;
		unsigned char all : 1;
	} toggles;
};

typedef unsigned char wave_sample_memory[32];

// Size assertions
static_assert(sizeof(sound_mode_1_registers) == 5, "Sound mode 1 registers must span 5 bytes.");
static_assert(sizeof(sound_mode_2_registers) == 4, "Sound mode 2 registers must span 4 bytes.");
static_assert(sizeof(sound_mode_3_registers) == 5, "Sound mode 3 registers must span 5 bytes.");
static_assert(sizeof(sound_mode_4_registers) == 4, "Sound mode 4 registers must span 4 bytes.");
static_assert(sizeof(sound_control_registers) == 3, "Sound control registers must span 3 bytes.");
static_assert(sizeof(wave_sample_memory) == 32, "Wave sample buffer must span 32 bytes.");