
#include "CPU6502.h"
#include "IMapper.h"

using namespace NintendoEntertainmentSystem;

CPU6502::CPU6502(IMapper* mapper)
    : _mapper(mapper)
    , _reg_accumulator(0)
    , _reg_x_index(0)
    , _reg_y_index(0)
    , _reg_stack_pointer(0xFF)
    , _reg_program_counter(0)
    , _reg_status(0)
    , _cycles_count(0)
{
    ui8_t bl = mapper->ReadMemory8(0xFFFC_ui16);
    ui8_t bh = mapper->ReadMemory8(0xFFFD_ui16);
    _reg_program_counter = (bh.to<ui16_t>() << 8_ui16) | bl.to<ui16_t>();
}
CPU6502::OPC::Code CPU6502::Peek() const
{
    return _mapper->ReadMemory8(_reg_program_counter).to<OPC::Code>();
}
ui8_t CPU6502::Fetch()
{
    return _mapper->ReadMemory8(_reg_program_counter++);
}
ui64_t CPU6502::CyclesCount() const
{
    return _cycles_count;
}
void CPU6502::SetFlag(Flags flag, bool value)
{
    if (value)
    {
        _reg_status |= 1_ui8 << ui8_t(uint8_t(flag));
    }
    else
    {
        _reg_status &= ~(1_ui8 << ui8_t(uint8_t(flag)));
    }
}
ui8_t CPU6502::Accumulator() const
{
    return _reg_accumulator;
}
bool CPU6502::Flag(Flags flag) const
{
    return (_reg_status & (1_ui8 << ui8_t(uint32_t(flag)))) != 0_ui8;
}
void CPU6502::WriteMemory8Absolute(ui8_t data)
{
    address_t address(0);
    address  = Fetch().to<address_t>();
    address |= Fetch().to<address_t>() << 8_ui16;
    _mapper->WriteMemory8(address, data);
}
void CPU6502::WriteMemory8AbsoluteX(ui8_t data)
{
    address_t address;
    address  = Fetch().to<address_t>();
    address |= Fetch().to<address_t>() << 8_ui16;
    _mapper->WriteMemory8(address + _reg_x_index.to<ui16_t>(), data);
}
void CPU6502::WriteMemory8AbsoluteY(ui8_t data)
{
    address_t address;
    address  = Fetch().to<address_t>();
    address |= Fetch().to<address_t>() << 8_ui16;
    _mapper->WriteMemory8(address + _reg_y_index.to<ui16_t>(), data);
}
void CPU6502::WriteMemory8ZeroPage(ui8_t data)
{
    address_t address = Fetch().to<address_t>();
    _mapper->WriteMemory8(address, data);
}
void CPU6502::WriteMemory8ZeroPageX(ui8_t data)
{
    address_t address = Fetch().to<address_t>();
    _mapper->WriteMemory8(address + _reg_x_index.to<address_t>(), data);
}
void CPU6502::WriteMemory8ZeroPageY(ui8_t data)
{
    address_t address = Fetch().to<address_t>();
    _mapper->WriteMemory8(address + _reg_y_index.to<address_t>(), data);
}
void CPU6502::WriteMemory8IndirectX(ui8_t data)
{
    address_t address1 = Fetch().to<address_t>();
    address_t address2;
    address2  = _mapper->ReadMemory8(address1 + _reg_x_index.to<address_t>() * 2_ui16).to<address_t>();
    address2 |= _mapper->ReadMemory8(address1 + _reg_x_index.to<address_t>() * 2_ui16 + 1_ui16).to<address_t>();
    _mapper->WriteMemory8(address2, data);
}
void CPU6502::WriteMemory8IndirectY(ui8_t data)
{
    address_t address1 = Fetch().to<address_t>();
    address_t address2;
    address2  = _mapper->ReadMemory8(address1 + _reg_y_index.to<address_t>() * 2_ui16).to<address_t>();
    address2 |= _mapper->ReadMemory8(address1 + _reg_y_index.to<address_t>() * 2_ui16 + 1_ui16).to<address_t>();
    _mapper->WriteMemory8(address2, data);
}
void CPU6502::ReadModifyWriteAccumulator(std::function<ui8_t(ui8_t)>&& cb)
{
    _reg_accumulator = cb(_reg_accumulator);
}
void CPU6502::ReadModifyWriteXIndex(std::function<ui8_t(ui8_t)>&& cb)
{
    _reg_x_index = cb(_reg_x_index);
}
void CPU6502::ReadModifyWriteYIndex(std::function<ui8_t(ui8_t)>&& cb)
{
    _reg_y_index = cb(_reg_y_index);
}
void CPU6502::ReadModifyWriteMemory8Absolute(std::function<ui8_t(ui8_t)>&& cb)
{
    address_t address;
    address  = Fetch().to<address_t>();
    address |= Fetch().to<address_t>() << 8_ui16;
    ui8_t* data = _mapper->GetMemoryPointer(address);
    *data = cb(*data);
}
void CPU6502::ReadModifyWriteMemory8AbsoluteX(std::function<ui8_t(ui8_t)>&& cb)
{
    address_t address;
    address  = Fetch().to<address_t>();
    address |= Fetch().to<address_t>() << 8_ui16;
    ui8_t* data = _mapper->GetMemoryPointer(address + _reg_x_index.to<address_t>());
    *data = cb(*data);
}
void CPU6502::ReadModifyWriteMemory8AbsoluteY(std::function<ui8_t(ui8_t)>&& cb)
{
    address_t address;
    address  = Fetch().to<address_t>();
    address |= Fetch().to<address_t>() << 8_ui16;
    ui8_t* data = _mapper->GetMemoryPointer(address + _reg_y_index.to<address_t>());
    *data = cb(*data);
}
void CPU6502::ReadModifyWriteMemory8ZeroPage(std::function<ui8_t(ui8_t)>&& cb)
{
    address_t address = Fetch().to<address_t>();
    ui8_t* data = _mapper->GetMemoryPointer(address);
    *data = cb(*data);
}
void CPU6502::ReadModifyWriteMemory8ZeroPageX(std::function<ui8_t(ui8_t)>&& cb)
{
    address_t address = Fetch().to<address_t>();
    ui8_t* data = _mapper->GetMemoryPointer(address + _reg_x_index.to<address_t>());
    *data = cb(*data);
}
void CPU6502::ReadModifyWriteMemory8ZeroPageY(std::function<ui8_t(ui8_t)>&& cb)
{
    address_t address = Fetch().to<address_t>();
    ui8_t* data = _mapper->GetMemoryPointer(address + _reg_y_index.to<address_t>());
    *data = cb(*data);
}
void CPU6502::ReadModifyWriteMemory8IndirectX(std::function<ui8_t(ui8_t)>&& cb)
{
    address_t address1 = Fetch().to<address_t>();
    address_t address2;
    address2  = _mapper->ReadMemory8(address1 + (_reg_x_index * 2_ui8).to<address_t>()).to<address_t>();
    address2 |= _mapper->ReadMemory8(address1 + (_reg_x_index * 2_ui8 + 1_ui8).to<address_t>()).to<address_t>();
    ui8_t* data = _mapper->GetMemoryPointer(address2);
    *data = cb(*data);
}
void CPU6502::ReadModifyWriteMemory8IndirectY(std::function<ui8_t(ui8_t)>&& cb)
{
    address_t address1 = Fetch().to<address_t>();
    address_t address2;
    address2  = _mapper->ReadMemory8(address1 + (_reg_y_index * 2_ui8).to<address_t>()).to<address_t>();
    address2 |= _mapper->ReadMemory8(address1 + (_reg_y_index * 2_ui8 + 1_ui8).to<address_t>()).to<address_t>();
    ui8_t* data = _mapper->GetMemoryPointer(address2);
    *data = cb(*data);
}
ui8_t CPU6502::ReadMemory8Immediate()
{
    return Fetch();
}
ui8_t CPU6502::ReadMemory8Absolute()
{
    address_t address;
    address  = Fetch().to<address_t>();
    address |= Fetch().to<address_t>() << 8_ui16;
    return _mapper->ReadMemory8(address);
}
ui8_t CPU6502::ReadMemory8AbsoluteX()
{
    address_t address;
    address  = Fetch().to<address_t>();
    address |= Fetch().to<address_t>() << 8_ui16;
    return _mapper->ReadMemory8(address + _reg_x_index.to<address_t>());
}
ui8_t CPU6502::ReadMemory8AbsoluteY()
{
    address_t address;
    address  = Fetch().to<address_t>();
    address |= Fetch().to<address_t>() << 8_ui16;
    return _mapper->ReadMemory8(address + _reg_y_index.to<address_t>());
}
ui8_t CPU6502::ReadMemory8ZeroPage()
{
    address_t address = Fetch().to<address_t>();
    return _mapper->ReadMemory8(address);
}
ui8_t CPU6502::ReadMemory8ZeroPageX()
{
    address_t address = Fetch().to<address_t>();
    return _mapper->ReadMemory8(address + _reg_x_index.to<address_t>());
}
ui8_t CPU6502::ReadMemory8ZeroPageY()
{
    address_t address = Fetch().to<address_t>();
    return _mapper->ReadMemory8(address + _reg_y_index.to<address_t>());
}
ui8_t CPU6502::ReadMemory8IndirectX()
{
    address_t address1 = Fetch().to<address_t>();
    address_t address2;
    address2  = _mapper->ReadMemory8(address1 + (_reg_x_index * 2_ui8).to<address_t>()).to<address_t>();
    address2 |= _mapper->ReadMemory8(address1 + (_reg_x_index * 2_ui8 + 1_ui8).to<address_t>()).to<address_t>();
    return _mapper->ReadMemory8(address2);
}
ui8_t CPU6502::ReadMemory8IndirectY()
{
    address_t address1 = Fetch().to<address_t>();
    address_t address2;
    address2  = _mapper->ReadMemory8(address1 + (_reg_y_index * 2_ui8).to<address_t>()).to<address_t>();
    address2 |= _mapper->ReadMemory8(address1 + (_reg_y_index * 2_ui8 + 1_ui8).to<address_t>()).to<address_t>();
    return _mapper->ReadMemory8(address2);
}
ui16_t CPU6502::ProgramCounter() const
{
    return _reg_program_counter;
}
void CPU6502::Push(ui8_t data)
{
    if (_reg_stack_pointer == 0x00_ui8)
    {
        throw std::runtime_error("CPU6502::Pop: Can not push on the stack since the stack is full!");
    }
    _mapper->WriteMemory8(ui16_t(CPUMemory::Segs::Stack) + _reg_stack_pointer.to<ui16_t>(), data);
    _reg_stack_pointer--;
}
ui8_t CPU6502::Pop()
{
    if (_reg_stack_pointer == 0xFF_ui8)
    {
        throw std::runtime_error("CPU6502::Pop: Can not pop from the stack since the stack is empty!");
    }
    ui8_t result = _mapper->ReadMemory8(ui16_t(CPUMemory::Segs::Stack) + _reg_stack_pointer.to<ui16_t>());
    _reg_stack_pointer++;
    return result;
}
//
// * = Add 1 if page boundary is crossed
// ** = Add 1 if branch occurs to same page
// *** = Add 2 if branch occurs to different page
// Due to the CPU's specification, we have to considere these points. They are ignored yet.
//
void CPU6502::ADC(ui8_t data)
{
    ui8_t carry = Flag(Flags::Carry) ? 1_ui8 : 0_ui8;
    ui8_t value1 = _reg_accumulator + data + carry;
    ui16_t value2 = (_reg_accumulator + data + carry).to<ui16_t>();
    _reg_accumulator = value1;
    SetFlag(Flags::Negative, (value1 & 0x80_ui8) == 0x80_ui8);
    SetFlag(Flags::Zero, value1 == 0x00_ui8);
    SetFlag(Flags::Carry, 0xFF_ui16 < value2);
    SetFlag(Flags::Overflow, (value1 & 0x80_ui8).to<ui16_t>() == (value2 & 0x80_ui16));
}
void CPU6502::ADC_Immediate()
{
    ADC(ReadMemory8Immediate());
    _cycles_count += 2_ui64;
}
void CPU6502::ADC_ZeroPage()
{
    ADC(ReadMemory8ZeroPage());
    _cycles_count += 3_ui64;
}
void CPU6502::ADC_ZeroPageX()
{
    ADC(ReadMemory8ZeroPageX());
    _cycles_count += 4_ui64;
}
void CPU6502::ADC_Absolute()
{
    ADC(ReadMemory8Absolute());
    _cycles_count += 4_ui64;
}
void CPU6502::ADC_AbsoluteX()
{
    ADC(ReadMemory8AbsoluteX());
    // *
    _cycles_count += 4_ui64;
}
void CPU6502::ADC_AbsoluteY()
{
    ADC(ReadMemory8AbsoluteY());
    // *
    _cycles_count += 4_ui64;
}
void CPU6502::ADC_IndirectX()
{
    ADC(ReadMemory8IndirectX());
    _cycles_count += 6_ui64;
}
void CPU6502::ADC_IndirectY()
{
    ADC(ReadMemory8IndirectY());
    // *
    _cycles_count += 5_ui64;
}

