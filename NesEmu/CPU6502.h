
#pragma once

#include <cstdint>
#include <functional>

#include "Typedef.h"
#include "IMapper.h"
#include "CPUMemory.h"
#include "Cartridge.h"

namespace NintendoEntertainmentSystem
{
    class CPU6502
    {
    public:
        struct OPC
        {
            enum Code
            {
                ADC_Immediate       = 0x69,
                ADC_ZeroPage        = 0x65,
                ADC_ZeroPageX       = 0x75,
                ADC_Absolute        = 0x6D,
                ADC_AbsoluteX       = 0x7D,
                ADC_AbsoluteY       = 0x79,
                ADC_IndirectX       = 0x61,
                ADC_IndirectY       = 0x71,
            
                AND_Immediate       = 0x29,
                AND_ZeroPage        = 0x25,
                AND_ZeroPageX       = 0x35,
                AND_Absolute        = 0x2D,
                AND_AbsoluteX       = 0x3D,
                AND_AbsoluteY       = 0x39,
                AND_IndirectX       = 0x21,
                AND_IndirectY       = 0x31,

                ASL_Accumulator     = 0x0A,
                ASL_ZeroPage        = 0x06,
                ASL_ZeroPageX       = 0x16,
                ASL_Absolute        = 0x0E,
                ASL_AbsoluteX       = 0x1E,

                BCC                 = 0x90,
                BCS                 = 0xB0,
                BEQ                 = 0xF0,

                BIT_ZeroPage        = 0x24,
                BIT_Absolute        = 0x2C,

                BMI                 = 0x30,
                BNE                 = 0xD0,
                BPL                 = 0x10,
                BRK                 = 0x00,
                BVC                 = 0x50,
                BVS                 = 0x70,
                CLC                 = 0x18,
                CLD                 = 0xD8,

                CLI                 = 0x58,
                CLV                 = 0xB8,

                CMP_Immediate       = 0xC9,
                CMP_ZeroPage        = 0xC5,
                CMP_ZeroPageX       = 0xD5,
                CMP_Absolute        = 0xCD,
                CMP_AbsoluteX       = 0xDD,
                CMP_AbsoluteY       = 0xD9,
                CMP_IndirectX       = 0xC1,
                CMP_IndirectY       = 0xD1,

                CPX_Immediate       = 0xE0,
                CPX_ZeroPage        = 0xE4,
                CPX_Absolute        = 0xEC,

                CPY_Immediate       = 0xC0,
                CPY_ZeroPage        = 0xC4,
                CPY_Absolute        = 0xCC,

                DEC_ZeroPage        = 0xC6,
                DEC_ZeroPageX       = 0xD6,
                DEC_Absolute        = 0xCE,
                DEC_AbsoluteX       = 0xDE,

                DEX                 = 0xCA,
                DEY                 = 0x88,

                EOR_Immediate       = 0x49,
                EOR_ZeroPage        = 0x45,
                EOR_ZeroPageX       = 0x55,
                EOR_Absolute        = 0x4D,
                EOR_AbsoluteX       = 0x5D,
                EOR_AbsoluteY       = 0x59,
                EOR_IndirectX       = 0x41,
                EOR_IndirectY       = 0x51,

                INC_ZeroPage        = 0xE6,
                INC_ZeroPageX       = 0xF6,
                INC_Absolute        = 0xEE,
                INC_AbsoluteX       = 0xFE,

                INX                 = 0xE8,
                INY                 = 0xC8,

                JMP_Absolute        = 0x4C,
                JMP_Indirect        = 0x6C,

                JSR                 = 0x20,

                LDA_Immediate       = 0xA9,
                LDA_ZeroPage        = 0xA5,
                LDA_ZeroPageX       = 0xB5,
                LDA_Absolute        = 0xAD,
                LDA_AbsoluteX       = 0xBD,
                LDA_AbsoluteY       = 0xB9,
                LDA_IndirectX       = 0xA1,
                LDA_IndirectY       = 0xB1,

                
                LDX_Immediate       = 0xA2,
                LDX_ZeroPage        = 0xA6,
                LDX_ZeroPageY       = 0xB6,
                LDX_Absolute        = 0xAE,
                LDX_AbsoluteY       = 0xBE,
                
