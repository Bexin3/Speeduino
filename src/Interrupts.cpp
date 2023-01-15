#include "Interrupts.h"



uint8_t TCChannel;


void interset(uint32_t _tcNum, uint8_t _tcChannel) {
TCChannel = _tcChannel;
  switch (_tcNum) {
    case (0):
      {
        NVIC_SetPriority(TCC0_IRQn, 3);
        NVIC_EnableIRQ(TCC0_IRQn);
      }
    case (1):
      {
        NVIC_SetPriority(TCC1_IRQn, 3);
        NVIC_EnableIRQ(TCC1_IRQn);
      }
    case (2):
      {
        NVIC_SetPriority(TCC2_IRQn, 3);
        NVIC_EnableIRQ(TCC2_IRQn);
      }
    case (3):
      {
        NVIC_SetPriority(TC3_IRQn, 3);
        NVIC_EnableIRQ(TC3_IRQn);
      }
    case (4):
      {
        NVIC_SetPriority(TC4_IRQn, 3);
        NVIC_EnableIRQ(TC4_IRQn);
      }
    case (5):
      {
        NVIC_SetPriority(TC5_IRQn, 3);
        NVIC_EnableIRQ(TC5_IRQn);
      }
  };
}

#pragma weak Tch
int Tch() {
  return 0;
}

void TCC0_Handler() {  //gets activated when PWM cycle ends

  TCC0->CC[TCChannel].reg = Tch();

  TCC0->INTFLAG.bit.OVF = 1;  //reset interrupt flag
}


void TCC1_Handler() {  //gets activated when PWM cycle ends

  TCC1->CC[TCChannel].reg = Tch();

  TCC1->INTFLAG.bit.OVF = 1;  //reset interrupt flag
}


void TCC2_Handler() {  //gets activated when PWM cycle ends

  TCC2->CC[TCChannel].reg = Tch();

  TCC2->INTFLAG.bit.OVF = 1;  //reset interrupt flag
}

void TC3_Handler() {  //gets activated when PWM cycle ends

  TC3->COUNT8.CC[TCChannel].reg = Tch();

  TC3->COUNT8.INTFLAG.bit.OVF = 1;  //reset interrupt flag
}

void TC4_Handler() {  //gets activated when PWM cycle ends

  TC4->COUNT8.CC[TCChannel].reg = Tch();

  TC4->COUNT8.INTFLAG.bit.OVF = 1;  //reset interrupt flag
}

void TC5_Handler() {  //gets activated when PWM cycle ends

  TC5->COUNT8.CC[TCChannel].reg = Tch();

  TC5->COUNT8.INTFLAG.bit.OVF = 1;  //reset interrupt flag
}

