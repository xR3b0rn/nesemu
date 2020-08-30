
#pragma once

#include "IMapper.h"

namespace NintendoEntertainmentSystem
{
    class Mapper000
        : public IMapper
    {
    public:
        using base1_t = IMapper;

        Mapper000(const Cartridge* cartridge);
        virtual void WriteMemory8(address_t address, ui8_t data) override;
    };
}
