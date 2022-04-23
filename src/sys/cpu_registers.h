#pragma once

struct register_set {
	union {
		struct {
			unsigned char f;
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

struct flag_register {
	unsigned char unused : 4;
	unsigned char c : 1;
	unsigned char h : 1;
	unsigned char n : 1;
	unsigned char z : 1;
};

// Size assertions
static_assert(sizeof(register_set) == 12, "CPU registers must span 12 bytes.");
static_assert(sizeof(flag_register) == 1, "Flag register must span 1 byte.");