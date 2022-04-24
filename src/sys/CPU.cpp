#include "CPU.h"

#include <bitset>

CPU::CPU(Clock *external_clock, interrupt_register &mapped_register, unsigned char *external_memory) : interrupts(mapped_register)
{
	clock = external_clock;
	memory = external_memory;
}

template<size_t n1, size_t n2, typename T>
constexpr unsigned char Extract(T bitset)
{
	unsigned char res = 0;
	for (auto i = n2; i <= n1; i++)
	{
		res = (res << 1) | bitset[i];
	}
	return res;
}

[[noreturn]]
void CPU::ExecuteText(unsigned char* text)
{
	while (true)
	{
		auto opcode1 = text[registers.pc++];
		if (opcode1 == 0xCB)
		{
			// Search for CB-prefixed opcode
			auto opcode2 = std::bitset<8>(text[registers.pc++]);

			// Register is always in bits 2:0 in CB-prefixed opcodes
			unsigned char rn = Extract<2, 0>(opcode2);
			auto &rd = DecodeRegister(rn);

			// BIT, RES, and SET all have the selected bit stored in bits 5:3
			unsigned char bit = Extract<5, 3>(opcode2);

			// Try to jump to SET, RES, or BIT, and then extract bits 5:3
			// to jump to one of the others if that fails.
			unsigned char x = Extract<7, 5>(opcode2);
			switch (x)
			{
			case 3:
				SET(bit, rd);
				break;
			case 2:
				RES(bit, rd);
				break;
			case 1:
				BIT(bit, rd);
				break;
			case 0:
			default:
				auto y = Extract<5, 3>(opcode2);
				switch (y)
				{
				case 7:
					SRL(rd);
					break;
				case 6:
					SWAP(rd);
					break;
				case 5:
					SRA(rd);
					break;
				case 4:
					SLA(rd);
					break;
				case 3:
					RR(rd);
					break;
				case 2:
					RL(rd);
					break;
				case 1:
					RRC(rd);
					break;
				case 0:
				default:
					RLC(rd);
					break;
				}
			}
		}
	}
}

unsigned char& CPU::DecodeRegister(unsigned char r)
{
	switch (r)
	{
	case 0:
		return registers.b;
	case 1:
		return registers.c;
	case 2:
		return registers.d;
	case 3:
		return registers.e;
	case 4:
		return registers.h;
	case 5:
		return registers.l;
	case 6:
		return memory[registers.hl];
	case 7:
		return registers.a;
	default:
		throw std::runtime_error("invalid register requested");
	}
}
