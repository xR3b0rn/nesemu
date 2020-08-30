
#pragma once

#include <vector>

#include "Typedef.h"
#include "Memory.h"

namespace NintendoEntertainmentSystem
{
    class Cartridge
    {
    public:
        enum class Mirroring
        {
            Vertical = 0,
            Horizontal = 1,
            FourScreen = 2,
            OneScreen = 3,
        };
        enum class TVSystem1
        {
            NTSC = 0,
            PAL = 1,
        };
        enum class TVSystem2
        {
            NTSC = 0,
            DualCompatible1 = 1,
            PAL = 2,
            DualCompatible2 = 3,
        };

    public:
        Cartridge(const std::string& fn_cartridge);
        const ui8_t* Prg16kRomData(ui8_t index) const; // 4kibyte
        const ui8_t* Chr8kRomData(ui8_t index) const;
        ui8_t MapperNumber() const;
        ui8_t CountPrg16KRamBanks() const;
        bool TrainerPresent() const;

    private:
        std::vector<ui8_t> _buffer;
    };
}