void CPU6502::AND(ui8_t data)
{
    _reg_accumulator = _reg_accumulator & data;
    SetFlag(Flags::Negative, (_reg_accumulator & 0x80_ui8) == 0x80_ui8);
    SetFlag(Flags::Zero, _reg_accumulator == 0x00_ui8);
}
void CPU6502::AND_Immediate()
{
    AND(ReadMemory8Immediate());
    _cycles_count += 2_ui64;
}
void CPU6502::AND_ZeroPage()
{
    AND(ReadMemory8ZeroPage());
    _cycles_count += 3_ui64;
}
void CPU6502::AND_ZeroPageX()
{
    AND(ReadMemory8ZeroPageX());
    _cycles_count += 4_ui64;
}
void CPU6502::AND_Absolute()
{
    AND(ReadMemory8Absolute());
    _cycles_count += 4_ui64;
}
void CPU6502::AND_AbsoluteX()
{
    AND(ReadMemory8AbsoluteX());
    // *
    _cycles_count += 4_ui64;
}
void CPU6502::AND_AbsoluteY()
{
    AND(ReadMemory8AbsoluteY());
    // *
    _cycles_count += 4_ui64;
}
void CPU6502::AND_IndirectX()
{
    AND(ReadMemory8IndirectX());
    _cycles_count += 6_ui64;
}
void CPU6502::AND_IndirectY()
{
    AND(ReadMemory8IndirectY());
    // *
    _cycles_count += 5_ui64;
}

