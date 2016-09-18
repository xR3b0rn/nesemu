
#pragma once

#include "Typedef.h"
#include "IMapper.h"
#include "CPUMemory.h"
#include "Cartridge.h"

namespace NintendoEntertainmentSystem
{
	class CPU6502
	{
	public:
		enum class EFlags : UINT32
		{
			Carry = 0,
			Zero = 1,
			Interrupt = 2,
			BinaryCoded = 3,
			Breakpoint = 4,
			Overflow = 6,
			Negative = 7
		};

	public:
		CPU6502(Cartridge* pCartridge);
		void setup();
		void doJob();
		UINT8* getPointerFromMemory(address_t address);
		void writeMappedMemory8Absolute(address_t address, UINT8 data);
		void switchPrgRom4k(UINT8 index, UINT8 area);
		Cartridge* getCartridge();

		// Write Memory By Different Addressing Modes
		void writeMemory8Absolute(UINT8 data);
		void writeMemory8AbsoluteX(UINT8 data);
		void writeMemory8AbsoluteY(UINT8 data);
		void writeMemory8ZeroPage(UINT8 data);
		void writeMemory8ZeroPageX(UINT8 data);
		void writeMemory8IndirectX(UINT8 data);
		void writeMemory8IndirectY(UINT8 data);

		// Read Memory By Different Addressing Modes
		UINT8 readMemory8Immediate();
		UINT8 readMemory8Absolute();
		UINT8 readMemory8AbsoluteX();
		UINT8 readMemory8AbsoluteY();
		UINT8 readMemory8ZeroPage();
		UINT8 readMemory8ZeroPageX();
		UINT8 readMemory8IndirectX();
		UINT8 readMemory8IndirectY();

		// setter
		void createMapperByMapperId(UINT16 mapperId);
		void setAccumulator(UINT8 data);
		void setFlag(EFlags flag, bool carry);

		// getter
		UINT8 getAccumulator();
		bool getFlag(EFlags flag);
		UINT64 getCyclesCount();

	private:
		// Attributes
		UINT8 m_AccumulatorRegister;
		UINT8 m_XIndexRegister;
		UINT8 m_YIndexRegister;
		UINT8 m_StackPointerRegister;
		UINT16 m_ProgramCounterRegister;
		UINT8 m_StatusRegister;

		// cycles counter
		UINT64 m_CyclesCounter;

		// Memory
		IMapper* m_pMapper;
		Cartridge* m_pCartridge;
		CPUMemory m_Memory;
	};
}
