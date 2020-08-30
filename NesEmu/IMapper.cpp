
#include "IMapper.h"

using namespace NintendoEntertainmentSystem;

IMapper::IMapper(const Cartridge* cartridge)
    : _cartridge(cartridge)
{}
const Cartridge* IMapper::GetCartridge() const
{
    return _cartridge;
}
