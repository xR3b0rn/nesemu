
#include <CPU6502.h>
#include <Mapper000.h>

#define CATCH_CONFIG_MAIN
#include "Catch2.h"

using namespace NintendoEntertainmentSystem;

TEST_CASE("Push", "[CPU]")
{
    Mapper000 mapper(nullptr);
    CPU6502 cpu(&mapper);
    REQUIRE(cpu.StackPointer() == 0xFF_ui8);
    cpu.Push(0x12_ui8);
    REQUIRE(cpu.StackPointer() == 0xFE_ui8);
    REQUIRE(mapper.ReadMemory8(ui16_t(uint16_t(CPUMemory::Segs::Stack)) + 0xFF_ui16) == 0x12_ui8);
}
TEST_CASE("Pop", "[CPU]")
{
    Mapper000 mapper(nullptr);
    CPU6502 cpu(&mapper);
    REQUIRE(cpu.StackPointer() == 0xFF_ui8);
    cpu.Push(0x12_ui8);
    REQUIRE(cpu.StackPointer() == 0xFE_ui8);
    REQUIRE(mapper.ReadMemory8(ui16_t(uint16_t(CPUMemory::Segs::Stack)) + 0xFF_ui16) == 0x12_ui8);
    ui8_t v = cpu.Pop();
    REQUIRE(v == 0x12_ui8);
    REQUIRE(cpu.StackPointer() == 0xFF_ui8);
}
