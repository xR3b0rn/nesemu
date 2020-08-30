
#pragma once

#include "Typedef.h"
#include "Memory.h"
#include "Cartridge.h"

namespace NintendoEntertainmentSystem
{
    class CPUMemory
        : public Memory<0xFFFF>
    {
    public:
        struct Segs
        {
            enum
            {
                ZeroPage = 0x00,
                Stack = 0x0100,
                RAM = 0x0200,
                SRAM = 0x6000,
                PRG_ROM_Lower = 0x8000,
                PRG_ROM_Upper = 0xC000,
            };
        };

        using base1_t = Memory<0xFFFF>;

        void SwitchPrgRom4k(const ui8_t* pMem, ui8_t area);
        void SwitchPrgRom16k(const ui8_t* pMem, ui8_t area);

        ui8_t* GetMemoryPointer(address_t address)
        {
            return base1_t::GetMemoryPointer(DemirrorAddress(address));
        }
        const ui8_t* GetMemoryPointer(address_t address) const
        {
            return base1_t::GetMemoryPointer(DemirrorAddress(address));
        }
        ui8_t ReadMemory8(address_t address) const
        {
            return base1_t::ReadMemory8(DemirrorAddress(address));
        }
        void WriteMemory8(address_t address, ui8_t data)
        {
            base1_t::WriteMemory8(DemirrorAddress(address), data);
        }
        address_t DemirrorAddress(address_t address) const
        {
            if (0x0800_ui16 <= address < 0x2000_ui16)
            {
                ui16_t base = address;
                ui16_t nr = base / 0x07FF_ui16;
                address = base - nr * 0x0FF_ui16;
            }
            else if (0x2008_ui16 <= address <= 0x4000_ui16)
            {
                ui16_t base = address - 0x2000_ui16;
                ui16_t nr = base / 0x0008_ui16;
                address = 0x2000_ui16 + base - nr * 0x0008_ui16;
            }
            return address;
        }
    };
}