                LDY_Immediate       = 0xA0,
                LDY_ZeroPage        = 0xA4,
                LDY_ZeroPageY       = 0xB4,
                LDY_Absolute        = 0xAC,
                LDY_AbsoluteY       = 0xBC,
                
                LSR_Accumulator     = 0x4A,
                LSR_ZeroPage        = 0x46,
                LSR_ZeroPageY       = 0x56,
                LSR_Absolute        = 0x4E,
                LSR_AbsoluteY       = 0x5E,
                
                NOP                 = 0xEA,
                
                ORA_Immediate       = 0x09,
                ORA_ZeroPage        = 0x05,
                ORA_ZeroPageX       = 0x15,
                ORA_Absolute        = 0x0D,
                ORA_AbsoluteX       = 0x1D,
                ORA_AbsoluteY       = 0x19,
                ORA_IndirectX       = 0x01,
                ORA_IndirectY       = 0x11,
                
                PHA                 = 0x48,
                PHP                 = 0x08,
                PLA                 = 0x68,
                PLP                 = 0x28,

                ROL_Accumulator     = 0x2A,
                ROL_ZeroPage        = 0x26,
                ROL_ZeroPageX       = 0x36,
                ROL_Absolute        = 0x2E,
                ROL_AbsoluteX       = 0x3E,

                ROR_Accumulator     = 0x6A,
                ROR_ZeroPage        = 0x66,
                ROR_ZeroPageX       = 0x76,
                ROR_Absolute        = 0x6E,
                ROR_AbsoluteX       = 0x7E,

                RTI                 = 0x40,
                RTS                 = 0x60,
                  
                SBC_Immediate       = 0xE9,
                SBC_ZeroPage        = 0xE5,
                SBC_ZeroPageX       = 0xF5,
                SBC_Absolute        = 0xED,
                SBC_AbsoluteX       = 0xFD,
                SBC_AbsoluteY       = 0xF9,
                SBC_IndirectX       = 0xE1,
                SBC_IndirectY       = 0xF1,

                SEC                 = 0x38,
                
                SED                 = 0xF8,
                SEI                 = 0x78,

                STA_ZeroPage        = 0x85,
                STA_ZeroPageX       = 0x95,
                STA_Absolute        = 0x8D,
                STA_AbsoluteX       = 0x9D,
                STA_AbsoluteY       = 0x99,
                STA_IndirectX       = 0x81,
                STA_IndirectY       = 0x91,

                STX_ZeroPage        = 0x86,
                STX_ZeroPageY       = 0x96,
                STX_Absolute        = 0x8E,

                STY_ZeroPage        = 0x84,
                STY_ZeroPageX       = 0x94,
                STY_Absolute        = 0x8C,

                TAX                 = 0xAA,
                TAY                 = 0xA8,
                TYA                 = 0x98,
                TSX                 = 0xBA,
                TXA                 = 0x8A,
                TXS                 = 0x9A,
            };
        };

        enum class Flags
            : std::size_t
        {
            Carry = 0,            // C
            Zero = 1,             // Z
            IgnoreInterrupts = 2, // I
            BCDMode = 3,          // D
            Breakpoint = 4,
            Overflow = 6,         // V
            Negative = 7          // N
        };

    public:
        CPU6502() = default;
        CPU6502(IMapper* mapper);
        
        void SetFlag(Flags flag, bool value);

        // getter
        OPC::Code Peek() const;
        ui8_t Fetch();
        ui8_t Accumulator() const;
        bool Flag(Flags flag) const;
        ui64_t CyclesCount() const;
        ui16_t ProgramCounter() const;
        
        void Push(ui8_t data);
        ui8_t Pop();

