
#include <memory>
#include <string>

#include "Nes.h"
#include "Mapper000.h"
#include "Mapper004.h"

using namespace std::string_literals;
using namespace NintendoEntertainmentSystem;

class FaxMapper
{
public:
    static std::unique_ptr<IMapper> CreateMapper(ui8_t id, Cartridge* cartridge)
    {
        std::unique_ptr<Mapper004> result;
        switch (id.to<std::size_t>())
        {
        case 0x000: return std::make_unique<Mapper000>(cartridge);
        case 0x004: return std::make_unique<Mapper004>(cartridge);
        }
        return nullptr;
    }
};

Nes::Nes(const std::string& fn_cartridge)
    : _cartridge(fn_cartridge)
{
    _mapper = FaxMapper::CreateMapper(_cartridge.MapperNumber(), &_cartridge);
    if (!_mapper)
    {
        throw std::runtime_error("Nes: Memory mapper \"" + _cartridge.MapperNumber().to_s() + "\" not supported!");
    }
    _cpu = CPU6502(_mapper.get());
    Interpret();
    //_ppu.set_PPUCTRL_register  (_cpu_memory.GetMemoryPointer(0x2000_ui16));
    //_ppu.set_PPUMASK_register  (_cpu_memory.GetMemoryPointer(0x2001_ui16));
    //_ppu.set_PPSTATUS_register (_cpu_memory.GetMemoryPointer(0x2002_ui16));
    //_ppu.set_OAMADDR_register  (_cpu_memory.GetMemoryPointer(0x2003_ui16));
    //_ppu.set_OAMDATA_register  (_cpu_memory.GetMemoryPointer(0x2004_ui16));
    //_ppu.set_PPUSCROOL_register(_cpu_memory.GetMemoryPointer(0x2005_ui16));
    //_ppu.set_PPUADDR_register  (_cpu_memory.GetMemoryPointer(0x2006_ui16));
    //_ppu.set_PPUDATA_register  (_cpu_memory.GetMemoryPointer(0x2007_ui16));
    //_ppu.set_OAMDMA_register   (_cpu_memory.GetMemoryPointer(0x4014_ui16));
}
void Nes::Interpret()
{
    // Computed goto
    static void* table[0x100] = { 0 };
    table[CPU6502::OPC::ADC_Immediate]       = &&ADC_Immediate;
    table[CPU6502::OPC::ADC_ZeroPage]        = &&ADC_ZeroPage;
    table[CPU6502::OPC::ADC_ZeroPageX]       = &&ADC_ZeroPageX;
    table[CPU6502::OPC::ADC_Absolute]        = &&ADC_Absolute;
    table[CPU6502::OPC::ADC_AbsoluteX]       = &&ADC_AbsoluteX;
    table[CPU6502::OPC::ADC_AbsoluteY]       = &&ADC_AbsoluteY;
    table[CPU6502::OPC::ADC_IndirectX]       = &&ADC_IndirectX;
    table[CPU6502::OPC::ADC_IndirectY]       = &&ADC_IndirectY;
    table[CPU6502::OPC::AND_Immediate]       = &&AND_Immediate;
    table[CPU6502::OPC::AND_ZeroPage]        = &&AND_ZeroPage;
    table[CPU6502::OPC::AND_ZeroPageX]       = &&AND_ZeroPageX;
    table[CPU6502::OPC::AND_Absolute]        = &&AND_Absolute;
    table[CPU6502::OPC::AND_AbsoluteX]       = &&AND_AbsoluteX;
    table[CPU6502::OPC::AND_AbsoluteY]       = &&AND_AbsoluteY;
    table[CPU6502::OPC::AND_IndirectX]       = &&AND_IndirectX;
    table[CPU6502::OPC::AND_IndirectY]       = &&AND_IndirectY;
    table[CPU6502::OPC::ASL_Accumulator]     = &&ASL_Accumulator;
    table[CPU6502::OPC::ASL_ZeroPage]        = &&ASL_ZeroPage;
    table[CPU6502::OPC::ASL_ZeroPageX]       = &&ASL_ZeroPageX;
    table[CPU6502::OPC::ASL_Absolute]        = &&ASL_Absolute;
    table[CPU6502::OPC::ASL_AbsoluteX]       = &&ASL_AbsoluteX;
    table[CPU6502::OPC::BCC]                 = &&BCC;
    table[CPU6502::OPC::BCS]                 = &&BCS;
    table[CPU6502::OPC::BEQ]                 = &&BEQ;
    table[CPU6502::OPC::BIT_ZeroPage]        = &&BIT_ZeroPage;
    table[CPU6502::OPC::BIT_Absolute]        = &&BIT_Absolute;
    table[CPU6502::OPC::BMI]                 = &&BMI;
    table[CPU6502::OPC::BNE]                 = &&BNE;
    table[CPU6502::OPC::BPL]                 = &&BPL;
    table[CPU6502::OPC::BRK]                 = &&BRK;
    table[CPU6502::OPC::BVC]                 = &&BVC;
    table[CPU6502::OPC::BVS]                 = &&BVS;
    table[CPU6502::OPC::CLC]                 = &&CLC;
    table[CPU6502::OPC::CLD]                 = &&CLD;
    table[CPU6502::OPC::CLI]                 = &&CLI;
    table[CPU6502::OPC::CLV]                 = &&CLV;
    table[CPU6502::OPC::CMP_Immediate]       = &&CMP_Immediate;
    table[CPU6502::OPC::CMP_ZeroPage]        = &&CMP_ZeroPage;
    table[CPU6502::OPC::CMP_ZeroPageX]       = &&CMP_ZeroPageX;
    table[CPU6502::OPC::CMP_Absolute]        = &&CMP_Absolute;
    table[CPU6502::OPC::CMP_AbsoluteX]       = &&CMP_AbsoluteX;
    table[CPU6502::OPC::CMP_AbsoluteY]       = &&CMP_AbsoluteY;
    table[CPU6502::OPC::CMP_IndirectX]       = &&CMP_IndirectX;
    table[CPU6502::OPC::CMP_IndirectY]       = &&CMP_IndirectY;
    table[CPU6502::OPC::CPX_Immediate]       = &&CPX_Immediate;
    table[CPU6502::OPC::CPX_ZeroPage]        = &&CPX_ZeroPage;
    table[CPU6502::OPC::CPX_Absolute]        = &&CPX_Absolute;
    table[CPU6502::OPC::CPY_Immediate]       = &&CPY_Immediate;
    table[CPU6502::OPC::CPY_ZeroPage]        = &&CPY_ZeroPage;
    table[CPU6502::OPC::CPY_Absolute]        = &&CPY_Absolute;
    table[CPU6502::OPC::DEC_ZeroPage]        = &&DEC_ZeroPage;
    table[CPU6502::OPC::DEC_ZeroPageX]       = &&DEC_ZeroPageX;
    table[CPU6502::OPC::DEC_Absolute]        = &&DEC_Absolute;
    table[CPU6502::OPC::DEC_AbsoluteX]       = &&DEC_AbsoluteX;
    table[CPU6502::OPC::DEX]                 = &&DEX;
    table[CPU6502::OPC::DEY]                 = &&DEY;
    table[CPU6502::OPC::EOR_Immediate]       = &&EOR_Immediate;
    table[CPU6502::OPC::EOR_ZeroPage]        = &&EOR_ZeroPage;
    table[CPU6502::OPC::EOR_ZeroPageX]       = &&EOR_ZeroPageX;
    table[CPU6502::OPC::EOR_Absolute]        = &&EOR_Absolute;
    table[CPU6502::OPC::EOR_AbsoluteX]       = &&EOR_AbsoluteX;
    table[CPU6502::OPC::EOR_AbsoluteY]       = &&EOR_AbsoluteY;
    table[CPU6502::OPC::EOR_IndirectX]       = &&EOR_IndirectX;
    table[CPU6502::OPC::EOR_IndirectY]       = &&EOR_IndirectY;
    table[CPU6502::OPC::INC_ZeroPage]        = &&INC_ZeroPage;
    table[CPU6502::OPC::INC_ZeroPageX]       = &&INC_ZeroPageX;
    table[CPU6502::OPC::INC_Absolute]        = &&INC_Absolute;
    table[CPU6502::OPC::INC_AbsoluteX]       = &&INC_AbsoluteX;
    table[CPU6502::OPC::INX]                 = &&INX;
    table[CPU6502::OPC::INY]                 = &&INY;
    table[CPU6502::OPC::JMP_Absolute]        = &&JMP_Absolute;
    table[CPU6502::OPC::JMP_Indirect]        = &&JMP_Indirect;
    table[CPU6502::OPC::JSR]                 = &&JSR;
    table[CPU6502::OPC::LDA_Immediate]       = &&LDA_Immediate;
    table[CPU6502::OPC::LDA_ZeroPage]        = &&LDA_ZeroPage;
    table[CPU6502::OPC::LDA_ZeroPageX]       = &&LDA_ZeroPageX;
    table[CPU6502::OPC::LDA_Absolute]        = &&LDA_Absolute;
    table[CPU6502::OPC::LDA_AbsoluteX]       = &&LDA_AbsoluteX;
    table[CPU6502::OPC::LDA_AbsoluteY]       = &&LDA_AbsoluteY;
    table[CPU6502::OPC::LDA_IndirectX]       = &&LDA_IndirectX;
    table[CPU6502::OPC::LDA_IndirectY]       = &&LDA_IndirectY;
    table[CPU6502::OPC::LDX_Immediate]       = &&LDX_Immediate;
    table[CPU6502::OPC::LDX_ZeroPage]        = &&LDX_ZeroPage;
    table[CPU6502::OPC::LDX_ZeroPageY]       = &&LDX_ZeroPageY;
    table[CPU6502::OPC::LDX_Absolute]        = &&LDX_Absolute;
    table[CPU6502::OPC::LDX_AbsoluteY]       = &&LDX_AbsoluteY;
    table[CPU6502::OPC::LDY_Immediate]       = &&LDY_Immediate;
    table[CPU6502::OPC::LDY_ZeroPage]        = &&LDY_ZeroPage;
    table[CPU6502::OPC::LDY_ZeroPageY]       = &&LDY_ZeroPageY;
    table[CPU6502::OPC::LDY_Absolute]        = &&LDY_Absolute;
    table[CPU6502::OPC::LDY_AbsoluteY]       = &&LDY_AbsoluteY;
    table[CPU6502::OPC::LSR_Accumulator]     = &&LSR_Accumulator;
    table[CPU6502::OPC::LSR_ZeroPage]        = &&LSR_ZeroPage;
    table[CPU6502::OPC::LSR_ZeroPageY]       = &&LSR_ZeroPageY;
    table[CPU6502::OPC::LSR_Absolute]        = &&LSR_Absolute;
    table[CPU6502::OPC::LSR_AbsoluteY]       = &&LSR_AbsoluteY;
    table[CPU6502::OPC::NOP]                 = &&NOP;
    table[CPU6502::OPC::ORA_Immediate]       = &&ORA_Immediate;
    table[CPU6502::OPC::ORA_ZeroPage]        = &&ORA_ZeroPage;
    table[CPU6502::OPC::ORA_ZeroPageX]       = &&ORA_ZeroPageX;
    table[CPU6502::OPC::ORA_Absolute]        = &&ORA_Absolute;
    table[CPU6502::OPC::ORA_AbsoluteX]       = &&ORA_AbsoluteX;
    table[CPU6502::OPC::ORA_AbsoluteY]       = &&ORA_AbsoluteY;
    table[CPU6502::OPC::ORA_IndirectX]       = &&ORA_IndirectX;
    table[CPU6502::OPC::ORA_IndirectY]       = &&ORA_IndirectY;
    table[CPU6502::OPC::PHA]                 = &&PHA;
    table[CPU6502::OPC::PHP]                 = &&PHP;
    table[CPU6502::OPC::PLA]                 = &&PLA;
    table[CPU6502::OPC::PLP]                 = &&PLP;
    table[CPU6502::OPC::ROL_Accumulator]     = &&ROL_Accumulator;
    table[CPU6502::OPC::ROL_ZeroPage]        = &&ROL_ZeroPage;
    table[CPU6502::OPC::ROL_ZeroPageX]       = &&ROL_ZeroPageX;
    table[CPU6502::OPC::ROL_Absolute]        = &&ROL_Absolute;
    table[CPU6502::OPC::ROL_AbsoluteX]       = &&ROL_AbsoluteX;
    table[CPU6502::OPC::ROR_Accumulator]     = &&ROR_Accumulator;
    table[CPU6502::OPC::ROR_ZeroPage]        = &&ROR_ZeroPage;
    table[CPU6502::OPC::ROR_ZeroPageX]       = &&ROR_ZeroPageX;
    table[CPU6502::OPC::ROR_Absolute]        = &&ROR_Absolute;
    table[CPU6502::OPC::ROR_AbsoluteX]       = &&ROR_AbsoluteX;
    table[CPU6502::OPC::RTI]                 = &&RTI;
    table[CPU6502::OPC::RTS]                 = &&RTS;
    table[CPU6502::OPC::SBC_Immediate]       = &&SBC_Immediate;
    table[CPU6502::OPC::SBC_ZeroPage]        = &&SBC_ZeroPage;
    table[CPU6502::OPC::SBC_ZeroPageX]       = &&SBC_ZeroPageX;
    table[CPU6502::OPC::SBC_Absolute]        = &&SBC_Absolute;
    table[CPU6502::OPC::SBC_AbsoluteX]       = &&SBC_AbsoluteX;
    table[CPU6502::OPC::SBC_AbsoluteY]       = &&SBC_AbsoluteY;
    table[CPU6502::OPC::SBC_IndirectX]       = &&SBC_IndirectX;
    table[CPU6502::OPC::SBC_IndirectY]       = &&SBC_IndirectY;
    table[CPU6502::OPC::SEC]                 = &&SEC;
    table[CPU6502::OPC::SED]                 = &&SED;
    table[CPU6502::OPC::SEI]                 = &&SEI;
    table[CPU6502::OPC::STA_ZeroPage]        = &&STA_ZeroPage;
    table[CPU6502::OPC::STA_ZeroPageX]       = &&STA_ZeroPageX;
    table[CPU6502::OPC::STA_Absolute]        = &&STA_Absolute;
    table[CPU6502::OPC::STA_AbsoluteX]       = &&STA_AbsoluteX;
    table[CPU6502::OPC::STA_AbsoluteY]       = &&STA_AbsoluteY;
    table[CPU6502::OPC::STA_IndirectX]       = &&STA_IndirectX;
    table[CPU6502::OPC::STA_IndirectY]       = &&STA_IndirectY;
    table[CPU6502::OPC::STX_ZeroPage]        = &&STX_ZeroPage;
    table[CPU6502::OPC::STX_ZeroPageY]       = &&STX_ZeroPageY;
    table[CPU6502::OPC::STX_Absolute]        = &&STX_Absolute;
    table[CPU6502::OPC::STY_ZeroPage]        = &&STY_ZeroPage;
    table[CPU6502::OPC::STY_ZeroPageX]       = &&STY_ZeroPageX;
    table[CPU6502::OPC::STY_Absolute]        = &&STY_Absolute;
    table[CPU6502::OPC::TAX]                 = &&TAX;
    table[CPU6502::OPC::TAY]                 = &&TAY;
    table[CPU6502::OPC::TYA]                 = &&TYA;
    table[CPU6502::OPC::TSX]                 = &&TSX;
    table[CPU6502::OPC::TXA]                 = &&TXA;
    table[CPU6502::OPC::TXS]                 = &&TXS;
    for (std::size_t i = 0; i < 0x100; i++)
    {
        if (table[i] == nullptr)
        {
            table[i] = &&Break;
        }
    }

    goto *table[_cpu.Fetch().raw()];
ADC_Immediate:
    _cpu.ADC_Immediate();
    goto *table[_cpu.Fetch().raw()];
ADC_ZeroPage:
    _cpu.ADC_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
ADC_ZeroPageX:
    _cpu.ADC_ZeroPageX();
    goto *table[_cpu.Fetch().raw()];
ADC_Absolute:
    _cpu.ADC_Absolute();
    goto *table[_cpu.Fetch().raw()];
ADC_AbsoluteX:
    _cpu.ADC_AbsoluteX();
    goto *table[_cpu.Fetch().raw()];
ADC_AbsoluteY:
    _cpu.ADC_AbsoluteY();
    goto *table[_cpu.Fetch().raw()];
ADC_IndirectX:
    _cpu.ADC_IndirectX();
    goto *table[_cpu.Fetch().raw()];
ADC_IndirectY:
    _cpu.ADC_IndirectY();
    goto *table[_cpu.Fetch().raw()];
AND_Immediate:
    _cpu.AND_Immediate();
    goto *table[_cpu.Fetch().raw()];
AND_ZeroPage:
    _cpu.AND_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
AND_ZeroPageX:
    _cpu.AND_ZeroPageX();
    goto *table[_cpu.Fetch().raw()];
AND_Absolute:
    _cpu.AND_Absolute();
    goto *table[_cpu.Fetch().raw()];
AND_AbsoluteX:
    _cpu.AND_AbsoluteX();
    goto *table[_cpu.Fetch().raw()];
AND_AbsoluteY:
    _cpu.AND_AbsoluteY();
    goto *table[_cpu.Fetch().raw()];
AND_IndirectX:
    _cpu.AND_IndirectX();
    goto *table[_cpu.Fetch().raw()];
AND_IndirectY:
    _cpu.AND_IndirectY();
    goto *table[_cpu.Fetch().raw()];
ASL_Accumulator:
    _cpu.ASL_Accumulator();
    goto *table[_cpu.Fetch().raw()];
ASL_ZeroPage:
    _cpu.ASL_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
ASL_ZeroPageX:
    _cpu.ASL_ZeroPageX();
    goto *table[_cpu.Fetch().raw()];
ASL_Absolute:
    _cpu.ASL_Absolute();
    goto *table[_cpu.Fetch().raw()];
ASL_AbsoluteX:
    _cpu.ASL_AbsoluteX();
    goto *table[_cpu.Fetch().raw()];
BCC:
    _cpu.BCC();
    goto *table[_cpu.Fetch().raw()];
BCS:
    _cpu.BCS();
    goto *table[_cpu.Fetch().raw()];
BEQ:
    _cpu.BEQ();
    goto *table[_cpu.Fetch().raw()];
BIT_ZeroPage:
    _cpu.BIT_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
BIT_Absolute:
    _cpu.BIT_Absolute();
    goto *table[_cpu.Fetch().raw()];
BMI:
    _cpu.BMI();
    goto *table[_cpu.Fetch().raw()];
BNE:
    _cpu.BNE();
    goto *table[_cpu.Fetch().raw()];
BPL:
    _cpu.BPL();
    goto *table[_cpu.Fetch().raw()];
BRK:
    _cpu.BRK();
    goto *table[_cpu.Fetch().raw()];
BVC:
    _cpu.BVC();
    goto *table[_cpu.Fetch().raw()];
BVS:
    _cpu.BVS();
    goto *table[_cpu.Fetch().raw()];
CLC:
    _cpu.CLC();
    goto *table[_cpu.Fetch().raw()];
CLD:
    _cpu.CLD();
    goto *table[_cpu.Fetch().raw()];
CLI:
    _cpu.CLI();
    goto *table[_cpu.Fetch().raw()];
CLV:
    _cpu.CLV();
    goto *table[_cpu.Fetch().raw()];
CMP_Immediate:
    _cpu.CMP_Immediate();
    goto *table[_cpu.Fetch().raw()];
CMP_ZeroPage:
    _cpu.CMP_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
CMP_ZeroPageX:
    _cpu.CMP_ZeroPageX();
    goto *table[_cpu.Fetch().raw()];
CMP_Absolute:
    _cpu.CMP_Absolute();
    goto *table[_cpu.Fetch().raw()];
CMP_AbsoluteX:
    _cpu.CMP_AbsoluteX();
    goto *table[_cpu.Fetch().raw()];
CMP_AbsoluteY:
    _cpu.CMP_AbsoluteY();
    goto *table[_cpu.Fetch().raw()];
CMP_IndirectX:
    _cpu.CMP_IndirectX();
    goto *table[_cpu.Fetch().raw()];
CMP_IndirectY:
    _cpu.CMP_IndirectY();
    goto *table[_cpu.Fetch().raw()];
CPX_Immediate:
    _cpu.CPX_Immediate();
    goto *table[_cpu.Fetch().raw()];
CPX_ZeroPage:
    _cpu.CPX_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
CPX_Absolute:
    _cpu.CPX_Absolute();
    goto *table[_cpu.Fetch().raw()];
CPY_Immediate:
    _cpu.CPY_Immediate();
    goto *table[_cpu.Fetch().raw()];
CPY_ZeroPage:
    _cpu.CPY_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
CPY_Absolute:
    _cpu.CPY_Absolute();
    goto *table[_cpu.Fetch().raw()];
DEC_ZeroPage:
    _cpu.DEC_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
DEC_ZeroPageX:
    _cpu.DEC_ZeroPageX();
    goto *table[_cpu.Fetch().raw()];
DEC_Absolute:
    _cpu.DEC_Absolute();
    goto *table[_cpu.Fetch().raw()];
DEC_AbsoluteX:
    _cpu.DEC_AbsoluteX();
    goto *table[_cpu.Fetch().raw()];
DEX:
    _cpu.DEX();
    goto *table[_cpu.Fetch().raw()];
DEY:
    _cpu.DEY();
    goto *table[_cpu.Fetch().raw()];
EOR_Immediate:
    _cpu.EOR_Immediate();
    goto *table[_cpu.Fetch().raw()];
EOR_ZeroPage:
    _cpu.EOR_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
EOR_ZeroPageX:
    _cpu.EOR_ZeroPageX();
    goto *table[_cpu.Fetch().raw()];
EOR_Absolute:
    _cpu.EOR_Absolute();
    goto *table[_cpu.Fetch().raw()];
EOR_AbsoluteX:
    _cpu.EOR_AbsoluteX();
    goto *table[_cpu.Fetch().raw()];
EOR_AbsoluteY:
    _cpu.EOR_AbsoluteY();
    goto *table[_cpu.Fetch().raw()];
EOR_IndirectX:
    _cpu.EOR_IndirectX();
    goto *table[_cpu.Fetch().raw()];
EOR_IndirectY:
    _cpu.EOR_IndirectY();
    goto *table[_cpu.Fetch().raw()];
INC_ZeroPage:
    _cpu.INC_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
INC_ZeroPageX:
    _cpu.INC_ZeroPageX();
    goto *table[_cpu.Fetch().raw()];
INC_Absolute:
    _cpu.INC_Absolute();
    goto *table[_cpu.Fetch().raw()];
INC_AbsoluteX:
    _cpu.INC_AbsoluteX();
    goto *table[_cpu.Fetch().raw()];
INX:
    _cpu.INX();
    goto *table[_cpu.Fetch().raw()];
INY:
    _cpu.INY();
    goto *table[_cpu.Fetch().raw()];
JMP_Absolute:
    _cpu.JMP_Absolute();
    goto *table[_cpu.Fetch().raw()];
JMP_Indirect:
    _cpu.JMP_Indirect();
    goto *table[_cpu.Fetch().raw()];
JSR:
    _cpu.JSR();
    goto *table[_cpu.Fetch().raw()];
LDA_Immediate:
    _cpu.LDA_Immediate();
    goto *table[_cpu.Fetch().raw()];
LDA_ZeroPage:
    _cpu.LDA_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
LDA_ZeroPageX:
    _cpu.LDA_ZeroPageX();
    goto *table[_cpu.Fetch().raw()];
LDA_Absolute:
    _cpu.LDA_Absolute();
    goto *table[_cpu.Fetch().raw()];
LDA_AbsoluteX:
    _cpu.LDA_AbsoluteX();
    goto *table[_cpu.Fetch().raw()];
LDA_AbsoluteY:
    _cpu.LDA_AbsoluteY();
    goto *table[_cpu.Fetch().raw()];
LDA_IndirectX:
    _cpu.LDA_IndirectX();
    goto *table[_cpu.Fetch().raw()];
LDA_IndirectY:
    _cpu.LDA_IndirectY();
    goto *table[_cpu.Fetch().raw()];
LDX_Immediate:
    _cpu.LDX_Immediate();
    goto *table[_cpu.Fetch().raw()];
LDX_ZeroPage:
    _cpu.LDX_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
LDX_ZeroPageY:
    _cpu.LDX_ZeroPageY();
    goto *table[_cpu.Fetch().raw()];
LDX_Absolute:
    _cpu.LDX_Absolute();
    goto *table[_cpu.Fetch().raw()];
LDX_AbsoluteY:
    _cpu.LDX_AbsoluteY();
    goto *table[_cpu.Fetch().raw()];
LDY_Immediate:
    _cpu.LDY_Immediate();
    goto *table[_cpu.Fetch().raw()];
LDY_ZeroPage:
    _cpu.LDY_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
LDY_ZeroPageY:
    _cpu.LDY_ZeroPageY();
    goto *table[_cpu.Fetch().raw()];
LDY_Absolute:
    _cpu.LDY_Absolute();
    goto *table[_cpu.Fetch().raw()];
LDY_AbsoluteY:
    _cpu.LDY_AbsoluteY();
    goto *table[_cpu.Fetch().raw()];
LSR_Accumulator:
    _cpu.LSR_Accumulator();
    goto *table[_cpu.Fetch().raw()];
LSR_ZeroPage:
    _cpu.LSR_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
LSR_ZeroPageY:
    _cpu.LSR_ZeroPageY();
    goto *table[_cpu.Fetch().raw()];
LSR_Absolute:
    _cpu.LSR_Absolute();
    goto *table[_cpu.Fetch().raw()];
LSR_AbsoluteY:
    _cpu.LSR_AbsoluteY();
    goto *table[_cpu.Fetch().raw()];
NOP:
    _cpu.NOP();
    goto *table[_cpu.Fetch().raw()];
ORA_Immediate:
    _cpu.ORA_Immediate();
    goto *table[_cpu.Fetch().raw()];
ORA_ZeroPage:
    _cpu.ORA_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
ORA_ZeroPageX:
    _cpu.ORA_ZeroPageX();
    goto *table[_cpu.Fetch().raw()];
ORA_Absolute:
    _cpu.ORA_Absolute();
    goto *table[_cpu.Fetch().raw()];
ORA_AbsoluteX:
    _cpu.ORA_AbsoluteX();
    goto *table[_cpu.Fetch().raw()];
ORA_AbsoluteY:
    _cpu.ORA_AbsoluteY();
    goto *table[_cpu.Fetch().raw()];
ORA_IndirectX:
    _cpu.ORA_IndirectX();
    goto *table[_cpu.Fetch().raw()];
ORA_IndirectY:
    _cpu.ORA_IndirectY();
    goto *table[_cpu.Fetch().raw()];
PHA:
    _cpu.PHA();
    goto *table[_cpu.Fetch().raw()];
PHP:
    _cpu.PHP();
    goto *table[_cpu.Fetch().raw()];
PLA:
    _cpu.PLA();
    goto *table[_cpu.Fetch().raw()];
PLP:
    _cpu.PLP();
    goto *table[_cpu.Fetch().raw()];
ROL_Accumulator:
    _cpu.ROL_Accumulator();
    goto *table[_cpu.Fetch().raw()];
ROL_ZeroPage:
    _cpu.ROL_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
ROL_ZeroPageX:
    _cpu.ROL_ZeroPageX();
    goto *table[_cpu.Fetch().raw()];
ROL_Absolute:
    _cpu.ROL_Absolute();
    goto *table[_cpu.Fetch().raw()];
ROL_AbsoluteX:
    _cpu.ROL_AbsoluteX();
    goto *table[_cpu.Fetch().raw()];
ROR_Accumulator:
    _cpu.ROR_Accumulator();
    goto *table[_cpu.Fetch().raw()];
ROR_ZeroPage:
    _cpu.ROR_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
ROR_ZeroPageX:
    _cpu.ROR_ZeroPageX();
    goto *table[_cpu.Fetch().raw()];
ROR_Absolute:
    _cpu.ROR_Absolute();
    goto *table[_cpu.Fetch().raw()];
ROR_AbsoluteX:
    _cpu.ROR_AbsoluteX();
    goto *table[_cpu.Fetch().raw()];
RTI:
    _cpu.RTI();
    goto *table[_cpu.Fetch().raw()];
RTS:
    _cpu.RTS();
    goto *table[_cpu.Fetch().raw()];
SBC_Immediate:
    _cpu.SBC_Immediate();
    goto *table[_cpu.Fetch().raw()];
SBC_ZeroPage:
    _cpu.SBC_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
SBC_ZeroPageX:
    _cpu.SBC_ZeroPageX();
    goto *table[_cpu.Fetch().raw()];
SBC_Absolute:
    _cpu.SBC_Absolute();
    goto *table[_cpu.Fetch().raw()];
SBC_AbsoluteX:
    _cpu.SBC_AbsoluteX();
    goto *table[_cpu.Fetch().raw()];
SBC_AbsoluteY:
    _cpu.SBC_AbsoluteY();
    goto *table[_cpu.Fetch().raw()];
SBC_IndirectX:
    _cpu.SBC_IndirectX();
    goto *table[_cpu.Fetch().raw()];
SBC_IndirectY:
    _cpu.SBC_IndirectY();
    goto *table[_cpu.Fetch().raw()];
SEC:
    _cpu.SEC();
    goto *table[_cpu.Fetch().raw()];
SED:
    _cpu.SED();
    goto *table[_cpu.Fetch().raw()];
SEI:
    _cpu.SEI();
    goto *table[_cpu.Fetch().raw()];
STA_ZeroPage:
    _cpu.STA_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
STA_ZeroPageX:
    _cpu.STA_ZeroPageX();
    goto *table[_cpu.Fetch().raw()];
STA_Absolute:
    _cpu.STA_Absolute();
    goto *table[_cpu.Fetch().raw()];
STA_AbsoluteX:
    _cpu.STA_AbsoluteX();
    goto *table[_cpu.Fetch().raw()];
STA_AbsoluteY:
    _cpu.STA_AbsoluteY();
    goto *table[_cpu.Fetch().raw()];
STA_IndirectX:
    _cpu.STA_IndirectX();
    goto *table[_cpu.Fetch().raw()];
STA_IndirectY:
    _cpu.STA_IndirectY();
    goto *table[_cpu.Fetch().raw()];
STX_ZeroPage:
    _cpu.STX_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
STX_ZeroPageY:
    _cpu.STX_ZeroPageY();
    goto *table[_cpu.Fetch().raw()];
STX_Absolute:
    _cpu.STX_Absolute();
    goto *table[_cpu.Fetch().raw()];
STY_ZeroPage:
    _cpu.STY_ZeroPage();
    goto *table[_cpu.Fetch().raw()];
STY_ZeroPageX:
    _cpu.STY_ZeroPageX();
    goto *table[_cpu.Fetch().raw()];
STY_Absolute:
    _cpu.STY_Absolute();
    goto *table[_cpu.Fetch().raw()];
TAX:
    _cpu.TAX();
    goto *table[_cpu.Fetch().raw()];
TAY:
    _cpu.TAY();
    goto *table[_cpu.Fetch().raw()];
TYA:
    _cpu.TYA();
    goto *table[_cpu.Fetch().raw()];
TSX:
    _cpu.TSX();
    goto *table[_cpu.Fetch().raw()];
TXA:
    _cpu.TXA();
    goto *table[_cpu.Fetch().raw()];
TXS:
    _cpu.TXS();
    goto *table[_cpu.Fetch().raw()];

Break:
    auto instr = _cpu.Peek();
    std::cout << "OP not supported" << std::endl;
}
