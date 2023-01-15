#include "ClockSetup.h"

void genericClockSetup(int clk, int dFactor) {

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



void AttachClock(int clk, int clkid) {
   GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(clkid) | GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN(clk);  //Attacch clock
}