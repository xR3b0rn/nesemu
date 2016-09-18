
#pragma once

#include "Memory.h"
#include "CPU6502.h"
#include "PPU.h"

namespace NintendoEntertainmentSystem
{
	class Nes
	{
	public:
		Nes();
		void loadCartridge(char* filename);

	private:
		CPU6502 m_CPU;
		PPU m_PPU;
		Cartridge m_Cartridge;
	};
}