        void ADC(ui8_t data);
        void ADC_Immediate();
        void ADC_ZeroPage();
        void ADC_ZeroPageX();
        void ADC_Absolute();
        void ADC_AbsoluteX();
        void ADC_AbsoluteY();
        void ADC_IndirectX();
        void ADC_IndirectY();
        
        void AND(ui8_t data);
        void AND_Immediate();
        void AND_ZeroPage();
        void AND_ZeroPageX();
        void AND_Absolute();
        void AND_AbsoluteX();
        void AND_AbsoluteY();
        void AND_IndirectX();
        void AND_IndirectY();

        ui8_t ASL(ui8_t data);
        void ASL_Accumulator();
        void ASL_ZeroPage();
        void ASL_ZeroPageX();
        void ASL_Absolute();
        void ASL_AbsoluteX();

        void BCC();
        void BCS();
        void BEQ();

        void BIT(ui8_t data);
        void BIT_ZeroPage();
        void BIT_Absolute();

        void BMI();
        void BNE();
        void BPL();
        void BRK();
        void BVC();
        void BVS();
        void CLC();
        void CLD();

        void CLI();
        void CLV();

        void CMP(ui8_t data);
        void CMP_Immediate();
        void CMP_ZeroPage();
        void CMP_ZeroPageX();
        void CMP_Absolute();
        void CMP_AbsoluteX();
        void CMP_AbsoluteY();
        void CMP_IndirectX();
        void CMP_IndirectY();

        void CPX(ui8_t data);
        void CPX_Immediate();
        void CPX_ZeroPage();
        void CPX_Absolute();

        void CPY(ui8_t data);
        void CPY_Immediate();
        void CPY_ZeroPage();
        void CPY_Absolute();

        ui8_t DEC(ui8_t data);
        void DEC_ZeroPage();
        void DEC_ZeroPageX();
        void DEC_Absolute();
        void DEC_AbsoluteX();

        void DEX();
        void DEY();

        void EOR(ui8_t data);
        void EOR_Immediate();
        void EOR_ZeroPage();
        void EOR_ZeroPageX();
        void EOR_Absolute();
        void EOR_AbsoluteX();
        void EOR_AbsoluteY();
        void EOR_IndirectX();
        void EOR_IndirectY();

        ui8_t INC(ui8_t data);
        void INC_ZeroPage();
        void INC_ZeroPageX();
        void INC_Absolute();
        void INC_AbsoluteX();

        void INX();
        void INY();

        void JMP();
        void JMP_Absolute();
        void JMP_Indirect();

        void JSR();
        
        void LDA(ui8_t data);
        void LDA_Immediate();
        void LDA_ZeroPage();
        void LDA_ZeroPageX();
        void LDA_Absolute();
        void LDA_AbsoluteX();
        void LDA_AbsoluteY();
        void LDA_IndirectX();
        void LDA_IndirectY();


        void LDX(ui8_t data);
        void LDX_Immediate();
        void LDX_ZeroPage();
        void LDX_ZeroPageY();
        void LDX_Absolute();
        void LDX_AbsoluteY();
        
        void LDY(ui8_t data);
        void LDY_Immediate();
        void LDY_ZeroPage();
        void LDY_ZeroPageY();
        void LDY_Absolute();
        void LDY_AbsoluteY();
        
        ui8_t LSR(ui8_t data);
        void LSR_Accumulator();
        void LSR_ZeroPage();
        void LSR_ZeroPageY();
        void LSR_Absolute();
        void LSR_AbsoluteY();

        void NOP();
        
        void ORA(ui8_t data);
        void ORA_Immediate();
        void ORA_ZeroPage();
        void ORA_ZeroPageX();
        void ORA_Absolute();
        void ORA_AbsoluteX();
        void ORA_AbsoluteY();
        void ORA_IndirectX();
        void ORA_IndirectY();

        void PHA();
        void PHP();
        void PLA();
        void PLP();

