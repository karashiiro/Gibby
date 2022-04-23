#pragma once

struct control_registers {
	unsigned char p10 : 1;
	unsigned char p11 : 1;
	unsigned char p12 : 1;
	unsigned char p13 : 1;
	unsigned char p14 : 1;
	unsigned char p15 : 1;
};

class Controls
{
public:
	explicit Controls(control_registers&mapped_registers);
private:
	control_registers&registers;
};
