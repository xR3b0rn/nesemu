
#pragma once

#include "IMapper.h"

namespace NintendoEntertainmentSystem
{
    class Mapper004
        : public IMapper
    {
    private:
        using base1_t = IMapper;

    public:
        Mapper004(const Cartridge* cartridge);
        virtual void WriteMemory8(address_t address, ui8_t data) override;

    private:
        bool _prg_mode;
        bool _chr_mode;
        ui8_t _address8001;
    };
}
