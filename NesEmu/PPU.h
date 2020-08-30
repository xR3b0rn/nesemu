
#pragma once

#include "Typedef.h"
#include "PPUMemory.h"

namespace NintendoEntertainmentSystem
{
    class PPU
    {
    private:
        enum class RegisterState
        {
            NO_STATE,
            FIRST,
            SECOND,
        };

    public:
        PPU();

        void doPreparationJob();
        void doMainJob();
        void setup();

        void set_PPUCTRL_register(ui8_t* pPPUCTRL);
        void set_PPUMASK_register(ui8_t* pPPUMASK);
        void set_PPSTATUS_register(ui8_t* pPPUSTATUS);
        void set_OAMADDR_register(ui8_t* pOAMADDR);
        void set_OAMDATA_register(ui8_t* pOAMDATA);
        void set_PPUSCROOL_register(ui8_t* pPPUSCROOL);
        void set_PPUADDR_register(ui8_t* pPPUADDR);
        void set_PPUDATA_register(ui8_t* pPPUDATA);
        void set_OAMDMA_register(ui8_t* pOAMDMA);

        void write_PPUCTRL_register(ui8_t data);
        void write_PPUMASK_register(ui8_t data);
        void write_OAMADDR_register(ui8_t data);
        void write_OAMDATA_register(ui8_t data);
        void write_PPUSCROLL_register(ui8_t data);
        void write_PPUADDR_register(ui8_t data);
        void write_PPUDATA_register(ui8_t data);
        void write_OAMDMA_register(ui8_t data);
        
        ui8_t read_PPUSTATUS_register();
        ui8_t read_OAMDATA_register(ui8_t data);
        ui8_t read_PPUDATA_register(ui8_t data);

    private:
        ui8_t* m_pPPUCTRL;
        ui8_t* m_pPPUMASK;
        ui8_t* m_pPPUSTATUS;
        ui8_t* m_pOAMADDR;
        ui8_t* m_pOAMDATA;
        ui8_t* m_pPPUSCROLL;
        ui8_t* m_pPPUADDR;
        ui8_t* m_pPPUDATA;
        ui8_t* m_pOAMDMA;

        RegisterState m_ePPUADDR_state;
        ui8_t m_prev_PPUADDR;

        PPUMemory m_Memory;
    };
}
