
#include "CPUMemory.h"

using namespace NintendoEntertainmentSystem;

void CPUMemory::SwitchPrgRom4k(const ui8_t* bank_src, ui8_t area)
{
    ui8_t* memory = GetMemory();
    std::memcpy(&memory[0x8000 + area.to<std::size_t>() * 0x1000], bank_src, 0x1000);
}
void CPUMemory::SwitchPrgRom16k(const ui8_t* bank_src, ui8_t area)
{
    ui8_t* memory = GetMemory();
    std::memcpy(&memory[0x8000 + area.to<std::size_t>() * 0x4000], bank_src, 0x4000);
}