ui8_t CPU6502::ASL(ui8_t data)
{
    SetFlag(Flags::Carry, (data & 0x80_ui8) == 0x80_ui8);
    data <<= 1_ui8;
    SetFlag(Flags::Negative, (data & 0x80_ui8) == 0x80_ui8);
    SetFlag(Flags::Zero, data == 0x00_ui8);
    return data;
}
void CPU6502::ASL_Accumulator()
{
    ReadModifyWriteAccumulator([this](ui8_t data) { return ASL(data); });
    _cycles_count += 2_ui64;
}
void CPU6502::ASL_ZeroPage()
{
    ReadModifyWriteMemory8ZeroPage([this](ui8_t data) { return ASL(data); });
    _cycles_count += 5_ui64;
}
void CPU6502::ASL_ZeroPageX()
{
    ReadModifyWriteMemory8ZeroPageX([this](ui8_t data) { return ASL(data); });
    _cycles_count += 6_ui64;
}
void CPU6502::ASL_Absolute()
{
    ReadModifyWriteMemory8Absolute([this](ui8_t data) { return ASL(data); });
    _cycles_count += 6_ui64;
}
void CPU6502::ASL_AbsoluteX()
{
    ReadModifyWriteMemory8AbsoluteX([this](ui8_t data) { return ASL(data); });
    _cycles_count += 7_ui64;
}

void CPU6502::BCC()
{
    i8_t relative = Fetch().cast<i8_t>();
    if (!Flag(Flags::Carry))
    {
        _reg_program_counter = ((_reg_program_counter - 2_ui16).to<i16_t>() + relative.to<i16_t>()).cast<ui16_t>();
    }
    // **, ***
    _cycles_count += 2_ui64;
}
void CPU6502::BCS()
{
    i8_t relative = Fetch().cast<i8_t>();
    if (Flag(Flags::Carry))
    {
        _reg_program_counter = ((_reg_program_counter - 2_ui16).to<i16_t>() + relative.to<i16_t>()).cast<ui16_t>();
    }
    // **, ***
    _cycles_count += 2_ui64;
}
void CPU6502::BEQ()
{
    i8_t relative = Fetch().cast<i8_t>();
    if (Flag(Flags::Zero))
    {
        _reg_program_counter = ((_reg_program_counter - 2_ui16).to<i16_t>() + relative.to<i16_t>()).cast<ui16_t>();
    }
    // **, ***
    _cycles_count += 2_ui64;
}

