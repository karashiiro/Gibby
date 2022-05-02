#pragma once

#include <bitset>
#include "cpu_registers.h"
#include "Clock.h"
#include "Memory.h"

class CPU
{
public:
	explicit CPU(Clock *external_clock, interrupt_register &mapped_register, Memory *external_memory);

	[[noreturn]] void Execute();
private:
	void ExecuteCB();

	void NOP() {}
	void STOP()
	{
		// TODO
		registers.pc++;
	}

	void JR(unsigned char cc, char r8)
	{
		std::bitset<2> flags(cc);
		if (flags.test(0) && !registers.f.n)
		{
			clock->Wait(8);
			return;
		}

		if (flags.test(1) && !registers.f.c)
		{
			clock->Wait(8);
			return;
		}

		if (!flags.test(1) && !registers.f.z)
		{
			clock->Wait(8);
			return;
		}

		registers.pc += r8;
		clock->Wait(12);
	}
	void JR(char r8)
	{
		registers.pc += r8;
		clock->Wait(4);
	}

	void JP(unsigned char cc, unsigned short n);
	void JP(unsigned short n)
	{
		registers.pc = n;
		clock->Wait(4);
	}

	void JPHL()
	{
		registers.pc = registers.hl;
	}

	static void LD(unsigned char &d, unsigned char s)
	{
		d = s;
	}
	static void LD(unsigned short &d, unsigned short s)
	{
		d = s;
	}

	void INC(unsigned short &rd);
	void INC(unsigned char &rd);

	void DEC(unsigned short &rd);
	void DEC(unsigned char &rd);

	void RLCA();
	void RLA();
	void RRCA();
	void RRA();

	void DAA();
	void CPL();
	void SCF();
	void CCF();

	void HALT();

	void ADD(unsigned short &rd, unsigned short rs);
	void ADD(unsigned char n)
	{
		unsigned char m = n + registers.f.c;
		unsigned char s_lo = (registers.a & 0x0F) + ~(m & 0x0F) + 1;
		unsigned char half_carry = (s_lo & 0x10) >> 4;
		unsigned short result = registers.a + m;
		registers.a = result;
		registers.f.z = registers.a == 0;
		registers.f.n = 0;
		registers.f.h = half_carry;
		registers.f.c = result & 0x0100 >> 8;
	}
	void ADD(unsigned short &sp, char r8);

	void ADC(unsigned char n)
	{
		unsigned char m = n + registers.f.c;
		unsigned char s_lo = (registers.a & 0x0F) + ~(m & 0x0F) + 1;
		unsigned char half_carry = (s_lo & 0x10) >> 4;
		unsigned short result = registers.a + m;
		registers.a = result;
		registers.f.z = registers.a == 0;
		registers.f.n = 0;
		registers.f.h = half_carry;
		registers.f.c = result & 0x0100 >> 8;
	}
	void SUB(unsigned char n)
	{
		unsigned char s_lo = (registers.a & 0x0F) + ~(n & 0x0F) + 1;
		unsigned char half_carry = (s_lo & 0x10) >> 4;
		unsigned short result = registers.a + ~n + 1;
		registers.a = result;
		registers.f.z = registers.a == 0;
		registers.f.n = 1;
		registers.f.h = half_carry;
		registers.f.c = result & 0x0100 >> 8;
	}
	void SBC(unsigned char n)
	{
		unsigned char m = n + registers.f.c;
		unsigned char s_lo = (registers.a & 0x0F) + ~(m & 0x0F) + 1;
		unsigned char half_carry = (s_lo & 0x10) >> 4;
		unsigned short result = registers.a + ~m + 1;
		registers.a = result;
		registers.f.z = registers.a == 0;
		registers.f.n = 1;
		registers.f.h = half_carry;
		registers.f.c = result & 0x0100 >> 8;
	}
	void AND(unsigned char n)
	{
		registers.a &= n;
		registers.f.z = registers.a == 0;
		registers.f.n = 0;
		registers.f.h = 1;
		registers.f.c = 0;
	}
	void XOR(unsigned char n)
	{
		registers.a ^= n;
		registers.f.z = registers.a == 0;
		registers.f.n = 0;
		registers.f.h = 0;
		registers.f.c = 0;
	}
	void OR(unsigned char n)
	{
		registers.a |= n;
		registers.f.z = registers.a == 0;
		registers.f.n = 0;
		registers.f.h = 0;
		registers.f.c = 0;
	}
	void CP(unsigned char n)
	{
		unsigned char s_lo = (registers.a & 0x0F) + ~(n & 0x0F) + 1;
		unsigned char half_carry = (s_lo & 0x10) >> 4;
		registers.f.z = registers.a == n;
		registers.f.n = 1;
		registers.f.h = half_carry;
		registers.f.c = registers.a < n;
	}

	void PUSH(unsigned short rs);
	void POP(unsigned short &rd);

	void DI();
	void EI();

	void CALL(unsigned char cc, unsigned short a16);
	void CALL(unsigned short a16);

	void RST(unsigned char n);

	void RET(unsigned char cc);
	void RET();
	void RETI();

	// CB-prefixed opcodes
	void RLC(unsigned char &rd);
	void RRC(unsigned char &rd);
	void RL(unsigned char &rd);
	void RR(unsigned char &rd);
	void SLA(unsigned char &rd);
	void SRA(unsigned char &rd);
	void SWAP(unsigned char &rd);
	void SRL(unsigned char &rd);
	void BIT(unsigned char b, unsigned char &rd)
	{
		registers.f.z = (rd & (1 << b)) >> b;
		registers.f.n = 0;
		registers.f.h = 1;
	}
	static void RES(unsigned char b, unsigned char &rd)
	{
		rd = rd & ~(1 << b);
	}
	static void SET(unsigned char b, unsigned char &rd)
	{
		rd = rd | (1 << b);
	}

	// Helper functions
	unsigned char& DecodeRegister1(unsigned char rn);
	unsigned short& DecodeRegister2(unsigned char rn);
	unsigned short& DecodeRegister3(unsigned char rn);
	unsigned char& DecodeRegister4(unsigned char rn);

	unsigned short ReadImm8();
	unsigned short ReadImm16();

	register_set registers{};
	interrupt_register &interrupts;

	Clock *clock;
	Memory *memory;
};
