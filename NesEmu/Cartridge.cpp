
#include "Cartridge.h"
#include <fstream>

using namespace NintendoEntertainmentSystem;

#pragma warning (push)
#pragma warning (disable : 4800)

#pragma region Cartridge Header
UINT8 Cartridge::Header::getSizeOfPrgRom()
{
	return m_SizeOfPrgRom;
}
UINT8 Cartridge::Header::getSizeOfChrRom()
{
	return m_SizeOfChrRom;
}
UINT16 Cartridge::Header::getMapperNumber()
{
	return (m_Flags6 >> 4) | (m_Flags7 & 0xF0);
}
bool Cartridge::Header::getTrainerPresent()
{
	return (bool)(m_Flags6 & 0x04);
}
bool Cartridge::Header::getCartridgeContainesBateryBackedPrgRam()
{
	return (bool)(m_Flags6 & 0x02);
}
Cartridge::EMirroring Cartridge::Header::getMirroring()
{
	return EMirroring(((m_Flags6 & 0x08) >> 2) | (m_Flags6 & 0x01));
}
bool Cartridge::Header::getNes2Dot0Format()
{
	return (m_Flags7 & 0x0C) == 0x08;
}
bool Cartridge::Header::getPlayChoice10()
{
	return (m_Flags7 & 0x02) == 0x02;
}
bool Cartridge::Header::getVsUnisystem()
{
	return (m_Flags7 & 0x01) == 0x01;
}
Cartridge::ETVSystem1 Cartridge::Header::getTvSystem1()
{
	return Cartridge::ETVSystem1(m_Flags9 & 0x01);
}
bool Cartridge::Header::getHasBusConflicts()
{
	return bool(m_Flags10 & 0x20);
}
bool Cartridge::Header::getPrgRamPresent()
{
	return bool(m_Flags10 & 0x10);
}
Cartridge::ETVSystem2 Cartridge::Header::getTvSystem2()
{
	return ETVSystem2(m_Flags10 & 0x03);
}
#pragma endregion

Cartridge::Cartridge()
{
	memset(&m_Header, 0, sizeof(m_Header));
}
void Cartridge::load(const char* filepath)
{
	std::ifstream is;
	is.open(filepath, std::ios::in | std::ios::binary);
	is.read((char*)&m_Header, sizeof(m_Header));
	if (m_Header.getTrainerPresent())
	{
		m_Trainer = new UINT8[0x200];
		is.read((char*)m_Trainer, 0x200);
	}
	UINT16 sizeOfPrgRom = m_Header.getSizeOfPrgRom() * 4;
	m_PrgRomData = new UINT8*[sizeOfPrgRom];
	for (INT32 i = 0; i < sizeOfPrgRom; i++)
	{
		m_PrgRomData[i] = new UINT8[0x1000];
		is.read((char*)m_PrgRomData[i], 0x1000);
	}
	m_ChrRomData = new UINT8*[m_Header.getSizeOfChrRom()];
	for (INT32 i = 0; i < m_Header.getSizeOfChrRom(); i++)
	{
		m_ChrRomData[i] = new UINT8[0x2000];
		is.read((char*)m_ChrRomData[i], sizeof(0x2000));
	}
}
UINT8* Cartridge::getPrgRomData(UINT8 index)
{
	return m_PrgRomData[index];
}
UINT8* Cartridge::getChrRomData(UINT8 index)
{
	return m_ChrRomData[index];
}
UINT16 Cartridge::getMapperNumber()
{
	return m_Header.getMapperNumber();
}
UINT8 Cartridge::getPrgRamCount()
{
	return m_Header.getSizeOfPrgRom() *  4;
}
#pragma warning (pop)