        ui8_t ROL(ui8_t data);
        void ROL_Accumulator();
        void ROL_ZeroPage();
        void ROL_ZeroPageX();
        void ROL_Absolute();
        void ROL_AbsoluteX();

        ui8_t ROR(ui8_t data);
        void ROR_Accumulator();
        void ROR_ZeroPage();
        void ROR_ZeroPageX();
        void ROR_Absolute();
        void ROR_AbsoluteX();

        void RTI();
        void RTS();
        
        void SBC(ui8_t data);
        void SBC_Immediate();
        void SBC_ZeroPage();
        void SBC_ZeroPageX();
        void SBC_Absolute();
        void SBC_AbsoluteX();
        void SBC_AbsoluteY();
        void SBC_IndirectX();
        void SBC_IndirectY();

        void SEC();

        void SED();
        void SEI();

        void STA_ZeroPage();
        void STA_ZeroPageX();
        void STA_Absolute();
        void STA_AbsoluteX();
        void STA_AbsoluteY();
        void STA_IndirectX();
        void STA_IndirectY();

        void STX_ZeroPage();
        void STX_ZeroPageY();
        void STX_Absolute();

        void STY_ZeroPage();
        void STY_ZeroPageX();
        void STY_Absolute();

        void TAX();
        void TAY();
        void TYA();
        void TSX();
        void TXA();
        void TXS();

    private:
        // Write memory by different addressing modes
        void WriteMemory8Absolute(ui8_t data);
        void WriteMemory8AbsoluteX(ui8_t data);
        void WriteMemory8AbsoluteY(ui8_t data);
        void WriteMemory8ZeroPage(ui8_t data);
        void WriteMemory8ZeroPageX(ui8_t data);
        void WriteMemory8ZeroPageY(ui8_t data);
        void WriteMemory8IndirectX(ui8_t data);
        void WriteMemory8IndirectY(ui8_t data);

        // Read memory by different addressing modes
        void ReadModifyWriteAccumulator(std::function<ui8_t(ui8_t)>&& cb);
        void ReadModifyWriteXIndex(std::function<ui8_t(ui8_t)>&& cb);
        void ReadModifyWriteYIndex(std::function<ui8_t(ui8_t)>&& cb);
        void ReadModifyWriteMemory8Absolute(std::function<ui8_t(ui8_t)>&& cb);
        void ReadModifyWriteMemory8AbsoluteX(std::function<ui8_t(ui8_t)>&& cb);
        void ReadModifyWriteMemory8AbsoluteY(std::function<ui8_t(ui8_t)>&& cb);
        void ReadModifyWriteMemory8ZeroPage(std::function<ui8_t(ui8_t)>&& cb);
        void ReadModifyWriteMemory8ZeroPageX(std::function<ui8_t(ui8_t)>&& cb);
        void ReadModifyWriteMemory8ZeroPageY(std::function<ui8_t(ui8_t)>&& cb);
        void ReadModifyWriteMemory8IndirectX(std::function<ui8_t(ui8_t)>&& cb);
        void ReadModifyWriteMemory8IndirectY(std::function<ui8_t(ui8_t)>&& cb);

        ui8_t ReadMemory8Immediate();
        ui8_t ReadMemory8Absolute();
        ui8_t ReadMemory8AbsoluteX();
        ui8_t ReadMemory8AbsoluteY();
        ui8_t ReadMemory8ZeroPage();
        ui8_t ReadMemory8ZeroPageX();
        ui8_t ReadMemory8ZeroPageY();
        ui8_t ReadMemory8IndirectX();
        ui8_t ReadMemory8IndirectY();
        
        // Memory
        IMapper* _mapper;
        // Attributes
        ui8_t _reg_accumulator;
        ui8_t _reg_x_index;
        ui8_t _reg_y_index;
        ui8_t _reg_stack_pointer;
        ui16_t _reg_program_counter;
        ui8_t _reg_status;

        // cycles counter
        ui64_t _cycles_count;
    };
}
