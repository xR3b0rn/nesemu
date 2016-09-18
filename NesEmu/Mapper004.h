
#pragma once

#include "IMapper.h"

namespace NintendoEntertainmentSystem
{
	class Mapper004
		: public IMapper
	{
	private:
		using __super1 = IMapper;
	public:
		Mapper004(CPU6502* pCPU6502);
		virtual void setup() override;
		virtual void writeMemory8(address_t address, UINT8 data) override;

	private:
		bool m_PrgMode;
		bool m_ChrMode;
		UINT8 m_Address8001;
	};
}
