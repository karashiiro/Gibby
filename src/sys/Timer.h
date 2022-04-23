#pragma once

struct timer_registers {
	unsigned char tima;
	unsigned char tma;
	unsigned char tac;
};

class Timer
{
public:
	explicit Timer(timer_registers &mapped_registers);
private:
	const timer_registers &registers;
};
