
#include "CPUOpCodes.h"

using namespace NintendoEntertainmentSystem;



#pragma region OpCode ADC
void CPUOpCodes::ADC(CPU6502* cpu, UINT8 data)
{
	UINT8 value1 = cpu->getAccumulator() + data + cpu->getFlag(CPU6502::EFlags::Carry) ? 1 : 0;
	UINT16 value2 = cpu->getAccumulator() + data + cpu->getFlag(CPU6502::EFlags::Carry) ? 1 : 0;
	cpu->setAccumulator(value1);
	cpu->setFlag(CPU6502::EFlags::Carry, 0xFF < value2);
	cpu->setFlag(CPU6502::EFlags::Overflow, (value1 & 0x80) == (value2 & 0x80));
	cpu->setFlag(CPU6502::EFlags::Negative, (value1 & 0x80) == 0x80);
	cpu->setFlag(CPU6502::EFlags::Zero, value1 == 0);
}
void CPUOpCodes::ADC_ZeroPage(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8ZeroPage();
	ADC(cpu, data);
}
void CPUOpCodes::ADC_ZeroPageX(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8ZeroPageX();
	ADC(cpu, data);
}
void CPUOpCodes::ADC_Absolute(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8Absolute();
	ADC(cpu, data);
}
void CPUOpCodes::ADC_AbsoluteX(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8AbsoluteX();
	ADC(cpu, data);
}
void CPUOpCodes::ADC_AbsoluteY(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8AbsoluteY();
	ADC(cpu, data);
}
void CPUOpCodes::ADC_IndirectX(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8IndirectX();
	ADC(cpu, data);
}
void CPUOpCodes::ADC_IndirectY(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8IndirectY();
	ADC(cpu, data);
}
#pragma endregion
#pragma region OpCode AND
void CPUOpCodes::AND(CPU6502* cpu, UINT8 data)
{
	cpu->setAccumulator(cpu->getAccumulator() & data);
	cpu->setFlag(CPU6502::EFlags::Zero, cpu->getAccumulator() == 0);
	cpu->setFlag(CPU6502::EFlags::Negative, (cpu->getAccumulator() & 0x80) == 0x80);
}
void CPUOpCodes::AND_ZeroPage(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8ZeroPage();
	AND(cpu, data);
}
void CPUOpCodes::AND_ZeroPageX(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8ZeroPageX();
	AND(cpu, data);
}
void CPUOpCodes::AND_Absolute(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8Absolute();
	AND(cpu, data);
}
void CPUOpCodes::AND_AbsoluteX(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8AbsoluteX();
	AND(cpu, data);
}
void CPUOpCodes::AND_AbsoluteY(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8AbsoluteY();
	AND(cpu, data);
}
void CPUOpCodes::AND_IndirectX(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8IndirectX();
	AND(cpu, data);
}
void CPUOpCodes::AND_IndirectY(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8IndirectY();
	AND(cpu, data);
}
#pragma endregion
#pragma region OpCode ASL
void CPUOpCodes::ASL(CPU6502* cpu, UINT8 data, bool carry)
{
	cpu->setFlag(CPU6502::EFlags::Carry, carry);
	cpu->setFlag(CPU6502::EFlags::Zero, data == 0x00);
}
void CPUOpCodes::ASL_Accumulator(CPU6502* cpu)
{
	bool carry = (cpu->getAccumulator() & 0x80) == 0x80;
	cpu->setAccumulator(cpu->getAccumulator() << 1);
	ASL(cpu, cpu->getAccumulator(), carry);
}
void CPUOpCodes::ASL_ZeroPage(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8ZeroPage();
	bool carry = (data & 0x80) == 0x80;
	data <<= 1;
	cpu->writeMemory8ZeroPage(data);
	ASL(cpu, data, carry);
}
void CPUOpCodes::ASL_ZeroPageX(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8ZeroPageX();
	bool carry = (data & 0x80) == 0x80;
	data <<= 1;
	cpu->writeMemory8ZeroPageX(data);
	ASL(cpu, data, carry);
}
void CPUOpCodes::ASL_AbsoluteX(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8AbsoluteX();
	bool carry = (data & 0x80) == 0x80;
	data <<= 1;
	cpu->writeMemory8AbsoluteX(data);
	ASL(cpu, data, carry);
}
void CPUOpCodes::ASL_AbsoluteY(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8AbsoluteY();
	bool carry = (data & 0x80) == 0x80;
	data <<= 1;
	cpu->writeMemory8AbsoluteY(data);
	ASL(cpu, data, carry);
}
#pragma endregion
#pragma region OpCode BCC
#pragma endregion

