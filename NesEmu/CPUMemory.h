
#pragma once

#include "Typedef.h"
#include "IMemory.h"
#include "Cartridge.h"

namespace NintendoEntertainmentSystem
{
	class CPUMemory
		: public IMemory<0xFFFF>
	{
	public:
		void switchPrgRom4k(UINT8* pMem, UINT8 area);

	private:
		friend class Cartridge;
	};
}
