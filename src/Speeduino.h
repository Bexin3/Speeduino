#ifndef Speeduino_h
#define Speeduino_h

#include <Arduino.h>

void ADCSetup(bool DacRef, int Res, int Samp, int ADCClk, int ADCDiv, int BaseV, bool Freerun, bool PreDiv);
void genericClockSetup(int clk, int dFactor);
void AttachClock(int clk, int clkid);
void AttachADC(int ADCpin = 0, int gain = 1, bool IDACRefon = 0);  
void GainINIT(int Gain); 
void DACSetup(int BaseV);
void AnalogBegin(int resolution = 12, bool midphase = 0, bool Freerun = 0);
int FastAnalogRead(int pin);
void interset(uint32_t _tcNum, uint8_t _tcChannel);
void TCC0_Handler();
void TCC1_Handler();
void TCC2_Handler();
void TC3_Handler();
void TC4_Handler();
void TC5_Handler();
int Tch();
int PWMSetup(int PMpin, float Frequency, int CLKID, bool EnablePWMInt);
void PWMBegin(int pin, float frequency);
void PWMDuty(int pin, float dutycycle);
void SetupPWMPins(uint32_t ulPin, EPioType ulPeripheral);
void GCLKDIVCalc(float Frequency); 
void Prescaler(float Frequency);
void interset(uint32_t _tcNum, uint8_t _tcChannel);
void PWMFrequency(int pin, float frequency);
int AnalogCollect();


#endif