void CPU6502::BIT(ui8_t data)
{
    ui8_t result = _reg_accumulator & data;
    SetFlag(Flags::Negative, (result & 0x80_ui8) == 0x80_ui8);
    SetFlag(Flags::Zero, result == 0x00_ui8);
}
void CPU6502::BIT_ZeroPage()
{
    BIT(ReadMemory8ZeroPage());
    _cycles_count += 3_ui64;
}
void CPU6502::BIT_Absolute()
{
    BIT(ReadMemory8Absolute());
    _cycles_count += 4_ui64;
}

void CPU6502::BMI()
{
    i8_t relative = Fetch().cast<i8_t>();
    if (Flag(Flags::Negative))
    {
        _reg_program_counter = ((_reg_program_counter - 2_ui16).to<i16_t>() + relative.to<i16_t>()).cast<ui16_t>();
    }
    // **, ***
    _cycles_count += 2_ui64;
}
void CPU6502::BNE()
{
    i8_t relative = Fetch().cast<i8_t>();
    if (!Flag(Flags::Zero))
    {
        _reg_program_counter = ((_reg_program_counter - 2_ui16).to<i16_t>() + relative.to<i16_t>()).cast<ui16_t>();
    }
    // **, ***
    _cycles_count += 2_ui64;
}
void CPU6502::BPL()
{
    i8_t relative = Fetch().cast<i8_t>();
    if (!Flag(Flags::Negative))
    {
        _reg_program_counter = ((_reg_program_counter - 2_ui16).to<i16_t>() + relative.to<i16_t>()).cast<ui16_t>();
    }
    // **, ***
    _cycles_count += 2_ui64;
}
void CPU6502::BRK()
{
    // Push return address on the stack
    ui8_t lh = ((_reg_program_counter - 1_ui16) & 0x00FF_ui16).to<ui8_t>();
    ui8_t uh = ((_reg_program_counter - 1_ui16) >> 0x0008_ui16).to<ui8_t>();
    Push(lh);
    Push(uh);
    // Push status on the stack
    ui8_t status = _reg_status;
    status |= 1_ui8 << ui8_t(uint8_t(Flags::Breakpoint));
    Push(status);
    // Set program counter to the IRQ + BRK routine
    lh = _mapper->ReadMemory8(0xFFFE_ui16);
    uh = _mapper->ReadMemory8(0xFFFF_ui16);
    _reg_program_counter = (uh.to<ui16_t>() << 16_ui16) | lh.to<ui16_t>();
}
void CPU6502::BVC()
{
    i8_t relative = Fetch().cast<i8_t>();
    if (!Flag(Flags::Overflow))
    {
        _reg_program_counter = ((_reg_program_counter - 2_ui16).to<i16_t>() + relative.to<i16_t>()).cast<ui16_t>();
    }
    // **, ***
    _cycles_count += 2_ui64;
}
void CPU6502::BVS()
{
    i8_t relative = Fetch().cast<i8_t>();
    if (Flag(Flags::Overflow))
    {
        _reg_program_counter = ((_reg_program_counter - 2_ui16).to<i16_t>() + relative.to<i16_t>()).cast<ui16_t>();
    }
    // **, ***
    _cycles_count += 2_ui64;
}
void CPU6502::CLC()
{
    SetFlag(Flags::Carry, false);
    _cycles_count += 2_ui64;
}
void CPU6502::CLD()
{
    SetFlag(Flags::BCDMode, false);
    _cycles_count += 2_ui64;
}

void CPU6502::CLI()
{
    SetFlag(Flags::IgnoreInterrupts, false);
    _cycles_count += 2_ui64;
}
void CPU6502::CLV()
{
    SetFlag(Flags::Overflow, false);
    _cycles_count += 2_ui64;
}

void CPU6502::CMP(ui8_t data)
{
    SetFlag(Flags::Negative, data < _reg_accumulator);
    SetFlag(Flags::Zero, _reg_accumulator == data);
    SetFlag(Flags::Carry, _reg_accumulator >= data);
}
void CPU6502::CMP_Immediate()
{
    CMP(ReadMemory8Immediate());
    _cycles_count += 2_ui64;
}
void CPU6502::CMP_ZeroPage()
{
    CMP(ReadMemory8ZeroPage());
    _cycles_count += 3_ui64;
}
void CPU6502::CMP_ZeroPageX()
{
    CMP(ReadMemory8ZeroPageX());
    _cycles_count += 4_ui64;
}
void CPU6502::CMP_Absolute()
{
    CMP(ReadMemory8Absolute());
    _cycles_count += 3_ui64;
}
void CPU6502::CMP_AbsoluteX()
{
    CMP(ReadMemory8AbsoluteX());
    // *
    _cycles_count += 4_ui64;
}
void CPU6502::CMP_AbsoluteY()
{
    CMP(ReadMemory8AbsoluteY());
    // *
    _cycles_count += 4_ui64;
}
void CPU6502::CMP_IndirectX()
{
    CMP(ReadMemory8IndirectX());
    _cycles_count += 6_ui64;
}
void CPU6502::CMP_IndirectY()
{
    CMP(ReadMemory8IndirectX());
    // *
    _cycles_count += 5_ui64;
}

