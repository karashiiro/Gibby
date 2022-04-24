#pragma once

#include "cpu_registers.h"
#include "Clock.h"

class CPU
{
public:
	explicit CPU(Clock *external_clock, interrupt_register &mapped_register, unsigned char *external_memory);

	void ExecuteText(unsigned char *text);
private:
	void NOP();
	void STOP();

	void JR(unsigned char cc, char r8);
	void JP(unsigned char cc, unsigned short &n);

	void LD(unsigned char &d, unsigned char &s);
	void LD(unsigned short &rd, unsigned short &s);

	void LDI(unsigned char &rd, unsigned char &rs);
	void LDD(unsigned char &rd, unsigned char &rs);

	void LDH(unsigned char &d, unsigned char &s);

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

	void ADD(unsigned short &rd, unsigned short &rs);
	void ADD(unsigned char &rd, unsigned char &n);
	void ADD(unsigned short &sp, char r8);

	void ADC(unsigned char &rd, unsigned char &n);
	void SUB(unsigned char &n);
	void SBC(unsigned char &n);
	void AND(unsigned char &n);
	void XOR(unsigned char &n);
	void OR(unsigned char &n);
	void CP(unsigned char &n);

	void PUSH(unsigned short &rs);
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
	void RRC(unsigned char &r)d;
	void RL(unsigned char &rd);
	void RR(unsigned char &rd);
	void SLA(unsigned char &rd);
	void SRA(unsigned char &rd);
	void SWAP(unsigned char &rd);
	void SRL(unsigned char &rd);
	void BIT(unsigned char b, unsigned char &r);
	void RES(unsigned char b, unsigned char &r);
	void SET(unsigned char b, unsigned char &r);

	register_set registers{};
	interrupt_register &interrupts;

	Clock *clock;
	unsigned char *memory;
};
