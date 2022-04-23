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
	unsigned char unused;
	unsigned char c : 1;
	unsigned char h : 1;
	unsigned char n : 1;
	unsigned char z : 1;
};