#ifndef ADCSetup_h
#define ADCSetup_h

#include <Arduino.h>

void ADCSetup(bool DacRef, int Res, int Samp, int ADCClk, int ADCDiv, int BaseV, bool Freerun, bool PreDiv);
void genericClockSetup(int clk, int dFactor, bool DoubleSpeed);
void AttachClock(int clk, int clkid);
void AttachADC(int ADCpin = 0, bool IDACRefon = 0, int gain = 1);  
void FastAttachADC(int ADCpin = 0, bool IDACRefon = 0);
void GainINIT(int Gain); 
void DACSetup(int BaseV);
void AnalogBegin(int resolution = 12, bool midphase = 0, bool Freerun = 0);
int FastAnalogRead(int pin);
int AnalogCollect();
void CompAttachADC(int ADCpin = 0, int Gain = 1, int NegatPin = 127);
void AnalogBeginOsc(int dividor = 3);
  
#endif
