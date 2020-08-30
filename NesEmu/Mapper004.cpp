
#include "Mapper004.h"
#include "CPU6502.h"

using namespace NintendoEntertainmentSystem;

Mapper004::Mapper004(const Cartridge* cartridge)
    : base1_t(cartridge)
{
    ui8_t c = cartridge->CountPrg16KRamBanks();
    SwitchPrgRom4k((c - 8_ui8).cast<ui8_t*>(), 0_ui8);
    SwitchPrgRom4k((c - 7_ui8).cast<ui8_t*>(), 1_ui8);
    SwitchPrgRom4k((c - 6_ui8).cast<ui8_t*>(), 2_ui8);
    SwitchPrgRom4k((c - 5_ui8).cast<ui8_t*>(), 3_ui8);
    SwitchPrgRom4k((c - 4_ui8).cast<ui8_t*>(), 4_ui8);
    SwitchPrgRom4k((c - 3_ui8).cast<ui8_t*>(), 5_ui8);
    SwitchPrgRom4k((c - 2_ui8).cast<ui8_t*>(), 6_ui8);
    SwitchPrgRom4k((c - 1_ui8).cast<ui8_t*>(), 7_ui8);
}
void Mapper004::WriteMemory8(address_t address, ui8_t data)
{
    if (address < 0x8000_ui16)
    {
        WriteMemory8(address, data);
    }
    else
    {
        // ...
    }
}
