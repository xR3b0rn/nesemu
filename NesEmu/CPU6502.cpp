
#include "CPU6502.h"
#include "CPUOpCodes.h"
#include "Mapper004.h"

using namespace NintendoEntertainmentSystem;

#pragma warning (push)
#pragma warning (disable : 4800)

CPU6502::CPU6502(Cartridge* pCartridge)
	: m_AccumulatorRegister(0)
	, m_XIndexRegister(0)
	, m_YIndexRegister(0)
	, m_StackPointerRegister(0)
	, m_ProgramCounterRegister(0)
	, m_StatusRegister(0)
	, m_CyclesCounter(0)
	, m_pMapper(nullptr)
	, m_pCartridge(pCartridge)
{
}
void CPU6502::setup()
{
	m_CyclesCounter = 0;
	createMapperByMapperId(m_pCartridge->getMapperNumber());
}
UINT64 CPU6502::getCyclesCount()
{
	return m_CyclesCounter;
}
void CPU6502::doJob()
{
	UINT8 opCode = readMemory8Immediate();
	switch (opCode)
	{
	case 0xA9: CPUOpCodes::LDA_Immediate(this); break;
	case 0xA5: CPUOpCodes::LDA_ZeroPage(this); break;
	case 0xB5: CPUOpCodes::LDA_ZeroPageX(this); break;
	case 0xAD: CPUOpCodes::LDA_Absolute(this); break;
	case 0xBD: CPUOpCodes::LDA_AbsoluteX(this); break;
	case 0xB9: CPUOpCodes::LDA_AbsoluteY(this); break;
	case 0xA1: CPUOpCodes::LDA_IndirectX(this); break;
	case 0xB1: CPUOpCodes::LDA_IndirectY(this); break;

	case 0x85: CPUOpCodes::STA_ZeroPage(this); break;
	case 0x95: CPUOpCodes::STA_ZeroPageX(this); break;
	case 0x8D: CPUOpCodes::STA_Absolute(this); break;
	case 0x9D: CPUOpCodes::STA_AbsoluteX(this); break;
	case 0x99: CPUOpCodes::STA_AbsoluteY(this); break;
	case 0x81: CPUOpCodes::STA_IndirectX(this); break;
	case 0x91: CPUOpCodes::STA_IndirectY(this); break;
	}
}
UINT8* CPU6502::getPointerFromMemory(address_t address)
{
	return m_Memory.getMemoryPointer(address);
}
void CPU6502::createMapperByMapperId(UINT16 mapperId)
{
	switch (mapperId)
	{
	case 0x004: m_pMapper = new Mapper004(this); break;
	}
	m_pMapper->setup();
	UINT16 bl = m_Memory.readMemory8(0xFFFC);
	UINT16 bh = m_Memory.readMemory8(0xFFFD);
	m_ProgramCounterRegister = (bh << 8) | bl;
}
void CPU6502::switchPrgRom4k(UINT8 index, UINT8 area)
{
	UINT8* pData = m_pCartridge->getPrgRomData(index);
	m_Memory.switchPrgRom4k(pData, area);
}
void CPU6502::setAccumulator(UINT8 data)
{
	m_AccumulatorRegister = data;
}
void CPU6502::setFlag(EFlags flag, bool carry)
{
	m_StatusRegister |= 1 << (UINT32)flag;
}
Cartridge* CPU6502::getCartridge()
{
	return m_pCartridge;
}
UINT8 CPU6502::getAccumulator()
{
	return m_AccumulatorRegister;
}
bool CPU6502::getFlag(EFlags flag)
{
	return m_StatusRegister & (1 << (UINT32)flag);
}
void CPU6502::writeMappedMemory8Absolute(address_t address, UINT8 data)
{
	m_Memory.writeMemory8(address, data);
}
void CPU6502::writeMemory8Absolute(UINT8 data)
{
	address_t address = 0;
	address  = m_Memory.readMemory8(m_ProgramCounterRegister);
	address |= m_Memory.readMemory8(m_ProgramCounterRegister + 1) << 8;
	m_ProgramCounterRegister += 2;
	m_CyclesCounter += 2;
	m_pMapper->writeMemory8(address, data);
}
void CPU6502::writeMemory8AbsoluteX(UINT8 data)
{
	address_t
	address = m_Memory.readMemory8(m_ProgramCounterRegister);
	address |= m_Memory.readMemory8(m_ProgramCounterRegister + 1) << 8;
	m_ProgramCounterRegister += 2;
	m_CyclesCounter += 2;
	m_pMapper->writeMemory8(address + m_XIndexRegister, data);
}
void CPU6502::writeMemory8AbsoluteY(UINT8 data)
{
	address_t
	address = m_Memory.readMemory8(m_ProgramCounterRegister);
	address |= m_Memory.readMemory8(m_ProgramCounterRegister + 1) << 8;
	m_ProgramCounterRegister += 2;
	m_CyclesCounter += 2;
	m_pMapper->writeMemory8(address + m_YIndexRegister, data);
}
void CPU6502::writeMemory8ZeroPage(UINT8 data)
{
	address_t address = m_Memory.readMemory8(m_ProgramCounterRegister);
	m_ProgramCounterRegister++;
	m_CyclesCounter++;
	m_pMapper->writeMemory8(address, data);
}
void CPU6502::writeMemory8ZeroPageX(UINT8 data)
{
	address_t address = m_Memory.readMemory8(m_ProgramCounterRegister);
	m_ProgramCounterRegister++;
	m_CyclesCounter++;
	m_pMapper->writeMemory8(address + m_XIndexRegister, data);
}
void CPU6502::writeMemory8IndirectX(UINT8 data)
{
	address_t address1 = m_Memory.readMemory8(m_ProgramCounterRegister);
	address_t
	address2 = m_Memory.readMemory8(address1 + m_XIndexRegister * 2);
	address2 |= m_Memory.readMemory8(address1 + m_XIndexRegister * 2 + 1);
	m_ProgramCounterRegister += 2;
	m_CyclesCounter += 2;
	m_pMapper->writeMemory8(address2, data);
}
void CPU6502::writeMemory8IndirectY(UINT8 data)
{
	address_t address1 = m_Memory.readMemory8(m_ProgramCounterRegister);
	address_t
	address2 = m_Memory.readMemory8(address1 + m_YIndexRegister * 2);
	address2 |= m_Memory.readMemory8(address1 + m_YIndexRegister * 2 + 1);
	m_ProgramCounterRegister += 2;
	m_CyclesCounter += 2;
	m_pMapper->writeMemory8(address2, data);
}
UINT8 CPU6502::readMemory8Immediate()
{
	UINT8 data = m_Memory.readMemory8(m_ProgramCounterRegister);
	m_ProgramCounterRegister++;
	m_CyclesCounter++;
	return data;
}
UINT8 CPU6502::readMemory8Absolute()
{
	address_t
	address = m_Memory.readMemory8(m_ProgramCounterRegister);
	address |= m_Memory.readMemory8(m_ProgramCounterRegister + 1) << 8;
	m_ProgramCounterRegister += 2;
	m_CyclesCounter += 2;
	return m_Memory.readMemory8(address);
}
UINT8 CPU6502::readMemory8AbsoluteX()
{
	address_t
	address = m_Memory.readMemory8(m_ProgramCounterRegister);
	address |= m_Memory.readMemory8(m_ProgramCounterRegister + (1 << 8));
	m_ProgramCounterRegister += 2;
	m_CyclesCounter += 2;
	return m_Memory.readMemory8(address + m_XIndexRegister);
}
UINT8 CPU6502::readMemory8AbsoluteY()
{
	address_t
	address = m_Memory.readMemory8(m_ProgramCounterRegister);
	address |= m_Memory.readMemory8(m_ProgramCounterRegister + (1 << 8));
	m_ProgramCounterRegister += 2;
	m_CyclesCounter += 2;
	return m_Memory.readMemory8(address + m_YIndexRegister);
}
UINT8 CPU6502::readMemory8ZeroPage()
{
	address_t address = m_Memory.readMemory8(m_ProgramCounterRegister);
	m_ProgramCounterRegister++;
	m_CyclesCounter++;
	return m_Memory.readMemory8(address);
}
UINT8 CPU6502::readMemory8ZeroPageX()
{
	address_t address = m_Memory.readMemory8(m_ProgramCounterRegister);
	m_ProgramCounterRegister++;
	m_CyclesCounter++;
	return m_Memory.readMemory8(address + m_XIndexRegister);
}
UINT8 CPU6502::readMemory8IndirectX()
{
	address_t address1 = m_Memory.readMemory8(m_ProgramCounterRegister);
	address_t
	address2 = m_Memory.readMemory8(address1 + m_XIndexRegister * 2);
	address2 |= m_Memory.readMemory8(address1 + m_XIndexRegister * 2 + 1);
	m_ProgramCounterRegister += 2;
	m_CyclesCounter += 2;
	return m_Memory.readMemory8(address2);
}
UINT8 CPU6502::readMemory8IndirectY()
{
	address_t address1 = m_Memory.readMemory8(m_ProgramCounterRegister);
	address_t
	address2 = m_Memory.readMemory8(address1 + m_YIndexRegister * 2);
	address2 |= m_Memory.readMemory8(address1 + m_YIndexRegister * 2 + 1);
	m_ProgramCounterRegister++;
	m_CyclesCounter++;
	return m_Memory.readMemory8(address2);
}

#pragma warning (pop)
