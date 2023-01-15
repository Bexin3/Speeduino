#ifndef Interrupts_h
#define Interrupts_h

#include <Arduino.h>


void interset(uint32_t _tcNum, uint8_t _tcChannel);
void TCC0_Handler();
void TCC1_Handler();
void TCC2_Handler();
void TC3_Handler();
void TC4_Handler();
void TC5_Handler();
int Tch();



#endif