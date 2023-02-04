#ifndef ClockSetup_h
#define ClockSetup_h

#include <Arduino.h>


void genericClockSetup(int clk, int dFactor, bool DoubleSpeed);
void AttachClock(int clk, int clkid);
 

#endif