#include "CPU.h"

#include <bitset>

CPU::CPU(Clock *external_clock, interrupt_register &mapped_register, Memory *external_memory) : interrupts(mapped_register)
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
void CPU::Execute()
{
	while (true)
	{
		auto opcode_1 = std::bitset<8>(ReadImm8());
		if (opcode_1.test(7))
		{
			if (opcode_1.test(6))
			{
				// misc instructions
				switch (Extract<2, 0>(opcode_1))
				{
				case 7:
					// resets
					{
						auto hi = Extract<5, 4>(opcode_1);
						auto lo8 = Extract<0, 0>(opcode_1);
						auto n = (hi << 4) | (lo8 << 3);
						RST(n);
					}
					break;
				case 6:
					// 8-bit immediate arithmetic instructions
					{
						auto d8 = ReadImm8();
						switch (Extract<5, 3>(opcode_1))
						{
						case 7:
							CP(d8);
							break;
						case 6:
							OR(d8);
							break;
						case 5:
							XOR(d8);
							break;
						case 4:
							AND(d8);
							break;
						case 3:
							SBC(d8);
							break;
						case 2:
							SUB(d8);
							break;
						case 1:
							ADC(d8);
							break;
						case 0:
						default:
							ADD(d8);
							break;
						}
					}
					break;
				case 5:
					// push or call
					{
						if (opcode_1.test(3) && Extract<2, 0>(opcode_1) == 7)
						{
							unsigned short a16 = ReadImm16();
							CALL(a16);
						}
						else
						{
							auto rn = Extract<5, 4>(opcode_1);
							auto &rd = DecodeRegister2(rn);
							PUSH(rd);
						}
					}
					break;
				case 4:
					// call
					if (opcode_1.test(5))
					{
						unsigned char cond = Extract<4, 3>(opcode_1);
						unsigned short a16 = ReadImm16();
						CALL(cond, a16);
					}
					break;
				case 3:
					// 16-bit relative jump, di/ei, or cb
					{
						switch (Extract<5, 3>(opcode_1))
						{
						case 3:
							EI();
							break;
						case 2:
							DI();
							break;
						case 1:
							ExecuteCB();
							break;
						case 0:
						default:
							{
								unsigned short a16 = ReadImm16();
								JP(a16);
							}
							break;
						}
					}
					break;
				case 2:
					// jump or load
					{
						if (opcode_1.test(5))
						{
							if (opcode_1.test(3))
							{
								unsigned short a16 = ReadImm16();
								auto &mem_a16 = memory->ReadByteRef(a16);
								if (opcode_1.test(4))
								{
									LD(registers.a, mem_a16);
								}
								else
								{
									LD(mem_a16, registers.a);
								}
							}
							else
							{
								auto &mem_c = memory->ReadByteRef(0xFF00 + registers.c);
								if (opcode_1.test(4))
								{
									LD(registers.a, mem_c);
								}
								else
								{
									LD(mem_c, registers.a);
								}
							}
						}
						else
						{
							auto cond = Extract<4, 3>(opcode_1);
							unsigned short a16 = ReadImm16();
							JP(cond, a16);
						}
					}
					break;
				case 1:
					// pop, ret, jp hl, ld
					{
						if (opcode_1.test(3))
						{
							switch (Extract<5, 4>(opcode_1))
							{
							case 3:
								LD(registers.sp, registers.hl);
								clock->Wait(4);
								break;
							case 2:
								JPHL();
								break;
							case 1:
								RETI();
								break;
							case 0:
							default:
								RET();
								break;
							}
						}
						else
						{
							auto rn = Extract<5, 4>(opcode_1);
							auto &rd = DecodeRegister2(rn);
							POP(rd);
						}
					}
					break;
				case 0:
				default:
					// ret, ldh, add, or ld
					{
						if (opcode_1.test(5))
						{
							switch (Extract<4, 3>(opcode_1))
							{
							case 3:
								{
									auto r8 = static_cast<char>(ReadImm8());
									auto sp_r8 = registers.sp + r8;
									clock->Wait(4);
									LD(registers.hl, sp_r8);
								}
								break;
							case 2:
								{
									auto a8 = ReadImm8();
									auto mem_a8 = memory->ReadByte(0xFF00 + a8);
									LD(registers.a, mem_a8);
								}
								break;
							case 1:
								{
									auto r8 = static_cast<char>(ReadImm8());
									ADD(registers.sp, r8);
								}
								break;
							case 0:
							default:
								{
									auto a8 = ReadImm8();
									auto &mem_a8 = memory->ReadByteRef(0xFF00 + a8);
									LD(mem_a8, registers.a);
								}
								break;
							}
						}
						else
						{
							auto cond = Extract<4, 3>(opcode_1);
							RET(cond);
						}
					}
					break;
				}
			}
			else
			{
				// arithmetic instructions
				auto rn = Extract<2, 0>(opcode_1);
				auto &rs = DecodeRegister1(rn);
				if (opcode_1.test(5))
				{
					if (opcode_1.test(4))
					{
						if (opcode_1.test(3))
						{
							CP(rs);
						}
						else
						{
							OR(rs);
						}
					}
					else
					{
						if (opcode_1.test(3))
						{
							XOR(rs);
						}
						else
						{
							AND(rs);
						}
					}
				}
				else
				{
					if (opcode_1.test(4))
					{
						if (opcode_1.test(3))
						{
							SBC(rs);
						}
						else
						{
							SUB(rs);
						}
					}
					else
					{
						if (opcode_1.test(3))
						{
							ADC(rs);
						}
						else
						{
							ADD(rs);
						}
					}
				}
			}
		}
		else
		{
			if (opcode_1.test(6))
			{
				// load instructions
				auto r1 = Extract<5, 3>(opcode_1);
				auto r2 = Extract<2, 0>(opcode_1);
				if (r1 == 6 && r2 == 6)
				{
					HALT();
				}
				else
				{
					auto &rd = DecodeRegister1(r1);
					auto &rs = DecodeRegister1(r2);
					LD(rd, rs);
				}
			}
			else
			{
				// misc instructions
				switch (Extract<2, 0>(opcode_1))
				{
				case 7:
					// bit stuff
					if (opcode_1.test(5))
					{
						if (opcode_1.test(4))
						{
							if (opcode_1.test(3))
							{
								CCF();
							}
							else
							{
								SCF();
							}
						}
						else
						{
							if (opcode_1.test(3))
							{
								CPL();
							}
							else
							{
								DAA();
							}
						}
					}
					else
					{
						if (opcode_1.test(4))
						{
							if (opcode_1.test(3))
							{
								RRA();
							}
							else
							{
								RLA();
							}
						}
						else
						{
							if (opcode_1.test(3))
							{
								RRCA();
							}
							else
							{
								RLCA();
							}
						}
					}
					break;
				case 6:
					// 8-bit immediate loads
					{
						auto rn = Extract<5, 3>(opcode_1);
						auto &rd = DecodeRegister1(rn);
						auto d8 = ReadImm8();
						LD(rd, d8);
					}
					break;
				case 5:
					// dec
					{
						auto rn = Extract<5, 3>(opcode_1);
						auto &rd = DecodeRegister1(rn);
						DEC(rd);
					}
					break;
				case 4:
					// inc
					{
						auto rn = Extract<5, 3>(opcode_1);
						auto &rd = DecodeRegister1(rn);
						INC(rd);
					}
					break;
				case 3:
					// inc or dec
					{
						auto rn = Extract<5, 4>(opcode_1);
						auto &rd = DecodeRegister3(rn);
						if (opcode_1.test(3))
						{
							DEC(rd);
						}
						else
						{
							INC(rd);
						}
					}
					break;
				case 2:
					// memory loads
					{
						auto rn = Extract<6, 4>(opcode_1);
						auto &r = DecodeRegister4(rn);
						if (opcode_1.test(3))
						{
							LD(registers.a, r);
						}
						else
						{
							LD(r, registers.a);
						}
					}
					break;
				case 1:
					// load or add
					{
						auto rn = Extract<6, 4>(opcode_1);
						auto &r = DecodeRegister3(rn);
						if (opcode_1.test(3))
						{
							ADD(registers.hl, r);
						}
						else
						{
							unsigned short d16 = ReadImm16();
							LD(r, d16);
						}
					}
					break;
				case 0:
				default:
					// nop, stop, jr, or load
					switch (Extract<5, 4>(opcode_1))
					{
					case 3:
					case 2:
						{
							char r8 = static_cast<char>(ReadImm8());
							JR(Extract<4, 3>(opcode_1), r8);
						}
						break;
					case 1:
						if (opcode_1.test(3))
						{
							char r8 = static_cast<char>(ReadImm8());
							JR(r8);
						}
						else
						{
							STOP();
						}
						break;
					case 0:
					default:
						if (opcode_1.test(3))
						{
							unsigned short a16 = ReadImm16();
							unsigned short v = 0;
							LD(v, registers.sp);
							memory->WriteByte(a16, v & 0x00ff);
							memory->WriteByte(a16 + 1, v >> 8);
						}
						else
						{
							NOP();
						}
						break;
					}
					break;
				}
			}
		}
	}
}

