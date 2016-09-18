
#include "CPUMemory.h"

using namespace NintendoEntertainmentSystem;

void CPUMemory::switchPrgRom4k(UINT8* pMem, UINT8 area)
{
	UINT8* memory = getMemory();
	memcpy(&memory[0x8000 + area * 0x1000], pMem, 0x1000);
}
