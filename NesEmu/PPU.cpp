
#include "PPU.h"

using namespace NintendoEntertainmentSystem;

PPU::PPU()
	: m_ePPUADDR_state(RegisterState::NO_STATE)
{
}
void PPU::doPreparationJob()
{
	switch (m_ePPUADDR_state)
	{
	case RegisterState::NO_STATE:
		m_prev_PPUADDR = *m_pPPUADDR;
		m_ePPUADDR_state = RegisterState::FIRST;
		break;
	case RegisterState::FIRST:
		m_ePPUADDR_state = RegisterState::SECOND;
		*m_pPPUDATA = (m_prev_PPUADDR << 8) | *m_pPPUADDR;
		break;
	case RegisterState::SECOND:
	{
		address_t address = (m_prev_PPUADDR << 8) | *m_pPPUADDR;
		m_Memory.writeMemory8(address, *m_pPPUDATA);
		m_ePPUADDR_state = RegisterState::NO_STATE;
		break;
	}
	}
}
void PPU::doMainJob()
{

}
void PPU::setup()
{
}
void PPU::set_PPUCTRL_register(UINT8* pPPUCTRL)
{
	m_pPPUCTRL = pPPUCTRL;
}
void PPU::set_PPUMASK_register(UINT8* pPPUMASK)
{
	m_pPPUMASK = pPPUMASK;
}
void PPU::set_PPSTATUS_register(UINT8* pPPUSTATUS)
{
	m_pPPUSTATUS = pPPUSTATUS;
}
void PPU::set_OAMADDR_register(UINT8* pOAMADDR)
{
	m_pOAMADDR = pOAMADDR;
}
void PPU::set_OAMDATA_register(UINT8* pOAMDATA)
{
	m_pOAMDATA = pOAMDATA;
}
void PPU::set_PPUSCROOL_register(UINT8* pPPUSCROOL)
{
	m_pPPUSCROLL = pPPUSCROOL;
}
void PPU::set_PPUADDR_register(UINT8* pPPUADDR)
{
	m_pPPUADDR = pPPUADDR;
}
void PPU::set_PPUDATA_register(UINT8* pPPUDATA)
{
	m_pPPUDATA = pPPUDATA;
}
void PPU::set_OAMDMA_register(UINT8* pOAMDMA)
{
	m_pOAMDMA = pOAMDMA;
}
