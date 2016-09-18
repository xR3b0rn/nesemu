
#include "Nes.h"

using namespace NintendoEntertainmentSystem;

Nes::Nes()
	: m_CPU(&m_Cartridge)
{
}
void Nes::loadCartridge(char* filename)
{
	m_Cartridge.load(filename);
	m_CPU.setup();
	m_PPU.set_PPUCTRL_register  (m_CPU.getPointerFromMemory(0x2000));
	m_PPU.set_PPUMASK_register  (m_CPU.getPointerFromMemory(0x2001));
	m_PPU.set_PPSTATUS_register (m_CPU.getPointerFromMemory(0x2002));
	m_PPU.set_OAMADDR_register  (m_CPU.getPointerFromMemory(0x2003));
	m_PPU.set_OAMDATA_register  (m_CPU.getPointerFromMemory(0x2004));
	m_PPU.set_PPUSCROOL_register(m_CPU.getPointerFromMemory(0x2005));
	m_PPU.set_PPUADDR_register  (m_CPU.getPointerFromMemory(0x2006));
	m_PPU.set_PPUDATA_register  (m_CPU.getPointerFromMemory(0x2007));
	m_PPU.set_OAMDMA_register   (m_CPU.getPointerFromMemory(0x4014));
	UINT64 oldCyclesCount = m_CPU.getCyclesCount();
	UINT32 cyclesDelta = 0;
	UINT32 i = 0;
	while (1)
	{
		cyclesDelta = m_CPU.getCyclesCount() - oldCyclesCount;
		oldCyclesCount = m_CPU.getCyclesCount();
		m_CPU.doJob();
		for (UINT32 i = 0; i < cyclesDelta; i++)
		{
			m_PPU.doPreparationJob();
			m_PPU.doMainJob();
			m_PPU.doMainJob();
		}
	}
}
