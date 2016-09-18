
#include "IMapper.h"

using namespace NintendoEntertainmentSystem;

IMapper::IMapper(CPU6502* pCPU6502)
	: m_pCPU6502(pCPU6502)
{
}
CPU6502* IMapper::getCPU6502()
{
	return m_pCPU6502;
}