void CPU6502::CPX(ui8_t data)
{
    SetFlag(Flags::Negative, data <= _reg_x_index);
    SetFlag(Flags::Zero, _reg_x_index == data);
    SetFlag(Flags::Carry, _reg_x_index < data);
}
void CPU6502::CPX_Immediate()
{
    CPX(ReadMemory8Immediate());
    _cycles_count += 2_ui64;
}
void CPU6502::CPX_ZeroPage()
{
    CPX(ReadMemory8ZeroPage());
    _cycles_count += 3_ui64;
}
void CPU6502::CPX_Absolute()
{
    CPX(ReadMemory8Absolute());
    _cycles_count += 4_ui64;
}

void CPU6502::CPY(ui8_t data)
{
    SetFlag(Flags::Negative, data <= _reg_y_index);
    SetFlag(Flags::Zero, _reg_y_index == data);
    SetFlag(Flags::Carry, _reg_y_index < data);
}
void CPU6502::CPY_Immediate()
{
    CPY(ReadMemory8Immediate());
    _cycles_count += 2_ui64;
}
void CPU6502::CPY_ZeroPage()
{
    CPY(ReadMemory8ZeroPage());
    _cycles_count += 3_ui64;
}
void CPU6502::CPY_Absolute()
{
    CPY(ReadMemory8Absolute());
    _cycles_count += 4_ui64;
}

ui8_t CPU6502::DEC(ui8_t data)
{
    data--;
    SetFlag(Flags::Negative, (data & 0x80_ui8) == 0x80_ui8);
    SetFlag(Flags::Zero, data == 0x00_ui8);
    return data;
}
void CPU6502::DEC_ZeroPage()
{
    ReadModifyWriteMemory8ZeroPage([this](ui8_t data) { return DEC(data); });
    _cycles_count += 5_ui64;
}
void CPU6502::DEC_ZeroPageX()
{
    ReadModifyWriteMemory8ZeroPageX([this](ui8_t data) { return DEC(data); });
    _cycles_count += 6_ui64;
}
void CPU6502::DEC_Absolute()
{
    ReadModifyWriteMemory8Absolute([this](ui8_t data) { return DEC(data); });
    _cycles_count += 6_ui64;
}
void CPU6502::DEC_AbsoluteX()
{
    ReadModifyWriteMemory8AbsoluteX([this](ui8_t data) { return DEC(data); });
    _cycles_count += 7_ui64;
}

void CPU6502::DEX()
{
    _reg_x_index--;
    SetFlag(Flags::Negative, (_reg_x_index & 0x80_ui8) == 0x80_ui8);
    SetFlag(Flags::Zero, _reg_x_index == 0x00_ui8);
    _cycles_count += 2_ui64;
}
void CPU6502::DEY()
{
    _reg_y_index--;
    SetFlag(Flags::Negative, (_reg_y_index & 0x80_ui8) == 0x80_ui8);
    SetFlag(Flags::Zero, _reg_y_index == 0x00_ui8);
    _cycles_count += 2_ui64;
}


void CPU6502::EOR(ui8_t data)
{
    _reg_accumulator = _reg_accumulator ^ data;
    SetFlag(Flags::Negative, (_reg_accumulator & 0x80_ui8) == 0x80_ui8);
    SetFlag(Flags::Zero, _reg_accumulator == 0x00_ui8);
}
void CPU6502::EOR_Immediate()
{
    EOR(ReadMemory8Immediate());
    _cycles_count += 2_ui64;
}
void CPU6502::EOR_ZeroPage()
{
    EOR(ReadMemory8ZeroPage());
    _cycles_count += 3_ui64;
}
void CPU6502::EOR_ZeroPageX()
{
    EOR(ReadMemory8ZeroPageX());
    _cycles_count += 4_ui64;
}
void CPU6502::EOR_Absolute()
{
    EOR(ReadMemory8Absolute());
    _cycles_count += 4_ui64;
}
void CPU6502::EOR_AbsoluteX()
{
    EOR(ReadMemory8AbsoluteX());
    // *
    _cycles_count += 4_ui64;
}
void CPU6502::EOR_AbsoluteY()
{
    EOR(ReadMemory8AbsoluteY());
    // *
    _cycles_count += 4_ui64;
}
void CPU6502::EOR_IndirectX()
{
    EOR(ReadMemory8IndirectX());
    _cycles_count += 6_ui64;
}
void CPU6502::EOR_IndirectY()
{
    EOR(ReadMemory8IndirectY());
    // *
    _cycles_count += 5_ui64;
}

ui8_t CPU6502::INC(ui8_t data)
{
    data++;
    SetFlag(Flags::Negative, (data & 0x80_ui8) == 0x80_ui8);
    SetFlag(Flags::Zero, data == 0x00_ui8);
    return data;
}
void CPU6502::INC_ZeroPage()
{
    ReadModifyWriteMemory8ZeroPage([this](ui8_t data) { return INC(data); });
    _cycles_count += 5_ui64;
}
void CPU6502::INC_ZeroPageX()
{
    ReadModifyWriteMemory8ZeroPageX([this](ui8_t data) { return INC(data); });
    _cycles_count += 6_ui64;
}
void CPU6502::INC_Absolute()
{
    ReadModifyWriteMemory8Absolute([this](ui8_t data) { return INC(data); });
    _cycles_count += 6_ui64;
}
void CPU6502::INC_AbsoluteX()
{
    ReadModifyWriteMemory8AbsoluteX([this](ui8_t data) { return INC(data); });
    _cycles_count += 7_ui64;
}

void CPU6502::INX()
{
    _reg_x_index++;
    SetFlag(Flags::Negative, (_reg_x_index & 0x80_ui8) == 0x80_ui8);
    SetFlag(Flags::Zero, _reg_x_index == 0x00_ui8);
    _cycles_count += 2_ui64;
}
void CPU6502::INY()
{
    _reg_y_index++;
    SetFlag(Flags::Negative, (_reg_y_index & 0x80_ui8) == 0x80_ui8);
    SetFlag(Flags::Zero, _reg_y_index == 0x00_ui8);
    _cycles_count += 2_ui64;
}

