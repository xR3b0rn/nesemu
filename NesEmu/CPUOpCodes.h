
#pragma once

#include "CPU6502.h"

namespace NintendoEntertainmentSystem
{
	class CPUOpCodes
	{
	public:
		static void ADC(CPU6502* cpu, UINT8 data);
		static void ADC_ZeroPage(CPU6502* cpu);
		static void ADC_ZeroPageX(CPU6502* cpu);
		static void ADC_Absolute(CPU6502* cpu);
		static void ADC_AbsoluteX(CPU6502* cpu);
		static void ADC_AbsoluteY(CPU6502* cpu);
		static void ADC_IndirectX(CPU6502* cpu);
		static void ADC_IndirectY(CPU6502* cpu);

		static void AND(CPU6502* cpu, UINT8 data);
		static void AND_ZeroPage(CPU6502* cpu);
		static void AND_ZeroPageX(CPU6502* cpu);
		static void AND_Absolute(CPU6502* cpu);
		static void AND_AbsoluteX(CPU6502* cpu);
		static void AND_AbsoluteY(CPU6502* cpu);
		static void AND_IndirectX(CPU6502* cpu);
		static void AND_IndirectY(CPU6502* cpu);

		static void ASL(CPU6502* cpu, UINT8 data, bool carrý);
		static void ASL_Accumulator(CPU6502* cpu);
		static void ASL_ZeroPage(CPU6502* cpu);
		static void ASL_ZeroPageX(CPU6502* cpu);
		static void ASL_AbsoluteX(CPU6502* cpu);
		static void ASL_AbsoluteY(CPU6502* cpu);



		static void BRK(CPU6502* cpu, UINT8 data);
		static void BRK_Immediate(CPU6502* cpu);


		static void LDA_Immediate(CPU6502* cpu);
		static void LDA_ZeroPage(CPU6502* cpu);
		static void LDA_ZeroPageX(CPU6502* cpu);
		static void LDA_Absolute(CPU6502* cpu);
		static void LDA_AbsoluteX(CPU6502* cpu);
		static void LDA_AbsoluteY(CPU6502* cpu);
		static void LDA_IndirectX(CPU6502* cpu);
		static void LDA_IndirectY(CPU6502* cpu);

		static void STA_ZeroPage(CPU6502* cpu);
		static void STA_ZeroPageX(CPU6502* cpu);
		static void STA_Absolute(CPU6502* cpu);
		static void STA_AbsoluteX(CPU6502* cpu);
		static void STA_AbsoluteY(CPU6502* cpu);
		static void STA_IndirectX(CPU6502* cpu);
		static void STA_IndirectY(CPU6502* cpu);

	private:
		static void LDA(CPU6502* cpu, UINT8 data);
		static void STA(CPU6502* cpu, UINT8 data);
	};
}
