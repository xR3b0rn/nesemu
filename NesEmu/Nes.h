
#pragma once

#include <iostream>
#include "Memory.h"
#include "CPU6502.h"

namespace NintendoEntertainmentSystem
{
    class Nes
    {
    public:
        Nes(const std::string& fn_cartridge);
        void Interpret();

    private:
        CPU6502 _cpu;
        //PPU _ppu;
        Cartridge _cartridge;
        std::unique_ptr<IMapper> _mapper;
    };
}