void CPU6502::JMP_Absolute()
{
    ui8_t pcl = Fetch();
    ui8_t pch = Fetch();
    _reg_program_counter = (pch.to<ui16_t>() << 16_ui16) | pcl.to<ui16_t>();
    _cycles_count += 3_ui64;
}
void CPU6502::JMP_Indirect()
{
    ui8_t l = Fetch();
    ui8_t h = Fetch();
    ui16_t address = (h.to<ui16_t>() << 16_ui16) | l.to<ui16_t>();
    ui8_t pcl = _mapper->ReadMemory8(address);
    ui8_t pch = _mapper->ReadMemory8(address + 1_ui16);
    _reg_program_counter = (pch.to<ui16_t>() << 16_ui16) | pcl.to<ui16_t>();
    _cycles_count += 5_ui64;
}

void CPU6502::JSR()
{
    // Store return address on the stack
    ui16_t ret_addr = _reg_program_counter + 1_ui16;
    ui8_t l = (ret_addr & 0x00FF_ui16).cast<ui8_t>();
    ui8_t h = (ret_addr >> 0x08_ui16).cast<ui8_t>();
    Push(h);
    Push(l);
    // Set program counter to new address
    ui8_t pcl = Fetch();
    ui8_t pch = Fetch();
    _reg_program_counter = (pch.to<ui16_t>() << 16_ui16) | pcl.to<ui16_t>();
    _cycles_count += 6_ui64;
}

void CPU6502::LDA(ui8_t data)
{
    _reg_accumulator = data;
    SetFlag(Flags::Negative, (_reg_accumulator & 0x80_ui8) == 0x80_ui8);
    SetFlag(Flags::Zero, _reg_accumulator == 0x00_ui8);
}
void CPU6502::LDA_Immediate()
{
    LDA(ReadMemory8Immediate());
    _cycles_count += 2_ui64;
}
void CPU6502::LDA_ZeroPage()
{
    LDA(ReadMemory8ZeroPage());
    _cycles_count += 3_ui64;
}
void CPU6502::LDA_ZeroPageX()
{
    LDA(ReadMemory8ZeroPageX());
    _cycles_count += 4_ui64;
}
void CPU6502::LDA_Absolute()
{
    LDA(ReadMemory8Absolute());
    _cycles_count += 4_ui64;
}
void CPU6502::LDA_AbsoluteX()
{
    LDA(ReadMemory8AbsoluteX());
    // *
    _cycles_count += 4_ui64;
}
void CPU6502::LDA_AbsoluteY()
{
    LDA(ReadMemory8AbsoluteY());
    // *
    _cycles_count += 4_ui64;
}
void CPU6502::LDA_IndirectX()
{
    LDA(ReadMemory8IndirectX());
    _cycles_count += 6_ui64;
}
void CPU6502::LDA_IndirectY()
{
    LDA(ReadMemory8IndirectY());
    // *
    _cycles_count += 5_ui64;
}

void CPU6502::LDX(ui8_t data)
{
    _reg_x_index = data;
    SetFlag(Flags::Zero, _reg_x_index == 0x00_ui8);
    SetFlag(Flags::Negative, (_reg_x_index & 0x80_ui8) == 0x80_ui8);
}
void CPU6502::LDX_Immediate()
{
    LDX(ReadMemory8Immediate());
    _cycles_count += 2_ui64;
}
void CPU6502::LDX_ZeroPage()
{
    LDX(ReadMemory8ZeroPage());
    _cycles_count += 3_ui64;
}
void CPU6502::LDX_ZeroPageY()
{
    LDX(ReadMemory8ZeroPageY());
    _cycles_count += 4_ui64;
}
void CPU6502::LDX_Absolute()
{
    LDX(ReadMemory8Absolute());
    _cycles_count += 4_ui64;
}
void CPU6502::LDX_AbsoluteY()
{
    LDX(ReadMemory8AbsoluteY());
    // *
    _cycles_count += 4_ui64;
}

void CPU6502::LDY(ui8_t data)
{
    _reg_y_index = data;
    SetFlag(Flags::Zero, _reg_y_index == 0x00_ui8);
    SetFlag(Flags::Negative, (_reg_y_index & 0x80_ui8) == 0x80_ui8);
}
void CPU6502::LDY_Immediate()
{
    LDY(ReadMemory8Immediate());
    _cycles_count += 2_ui64;
}
void CPU6502::LDY_ZeroPage()
{
    LDY(ReadMemory8ZeroPage());
    _cycles_count += 3_ui64;
}
void CPU6502::LDY_ZeroPageY()
{
    LDY(ReadMemory8ZeroPageY());
    _cycles_count += 4_ui64;
}
void CPU6502::LDY_Absolute()
{
    LDY(ReadMemory8Absolute());
    _cycles_count += 4_ui64;
}
void CPU6502::LDY_AbsoluteY()
{
    LDY(ReadMemory8AbsoluteY());
    // *
    _cycles_count += 4_ui64;
}
        
