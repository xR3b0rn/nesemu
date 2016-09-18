
#pragma once

#include "Typedef.h"
#include "PPUMemory.h"

namespace NintendoEntertainmentSystem
{
	class PPU
	{
	private:
		enum class RegisterState
		{
			NO_STATE,
			FIRST,
			SECOND,
		};

	public:
		PPU();

		void doPreparationJob();
		void doMainJob();
		void setup();

		void set_PPUCTRL_register(UINT8* pPPUCTRL);
		void set_PPUMASK_register(UINT8* pPPUMASK);
		void set_PPSTATUS_register(UINT8* pPPUSTATUS);
		void set_OAMADDR_register(UINT8* pOAMADDR);
		void set_OAMDATA_register(UINT8* pOAMDATA);
		void set_PPUSCROOL_register(UINT8* pPPUSCROOL);
		void set_PPUADDR_register(UINT8* pPPUADDR);
		void set_PPUDATA_register(UINT8* pPPUDATA);
		void set_OAMDMA_register(UINT8* pOAMDMA);

		void write_PPUCTRL_register(UINT8 data);
		void write_PPUMASK_register(UINT8 data);
		void write_OAMADDR_register(UINT8 data);
		void write_OAMDATA_register(UINT8 data);
		void write_PPUSCROLL_register(UINT8 data);
		void write_PPUADDR_register(UINT8 data);
		void write_PPUDATA_register(UINT8 data);
		void write_OAMDMA_register(UINT8 data);
		
		UINT8 read_PPUSTATUS_register();
		UINT8 read_OAMDATA_register(UINT8 data);
		UINT8 read_PPUDATA_register(UINT8 data);

	private:
		UINT8* m_pPPUCTRL;
		UINT8* m_pPPUMASK;
		UINT8* m_pPPUSTATUS;
		UINT8* m_pOAMADDR;
		UINT8* m_pOAMDATA;
		UINT8* m_pPPUSCROLL;
		UINT8* m_pPPUADDR;
		UINT8* m_pPPUDATA;
		UINT8* m_pOAMDMA;

		RegisterState m_ePPUADDR_state;
		UINT8 m_prev_PPUADDR;

		PPUMemory m_Memory;
	};
}
