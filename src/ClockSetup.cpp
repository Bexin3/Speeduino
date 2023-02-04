#include "ClockSetup.h"

void genericClockSetup(int clk, int dFactor, bool DoubleSpeed) {
    
if (DoubleSpeed) {

GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID(1);
while (GCLK->STATUS.bit.SYNCBUSY);

// Set DPLL ratio to 1 MHz * (95 + 1) = 96 MHz
SYSCTRL->DPLLRATIO.reg = SYSCTRL_DPLLRATIO_LDRFRAC(0) | SYSCTRL_DPLLRATIO_LDR(95);

// Configure DPLL to disregard phase lock and select GCLK as source
SYSCTRL->DPLLCTRLB.reg = SYSCTRL_DPLLCTRLB_LBYPASS | SYSCTRL_DPLLCTRLB_WUF | SYSCTRL_DPLLCTRLB_REFCLK(SYSCTRL_DPLLCTRLB_REFCLK_GCLK_Val);

// Enable DPLL
SYSCTRL->DPLLCTRLA.reg |= SYSCTRL_DPLLCTRLA_ENABLE;



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




