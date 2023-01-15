#include "DACSetup.h"

void DACSetup(int BaseVoltage) {

  AttachClock(1, 0x21); 

  DAC->CTRLA.reg = DAC_CTRLA_SWRST;  //Reset
  while (DAC->CTRLA.reg & DAC_CTRLA_SWRST)
    ;

  DAC->CTRLB.reg = DAC_CTRLB_EOEN | DAC_CTRLB_IOEN | DAC_CTRLB_REFSEL_AVCC;  //Enable external and internal refferences
  DAC->CTRLA.reg = DAC_CTRLA_ENABLE;                                         //Enable the DAC

  DAC->DATA.reg = BaseVoltage;  //Set up the DAC output value
}