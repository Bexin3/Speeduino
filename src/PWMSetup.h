

#ifndef PWMSetup_h
#define PWMSetup_h

#include <Arduino.h>

int PWMSetup(int PMpin, float Frequency, int CLKID, bool EnablePWMInt);
void PWMBegin(int pin, float frequency);
void PWMDuty(int pin, float dutycycle);
void SetupPWMPins(uint32_t ulPin, EPioType ulPeripheral);
void GCLKDIVCalc(float Frequency); 
void Prescaler(float Frequency);
void interset(uint32_t _tcNum, uint8_t _tcChannel);
void genericClockSetup(int clk, int dFactor);
void AttachClock(int clk, int clkid);
void PWMFrequency(int pin, float frequency);




#endif
