#ifndef ADCSetup_h
#define ADCSetup_h

#include <Arduino.h>

void ADCSetup(bool DacRef, int Res, int Samp, int ADCClk, int ADCDiv, int BaseV, bool Freerun);
void genericClockSetup(int clk, int dFactor);
void AttachClock(int clk, int clkid);
void AttachADC(int ADCpin, int gain, bool IDACRefon);  
void GainINIT(int Gain); 
void DACSetup(int BaseV);
void AnalogBegin(int resolution = 12, bool Midphase = 0, bool Freerun = 0);
int FastAnalogRead(int pin);

#endif
