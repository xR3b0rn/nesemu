
#pragma once

#include "Typedef.h"
#include "Memory.h"

namespace NintendoEntertainmentSystem
{
	class Cartridge
	{
	public:
		enum class EMirroring
		{
			VERTICAL = 0,
			HORIZONTAL = 1,
			FOUR_SCREEN = 2,
			ONE_SCREEN = 3,
		};
		enum class ETVSystem1
		{
			NTSC = 0,
			PAL = 1,
		};
		enum class ETVSystem2
		{
			NTSC = 0,
			DUAL_COMPATIBLE1 = 1,
			PAL = 2,
			DUAL_COMPATIBLE2 = 3,
		};

#pragma pack(1)
		class Header
		{
		public:
			UINT8 getSizeOfPrgRom(); // 32kibyte
			UINT8 getSizeOfChrRom();
			UINT16 getMapperNumber();
			bool getTrainerPresent();
			bool getCartridgeContainesBateryBackedPrgRam();
			EMirroring getMirroring();
			bool getNes2Dot0Format();
			bool getPlayChoice10();
			bool getVsUnisystem();
			ETVSystem1 getTvSystem1();
			bool getHasBusConflicts();
			bool getPrgRamPresent();
			ETVSystem2 getTvSystem2();

		private:
			char m_Signature[4];
			UINT8 m_SizeOfPrgRom;
			UINT8 m_SizeOfChrRom;
			UINT8 m_Flags6;
			UINT8 m_Flags7;
			UINT8 m_SizeOfPrgRam;
			UINT8 m_Flags9;
			UINT8 m_Flags10;
			UINT8 m_Paddern[5]; // zero filled
		};
#pragma pack()

	public:
		Cartridge();
		void load(const char* filepath);
		UINT8* getPrgRomData(UINT8 index); // 4kibyte
		UINT8* getChrRomData(UINT8 index);
		UINT16 getMapperNumber();
		UINT8 getPrgRamCount();

	private:
		Cartridge::Header m_Header;
		UINT8** m_PrgRomData;	// 4096 * x bytes
		UINT8** m_ChrRomData;	// 8192 * y bytes
		UINT8* m_Trainer;		// 0 or 512 bytes
		EMirroring m_Mirroring;
	};
}
