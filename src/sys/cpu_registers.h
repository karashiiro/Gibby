#pragma once

struct flag_register {
	unsigned char : 4;
	unsigned char c : 1;
	unsigned char h : 1;
	unsigned char n : 1;
	unsigned char z : 1;
};

struct register_set {
	union {
		struct {
			flag_register f;
			unsigned char a;
		};
		unsigned short af;
	};
	union {
		struct {
			unsigned char c;
			unsigned char b;
		};
		unsigned short bc;
	};
	union {
		struct {
			unsigned char e;
			unsigned char d;
		};
		unsigned short de;
	};
	union {
		struct {
			unsigned char l;
			unsigned char h;
		};
		unsigned short hl;
	};
	unsigned short sp;
	unsigned short pc;
};

struct interrupt_register {
	unsigned char v_blank        : 1;
	unsigned char lcd_control    : 1;
	unsigned char timer_overflow : 1;
	unsigned char pin_transition : 1;
	unsigned char : 4;
};

// Size assertions
static_assert(sizeof(register_set) == 12, "CPU registers must span 12 bytes.");
static_assert(sizeof(flag_register) == 1, "Flag register must span 1 byte.");
static_assert(sizeof(interrupt_register) == 1, "Interrupt register must span 1 byte.");