ui8_t CPU6502::LSR(ui8_t data)
{
    SetFlag(Flags::Carry, (data & 0x01_ui8) == 0x01_ui8);
    SetFlag(Flags::Negative, false);
    data >>= 1_ui8;
    SetFlag(Flags::Zero, data == 0_ui8);
    return data;
}
void CPU6502::LSR_Accumulator()
{
    ReadModifyWriteAccumulator([this](ui8_t data) { return LSR(data); });
    _cycles_count += 2_ui64;
}
void CPU6502::LSR_ZeroPage()
{
    ReadModifyWriteMemory8ZeroPage([this](ui8_t data) { return LSR(data); });
    _cycles_count += 5_ui64;
}
void CPU6502::LSR_ZeroPageY()
{
    ReadModifyWriteMemory8ZeroPageY([this](ui8_t data) { return LSR(data); });
    _cycles_count += 6_ui64;
}
void CPU6502::LSR_Absolute()
{
    ReadModifyWriteMemory8Absolute([this](ui8_t data) { return LSR(data); });
    _cycles_count += 6_ui64;
}
void CPU6502::LSR_AbsoluteY()
{
    ReadModifyWriteMemory8AbsoluteY([this](ui8_t data) { return LSR(data); });
    _cycles_count += 7_ui64;
}

void CPU6502::NOP()
{
    _cycles_count += 2_ui64;
}

void CPU6502::ORA(ui8_t data)
{
    _reg_accumulator = _reg_accumulator | data;
    SetFlag(Flags::Negative, (_reg_accumulator & 0x80_ui8) == 0x80_ui8);
    SetFlag(Flags::Zero, _reg_accumulator == 0x00_ui8);
}
void CPU6502::ORA_Immediate()
{
    ORA(ReadMemory8Immediate());
    _cycles_count += 2_ui64;
}
void CPU6502::ORA_ZeroPage()
{
    ORA(ReadMemory8ZeroPage());
    _cycles_count += 3_ui64;
}
void CPU6502::ORA_ZeroPageX()
{
    ORA(ReadMemory8ZeroPageX());
    _cycles_count += 4_ui64;
}
void CPU6502::ORA_Absolute()
{
    ORA(ReadMemory8Absolute());
    _cycles_count += 4_ui64;
}
void CPU6502::ORA_AbsoluteX()
{
    ORA(ReadMemory8AbsoluteX());
    // *
    _cycles_count += 4_ui64;
}
void CPU6502::ORA_AbsoluteY()
{
    ORA(ReadMemory8AbsoluteY());
    // *
    _cycles_count += 4_ui64;
}
void CPU6502::ORA_IndirectX()
{
    ORA(ReadMemory8IndirectX());
    _cycles_count += 6_ui64;
}
void CPU6502::ORA_IndirectY()
{
    ORA(ReadMemory8IndirectY());
    // *
    _cycles_count += 5_ui64;
}

void CPU6502::PHA()
{
    Push(_reg_accumulator);
    _cycles_count += 3_ui64;
}
void CPU6502::PHP()
{
    Push(_reg_status);
    _cycles_count += 3_ui64;
}
void CPU6502::PLA()
{
    _reg_accumulator = Pop();
    _cycles_count += 4_ui64;
}
void CPU6502::PLP()
{
    _reg_status = Pop();
    _cycles_count += 4_ui64;
}

ui8_t CPU6502::ROL(ui8_t data)
{
    ui8_t carry = Flag(Flags::Carry) ? 1_ui8 : 0_ui8;
    SetFlag(Flags::Carry, (data & 0x80_ui8) == 0x80_ui8);
    data <<= 1_ui8;
    data |= carry;
    SetFlag(Flags::Negative, (data & 0x80_ui8) == 0x80_ui8);
    SetFlag(Flags::Zero, data == 0x00_ui8);
    return data;
}
void CPU6502::ROL_Accumulator()
{
    ReadModifyWriteAccumulator([this](ui8_t data) { return ROL(data); });
    _cycles_count += 2_ui64;
}
void CPU6502::ROL_ZeroPage()
{
    ReadModifyWriteMemory8ZeroPage([this](ui8_t data) { return ROL(data); });
    _cycles_count += 5_ui64;
}
void CPU6502::ROL_ZeroPageX()
{
    ReadModifyWriteMemory8ZeroPageX([this](ui8_t data) { return ROL(data); });
    _cycles_count += 6_ui64;
}
void CPU6502::ROL_Absolute()
{
    ReadModifyWriteMemory8Absolute([this](ui8_t data) { return ROL(data); });
    _cycles_count += 6_ui64;
}
void CPU6502::ROL_AbsoluteX()
{
    ReadModifyWriteMemory8AbsoluteX([this](ui8_t data) { return ROL(data); });
    _cycles_count += 7_ui64;
}

ui8_t CPU6502::ROR(ui8_t data)
{
    ui8_t carry = Flag(Flags::Carry) ? 1_ui8 : 0_ui8;
    SetFlag(Flags::Carry, (data & 0x01_ui8) == 0x01_ui8);
    data >>= 1_ui8;
    data |= carry << 0x07_ui8;
    SetFlag(Flags::Negative, (data & 0x80_ui8) == 0x80_ui8);
    SetFlag(Flags::Zero, data == 0x00_ui8);
    return data;
}
void CPU6502::ROR_Accumulator()
{
    ReadModifyWriteAccumulator([this](ui8_t data) { return ROR(data); });
    _cycles_count += 2_ui64;
}
void CPU6502::ROR_ZeroPage()
{
    ReadModifyWriteMemory8ZeroPage([this](ui8_t data) { return ROR(data); });
    _cycles_count += 5_ui64;
}
void CPU6502::ROR_ZeroPageX()
{
    ReadModifyWriteMemory8ZeroPageX([this](ui8_t data) { return ROR(data); });
    _cycles_count += 6_ui64;
}
void CPU6502::ROR_Absolute()
{
    ReadModifyWriteMemory8Absolute([this](ui8_t data) { return ROR(data); });
    _cycles_count += 6_ui64;
}
void CPU6502::ROR_AbsoluteX()
{
    ReadModifyWriteMemory8AbsoluteX([this](ui8_t data) { return ROR(data); });
    _cycles_count += 7_ui64;
}