#pragma region OpCode BRK
void CPUOpCodes::BRK(CPU6502* cpu, UINT8 data)
{

}
void CPUOpCodes::BRK_Immediate(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8Immediate();

}
#pragma endregion

#pragma region OpCode LDA
void CPUOpCodes::LDA(CPU6502* cpu, UINT8 data)
{
	cpu->setAccumulator(data);
	cpu->setFlag(CPU6502::EFlags::Zero, data == 0);
	cpu->setFlag(CPU6502::EFlags::Negative, data < 0);
}
void CPUOpCodes::LDA_Immediate(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8Immediate();
	LDA(cpu, data);
}
void CPUOpCodes::LDA_ZeroPage(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8ZeroPage();
	LDA(cpu, data);
}
void CPUOpCodes::LDA_ZeroPageX(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8ZeroPageX();
	LDA(cpu, data);
}
void CPUOpCodes::LDA_Absolute(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8Absolute();
	LDA(cpu, data);
}
void CPUOpCodes::LDA_AbsoluteX(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8AbsoluteX();
	LDA(cpu, data);
}
void CPUOpCodes::LDA_AbsoluteY(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8AbsoluteY();
	LDA(cpu, data);
}
void CPUOpCodes::LDA_IndirectX(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8IndirectX();
	LDA(cpu, data);
}
void CPUOpCodes::LDA_IndirectY(CPU6502* cpu)
{
	UINT8 data = cpu->readMemory8IndirectY();
	LDA(cpu, data);
}
#pragma endregion
#pragma region OpCode STA
void CPUOpCodes::STA(CPU6502* cpu, UINT8 data)
{
}
void CPUOpCodes::STA_ZeroPage(CPU6502* cpu)
{
	UINT8 data = cpu->getAccumulator();
	cpu->writeMemory8ZeroPage(data);
	STA(cpu, data);
}
void CPUOpCodes::STA_ZeroPageX(CPU6502* cpu)
{
	UINT8 data = cpu->getAccumulator();
	cpu->writeMemory8ZeroPageX(data);
	STA(cpu, data);
}
void CPUOpCodes::STA_Absolute(CPU6502* cpu)
{
	UINT8 data = cpu->getAccumulator();
	cpu->writeMemory8Absolute(data);
	STA(cpu, data);
}
void CPUOpCodes::STA_AbsoluteX(CPU6502* cpu)
{
	UINT8 data = cpu->getAccumulator();
	cpu->writeMemory8AbsoluteX(data);
	STA(cpu, data);
}
void CPUOpCodes::STA_AbsoluteY(CPU6502* cpu)
{
	UINT8 data = cpu->getAccumulator();
	cpu->writeMemory8AbsoluteY(data);
	STA(cpu, data);
}
void CPUOpCodes::STA_IndirectX(CPU6502* cpu)
{
	UINT8 data = cpu->getAccumulator();
	cpu->writeMemory8IndirectX(data);
	STA(cpu, data);
}
void CPUOpCodes::STA_IndirectY(CPU6502* cpu)
{
	UINT8 data = cpu->getAccumulator();
	cpu->writeMemory8IndirectY(data);
	STA(cpu, data);
}
#pragma endregion
