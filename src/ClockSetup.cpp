#include "ClockSetup.h"

void genericClockSetup(int clk, int dFactor, bool DoubleSpeed) {
    

if (DoubleSpeed) {

    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN |         // Enable the generic clock
                        GCLK_CLKCTRL_GEN_GCLK1 |     // Select GCLK1 using either external XOSC32K or internal OSC32K oscillator depending on the board
                        //GCLK_CLKCTRL_GEN_GCLK2 |     // Select GCLK2 using the OSCULP32K ultra low power 32k oscillator
                        GCLK_CLKCTRL_ID_FDPLL;       // Connect GCLK1 to GCLK_DPLL input
    
    SYSCTRL->DPLLCTRLB.reg = SYSCTRL_DPLLCTRLB_REFCLK_GCLK;     // Select GCLK_DPLL as the clock source
    
    SYSCTRL->DPLLRATIO.reg = SYSCTRL_DPLLRATIO_LDRFRAC(11) |    // Generate a 96MHz DPLL clock source from the external 32kHz crystal
                             SYSCTRL_DPLLRATIO_LDR(2928);       // Frequency = 32.768kHz * (2928 + 1 + 11/16) = 96MHz
    
    SYSCTRL->DPLLCTRLA.reg = SYSCTRL_DPLLCTRLA_ENABLE;          // Enable the Digital Phase Locked Loop (DPLL)
    while (!SYSCTRL->DPLLSTATUS.bit.LOCK);                      // Wait for the DPLL to achieve lock



  REG_GCLK_GENDIV = GCLK_GENDIV_DIV(dFactor) | GCLK_GENDIV_ID(clk);  // Select Generic Clock (GCLK) 4
  while (GCLK->STATUS.bit.SYNCBUSY)
    ;  // Wait for synchronization

  REG_GCLK_GENCTRL = GCLK_GENCTRL_IDC |          // Set the duty cycle to 50/50 HIGH/LOW
                     GCLK_GENCTRL_GENEN |        // Enable GCLK4
                     GCLK_GENCTRL_SRC(0x08) |  // Set the 48MHz clock source
                     GCLK_GENCTRL_ID(clk);    // Select GCLK4




} else {
    

  REG_GCLK_GENDIV = GCLK_GENDIV_DIV(dFactor) | GCLK_GENDIV_ID(clk);  // Select Generic Clock (GCLK) 4
  while (GCLK->STATUS.bit.SYNCBUSY)
    ;  // Wait for synchronization

  REG_GCLK_GENCTRL = GCLK_GENCTRL_IDC |          // Set the duty cycle to 50/50 HIGH/LOW
                     GCLK_GENCTRL_GENEN |        // Enable GCLK4
                     GCLK_GENCTRL_SRC_DFLL48M |  // Set the 48MHz clock source
                     GCLK_GENCTRL_ID(clk);    // Select GCLK4


  while (GCLK->STATUS.bit.SYNCBUSY)
    ;  // Wait for synchronization

}

}



void AttachClock(int clk, int clkid) {
   GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(clkid) | GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN(clk);  //Attacch clock
}


