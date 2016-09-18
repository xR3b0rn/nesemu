
#include "Mapper004.h"
#include "CPU6502.h"

using namespace NintendoEntertainmentSystem;

#pragma warning (push)
#pragma warning (disable : 4800)

Mapper004::Mapper004(CPU6502* pCPU6502)
	: __super1(pCPU6502)
{
}
void Mapper004::setup()
{
	CPU6502* pCPU6502 = getCPU6502();
	UINT8 prgRamCount = pCPU6502->getCartridge()->getPrgRamCount();
	pCPU6502->switchPrgRom4k(prgRamCount - 8, 0);
	pCPU6502->switchPrgRom4k(prgRamCount - 7, 1);
	pCPU6502->switchPrgRom4k(prgRamCount - 6, 2);
	pCPU6502->switchPrgRom4k(prgRamCount - 5, 3);
	pCPU6502->switchPrgRom4k(prgRamCount - 4, 4);
	pCPU6502->switchPrgRom4k(prgRamCount - 3, 5);
	pCPU6502->switchPrgRom4k(prgRamCount - 2, 6);
	pCPU6502->switchPrgRom4k(prgRamCount - 1, 7);
}
void Mapper004::writeMemory8(address_t address, UINT8 data)
{
	CPU6502* pCPU6502 = getCPU6502();
	if (address < 0x8000)
	{
		pCPU6502->writeMappedMemory8Absolute(address, data);
	}
	else
	{
		switch (address)
		{
		case 0x8000:
			m_PrgMode = data & 0x80;
			m_ChrMode = data & 0x40;
			m_Address8001 = data & 0x07;
			break;
		case 0x8001:
			switch (m_Address8001)
			{
			case 0: break;

			case 1: break;
			case 2: break;
			case 3: break;
			case 4: break;
			case 5: break;
			case 6:
				if (m_PrgMode)
				{
					pCPU6502->switchPrgRom4k(data * 2, 3);
					pCPU6502->switchPrgRom4k(data * 2 + 1, 4);
				}
				else
				{
					pCPU6502->switchPrgRom4k(data * 2, 0);
					pCPU6502->switchPrgRom4k(data * 2 + 1, 1);
				}
				pCPU6502->switchPrgRom4k(data * 2 + 2, 1);
				pCPU6502->switchPrgRom4k(data * 2 + 3, 2);
				break;
			case 7: break;;
			}
			break;
		case 0xA000:
		case 0xA001:
		case 0xC000:
		case 0xC001:
		case 0xE000:
		case 0xE001:;
		}
	}
}

#pragma warning (pop)
