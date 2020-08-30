
#include "Mapper000.h"

using namespace NintendoEntertainmentSystem;

Mapper000::Mapper000(const Cartridge* cartridge)
    : base1_t(cartridge)
{
    if (cartridge)
    {
        SwitchPrgRom16k(GetCartridge()->Prg16kRomData(0_ui8), 0_ui8);
        if (GetCartridge()->CountPrg16KRamBanks() == 1_ui8)
        {
            SwitchPrgRom16k(GetCartridge()->Prg16kRomData(0_ui8), 1_ui8);
        }
        else
        {
            SwitchPrgRom16k(GetCartridge()->Prg16kRomData(1_ui8), 1_ui8);
        }
    }
}
void Mapper000::WriteMemory8(address_t address, ui8_t data)
{
    base1_t::base1_t::WriteMemory8(address, data);
}
