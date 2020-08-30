
#include "Cartridge.h"
#include <fstream>

using namespace NintendoEntertainmentSystem;

enum HeaderOffsets
{
    StringIdentification  = 0x00,
    IntegerIdentification = 0x03,
    NumOf16KPrgRomBanks   = 0x04,
    NumOf8KChrRomBanks    = 0x05,
    RomControlByte1       = 0x06,
    RomControlByte2       = 0x07,
    NumberOf8KRamBanks    = 0x08,
    Reserved              = 0x09,
    FirstNonHeaderByte    = 0x10,
};

Cartridge::Cartridge(const std::string& fn_cartridge)
{
    std::ifstream ifs(fn_cartridge, std::ios::binary | std::ios::ate);
    if (!ifs.is_open())
    {
        throw std::runtime_error("Cartridge: Could not open \"" + fn_cartridge + "\"!");
    }
    std::streamsize size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    _buffer.resize(size);
    ifs.read(reinterpret_cast<char*>(&_buffer[0]), size);
}
const ui8_t* Cartridge::Prg16kRomData(ui8_t index) const
{
    if (CountPrg16KRamBanks() <= index)
    {
        throw std::runtime_error("Cartrdige: ROM does not have requeted PRG-ROM bank \"" + index.to_s() + "\"!");
    }
    ui64_t trainer_offset = TrainerPresent() ? 512_ui64 : 0_ui64;
    ui64_t start_prg_rom_data = ui64_t(FirstNonHeaderByte) + trainer_offset;
    return &_buffer[(start_prg_rom_data + index.to<ui64_t>() * 0x4000_ui64).raw()];
}
const ui8_t* Cartridge::Chr8kRomData(ui8_t index) const
{
    ui64_t trainer_offset = TrainerPresent() ? 512_ui64 : 0_ui64;
    ui64_t start_chr_rom_data = ui64_t(FirstNonHeaderByte) + trainer_offset + CountPrg16KRamBanks().to<ui64_t>() * 0x4000_ui64;
    return &_buffer[(start_chr_rom_data + index.to<ui64_t>() * 0x2000_ui64).raw()];
}
ui8_t Cartridge::MapperNumber() const
{
    return _buffer[RomControlByte1] >> 4_ui8 | _buffer[RomControlByte2] & 0xF0_ui8;
}
ui8_t Cartridge::CountPrg16KRamBanks() const
{
    return _buffer[NumOf16KPrgRomBanks];
}
bool Cartridge::TrainerPresent() const
{
    return (_buffer[RomControlByte1] & 0x04_ui8) != 0_ui8;
}
