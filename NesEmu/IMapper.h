
#pragma once

#include "Typedef.h"
#include "CPUMemory.h"

namespace NintendoEntertainmentSystem
{
    class CPU6502;
    class IMapper
        : public CPUMemory
    {
    public:
        using base1_t = CPUMemory;

        IMapper(const Cartridge* cartridge);
        virtual void WriteMemory8(address_t address, ui8_t data) = 0;
        virtual ~IMapper() = default;

    protected:
        const Cartridge* GetCartridge() const;

    private:
        const Cartridge* _cartridge;
    };
}