void CPU::ExecuteCB()
{
	// Search for CB-prefixed opcode
	auto opcode = std::bitset<8>(ReadImm8());

	// Register is always in bits 2:0 in CB-prefixed opcodes
	auto rn = Extract<2, 0>(opcode);
	auto &rd = DecodeRegister1(rn);

	// BIT, RES, and SET all have the selected bit stored in bits 5:3
	auto bit = Extract<5, 3>(opcode);

	// Try to jump to SET, RES, or BIT, and then extract bits 5:3
	// to jump to one of the others if that fails.
	switch (Extract<7, 6>(opcode))
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
		switch (Extract<5, 3>(opcode))
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

unsigned char& CPU::DecodeRegister1(unsigned char rn)
{
	switch (rn)
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
		return memory->ReadByteRef(registers.hl);
	case 7:
		return registers.a;
	default:
		throw std::runtime_error("invalid register requested");
	}
}

unsigned short& CPU::DecodeRegister2(unsigned char rn)
{
	switch (rn)
	{
	case 0:
		return registers.bc;
	case 1:
		return registers.de;
	case 2:
		return registers.hl;
	case 3:
		return registers.af;
	default:
		throw std::runtime_error("invalid register requested");
	}
}

unsigned short& CPU::DecodeRegister3(unsigned char rn)
{
	switch (rn)
	{
	case 0:
		return registers.bc;
	case 1:
		return registers.de;
	case 2:
		return registers.hl;
	case 3:
		return registers.sp;
	default:
		throw std::runtime_error("invalid register requested");
	}
}

unsigned char& CPU::DecodeRegister4(unsigned char rn)
{
	switch (rn)
	{
	case 0:
		return memory->ReadByteRef(registers.bc);
	case 1:
		return memory->ReadByteRef(registers.de);
	case 2:
		return memory->ReadByteRef(registers.hl++);
	case 3:
		return memory->ReadByteRef(registers.hl--);
	default:
		throw std::runtime_error("invalid register requested");
	}
}

unsigned short CPU::ReadImm8()
{
	return memory->ReadByte(registers.pc++);
}

unsigned short CPU::ReadImm16()
{
	return (ReadImm8() << 8) | ReadImm8();
}
