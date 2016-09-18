
#pragma once

#include "Typedef.h"
#include "CPUMemory.h"

namespace NintendoEntertainmentSystem
{
	class CPU6502;

	class IMapper abstract
	{
	public:
		IMapper(CPU6502* pCPU6502);
		virtual void setup() = 0;
		virtual void writeMemory8(address_t address, UINT8 data) = 0;

	protected:
		CPU6502* getCPU6502();

	private:
		CPU6502* m_pCPU6502;
	};
}
