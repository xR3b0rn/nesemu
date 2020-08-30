
#pragma once

#include "Typedef.h"

namespace NintendoEntertainmentSystem
{
    template <std::size_t Size>
    class Memory
    {
    public:
        Memory()
        {
            std::memset(_memory, 0xFF, Size);
        }
        ui8_t* GetMemoryPointer(address_t address)
        {
            return &_memory[address.raw()];
        }
        const ui8_t* GetMemoryPointer(address_t address) const
        {
            return &_memory[address.raw()];
        }
        ui8_t ReadMemory8(address_t address) const
        {
            return _memory[address.raw()];
        }
        void WriteMemory8(address_t address, ui8_t data)
        {
            _memory[address.raw()] = data;
        }

    protected:
        ui8_t* GetMemory()
        {
            return _memory;
        }
        const ui8_t* GetMemory() const
        {
            return _memory;
        }

    private:
        ui8_t _memory[Size];
    };
}
