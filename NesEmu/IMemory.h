
#pragma once

#include "Typedef.h"

namespace NintendoEntertainmentSystem
{
	template <UINT32 SIZE>
	class IMemory
	{
	public:
		UINT8* getMemoryPointer(address_t address);
		UINT8 readMemory8(address_t address);
		void writeMemory8(address_t address, UINT8 data);

	protected:
		UINT8* getMemory();

	private:
		UINT8 m_pMemory[SIZE];
	};
}

#include "IMemory.tpp"