void CPU6502::RTI()
{
    _reg_status = Pop();
    ui8_t uh = Pop();
    ui8_t lh = Pop();
    _reg_program_counter = (uh.to<ui16_t>() << 16_ui16) | lh.to<ui16_t>() + 1_ui16;
    _cycles_count += 7_ui64;
}
void CPU6502::RTS()
{
    ui8_t uh = Pop();
    ui8_t lh = Pop();
    _reg_program_counter = (uh.to<ui16_t>() << 16_ui16) | lh.to<ui16_t>() + 1_ui16;
    _cycles_count += 6_ui64;
}

void CPU6502::SBC(ui8_t data)
{
    bool overflow = 127_i16 < (_reg_accumulator.cast<i8_t>().to<i16_t>() + data.cast<i8_t>().to<i16_t>()) < -128_i16;
    ui8_t carry = Flag(Flags::Carry) ? 0x00_ui8 : 0x01_ui8;
    _reg_accumulator = _reg_accumulator - data - carry;
    SetFlag(Flags::Carry, _reg_accumulator.cast<i8_t>() >= 0x00_i8);
    SetFlag(Flags::Overflow, overflow);
    SetFlag(Flags::Zero, _reg_accumulator == 0x00_ui8);
    SetFlag(Flags::Negative, (_reg_accumulator & 0x80_ui8) == 0x80_ui8);
}
void CPU6502::SBC_Immediate()
{
    SBC(ReadMemory8Immediate());
    _cycles_count += 2_ui64;
}
void CPU6502::SBC_ZeroPage()
{
    SBC(ReadMemory8ZeroPage());
    _cycles_count += 3_ui64;
}
void CPU6502::SBC_ZeroPageX()
{
    SBC(ReadMemory8ZeroPageX());
    _cycles_count += 4_ui64;
}
void CPU6502::SBC_Absolute()
{
    SBC(ReadMemory8Absolute());
    _cycles_count += 4_ui64;
}
void CPU6502::SBC_AbsoluteX()
{
    SBC(ReadMemory8AbsoluteX());
    // *
    _cycles_count += 4_ui64;
}
void CPU6502::SBC_AbsoluteY()
{
    SBC(ReadMemory8AbsoluteY());
    // *
    _cycles_count += 4_ui64;
}
void CPU6502::SBC_IndirectX()
{
    SBC(ReadMemory8IndirectX());
    _cycles_count += 6_ui64;
}
void CPU6502::SBC_IndirectY()
{
    SBC(ReadMemory8IndirectY());
    // *
    _cycles_count += 5_ui64;
}

void CPU6502::SEC()
{
    SetFlag(Flags::Carry, true);
    _cycles_count += 2_ui64;
}

void CPU6502::SED()
{
    SetFlag(Flags::BCDMode, true);
    _cycles_count += 2_ui64;
}
void CPU6502::SEI()
{
    SetFlag(Flags::IgnoreInterrupts, true);
    _cycles_count += 2_ui64;
}

void CPU6502::STA_ZeroPage()
{
    WriteMemory8ZeroPage(_reg_accumulator);
    _cycles_count += 3_ui64;
}
void CPU6502::STA_ZeroPageX()
{
    WriteMemory8ZeroPageX(_reg_accumulator);
    _cycles_count += 4_ui64;
}
void CPU6502::STA_Absolute()
{
    WriteMemory8Absolute(_reg_accumulator);
    _cycles_count += 4_ui64;
}
void CPU6502::STA_AbsoluteX()
{
    WriteMemory8AbsoluteX(_reg_accumulator);
    _cycles_count += 5_ui64;
}
void CPU6502::STA_AbsoluteY()
{
    WriteMemory8AbsoluteY(_reg_accumulator);
    _cycles_count += 5_ui64;
}
void CPU6502::STA_IndirectX()
{
    WriteMemory8IndirectX(_reg_accumulator);
    _cycles_count += 6_ui64;
}
void CPU6502::STA_IndirectY()
{
    WriteMemory8IndirectY(_reg_accumulator);
    _cycles_count += 6_ui64;
}

void CPU6502::STX_ZeroPage()
{
    WriteMemory8ZeroPage(_reg_x_index);
    _cycles_count += 3_ui64;
}
void CPU6502::STX_ZeroPageY()
{
    WriteMemory8ZeroPageY(_reg_x_index);
    _cycles_count += 4_ui64;
}
void CPU6502::STX_Absolute()
{
    WriteMemory8Absolute(_reg_x_index);
    _cycles_count += 4_ui64;
}

void CPU6502::STY_ZeroPage()
{
    WriteMemory8ZeroPage(_reg_y_index);
    _cycles_count += 3_ui64;
}
void CPU6502::STY_ZeroPageX()
{
    WriteMemory8ZeroPageX(_reg_y_index);
    _cycles_count += 4_ui64;
}
void CPU6502::STY_Absolute()
{
    WriteMemory8Absolute(_reg_y_index);
    _cycles_count += 4_ui64;
}

void CPU6502::TAX()
{
    _reg_x_index = _reg_accumulator;
    _cycles_count += 2_ui64;
}
void CPU6502::TAY()
{
    _reg_y_index = _reg_accumulator;
    _cycles_count += 2_ui64;
}
void CPU6502::TYA()
{
    _reg_accumulator = _reg_y_index;
    _cycles_count += 2_ui64;
}
void CPU6502::TSX()
{
    _reg_x_index = _reg_stack_pointer;
    _cycles_count += 2_ui64;
}
void CPU6502::TXA()
{
    _reg_accumulator = _reg_x_index;
    _cycles_count += 2_ui64;
}
void CPU6502::TXS()
{
    _reg_stack_pointer = _reg_x_index;
    _cycles_count += 2_ui64;
}
