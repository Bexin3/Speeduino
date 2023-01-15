#include "PWMSetup.h"


int GCLKDIV;   //Dividor of PWM GCLK
int PRESC;     //Prescaler of PWM
int PRESVAL;   //Value by which this divides
int PRESCALC;  //Calculating which PRESC to use

PinDescription _pinDesc;
uint32_t _pinAttr;
uint32_t _tcNum;
uint8_t _tcChannel;
bool EnablePWMInt;

void PWMBegin(int pin, float frequency) {
PWMSetup(pin, frequency, 4, 0);
}

void PWMDuty(int pin, float dutycycle) {

PinDescription _pinDesc = g_APinDescription[pin];

_tcNum = GetTCNumber(_pinDesc.ulPWMChannel);
_tcChannel = GetTCChannelNumber(_pinDesc.ulPWMChannel);


if (_tcNum >= TCC_INST_NUM) {
    // Convert to 8-bit

    // -- Configure TC
 Tc *TCx = (Tc *)GetTC(_pinDesc.ulPWMChannel);
 TCx->COUNT8.CC[_tcChannel].reg = int(TCx->COUNT8.PER.reg*dutycycle);


} else {

  Tcc *TCCx = (Tcc *)GetTC(_pinDesc.ulPWMChannel);
  TCCx->CC[_tcChannel].reg = int(TCCx->PER.reg*dutycycle);


};

}

int PWMSetup(int PMpin, float Frequency, int CLKID, bool EnablePWMInt) {

PinDescription _pinDesc = g_APinDescription[PMpin];
_pinAttr = _pinDesc.ulPinAttribute;
_tcNum = GetTCNumber(_pinDesc.ulPWMChannel);
_tcChannel = GetTCChannelNumber(_pinDesc.ulPWMChannel);






  GCLKDIVCalc(Frequency);
  genericClockSetup(CLKID, GCLKDIV);  //Sets up PWM clock and divides it
  AttachClock(CLKID, int(26 + (_tcNum / 2)));
  Prescaler(Frequency);


  int period = int((48000000 / Frequency / PRESVAL / GCLKDIV) - 1);

  if (EnablePWMInt) {
    interset(_tcNum, _tcChannel);
  };


  //Which timer to use
  if (_pinAttr & PIN_ATTR_TIMER) {
    SetupPWMPins(PMpin, PIO_TIMER);
  } else {
    SetupPWMPins(PMpin, PIO_TIMER_ALT);
  }



  // Check which timer to use
  if (_tcNum >= TCC_INST_NUM) {
    // Convert to 8-bit

    // -- Configure TC
    Tc *TCx = (Tc *)GetTC(_pinDesc.ulPWMChannel);

    //reset
    TCx->COUNT8.CTRLA.bit.SWRST = 1;

    while (TCx->COUNT16.STATUS.bit.SYNCBUSY)
      ;

    // Disable TCx
    TCx->COUNT8.CTRLA.bit.ENABLE = 0;

    while (TCx->COUNT16.STATUS.bit.SYNCBUSY)
      ;

    // Set Timer counter Mode to 8 bits, normal PWM, PRESCALER_DIV1
    TCx->COUNT16.CTRLA.reg |= TC_CTRLA_MODE_COUNT8 | TC_CTRLA_WAVEGEN_NPWM | TC_CTRLA_PRESCALER_DIV1;

    while (TCx->COUNT16.STATUS.bit.SYNCBUSY)
      ;

    // Set the Dutycycle
    TCx->COUNT8.CC[_tcChannel].reg = (uint8_t)period;

    while (TCx->COUNT16.STATUS.bit.SYNCBUSY)
      ;

    // Set PER to _compareValue to match frequency
    // convert to 8-bit
    TCx->COUNT8.PER.reg = period >> 8;

    while (TCx->COUNT16.STATUS.bit.SYNCBUSY)
      ;

    /*  Set up interrupts  */
    TCx->COUNT8.EVCTRL.bit.OVFEO = 1;
    TCx->COUNT8.INTENSET.bit.OVF = 1;
    TCx->COUNT8.INTFLAG.bit.OVF = 1;



    TCx->COUNT8.CTRLA.bit.PRESCALER = PRESC;  //Set calculated prescaler value
    TCx->COUNT8.CTRLA.bit.ENABLE = 1;         //Turn timer on

    while (TCx->COUNT16.STATUS.bit.SYNCBUSY)
      ;
  } else {


    // -- Configure TCC
    Tcc *TCCx = (Tcc *)GetTC(_pinDesc.ulPWMChannel);

    // Disable TCCx
    TCCx->CTRLA.bit.ENABLE = 0;

    while (TCCx->SYNCBUSY.reg & TCC_SYNCBUSY_MASK)
      ;

    // Set prescaler
    //TCCx->CTRLA.reg |= _prescalerConfigBits;

    // while (TCCx->SYNCBUSY.reg & TCC_SYNCBUSY_MASK);

    // Set TCCx as normal PWM
    TCCx->WAVE.reg |= TCC_WAVE_WAVEGEN_NPWM;

    while (TCCx->SYNCBUSY.reg & TCC_SYNCBUSY_MASK)
      ;

    // Set the Dutycycle
    TCCx->CC[_tcChannel].reg = period;

    while (TCCx->SYNCBUSY.reg & TCC_SYNCBUSY_MASK)
      ;

    // Set PER to _compareValue to match frequency
    TCCx->PER.reg = period;

    while (TCCx->SYNCBUSY.reg & TCC_SYNCBUSY_MASK)
      ;

    /*  Set up interrupts  */
    TCCx->EVCTRL.bit.OVFEO = 1;
    TCCx->INTENSET.bit.OVF = 1;
    TCCx->INTFLAG.bit.OVF = 1;



    // Set prescaler value and enable
    TCCx->CTRLA.bit.PRESCALER = PRESC;
    TCCx->CTRLA.bit.ENABLE = 1;

    while (TCCx->SYNCBUSY.reg & TCC_SYNCBUSY_MASK)
      ;
  };

  return period;
}


void SetupPWMPins(uint32_t ulPin, EPioType ulPeripheral) {  //Set up PWM pins


  if (g_APinDescription[ulPin].ulPin & 1)  // is pin odd?
  {
    uint32_t temp;

    // Get whole current setup for both odd and even pins and remove odd one
    temp = (PORT->Group[g_APinDescription[ulPin].ulPort].PMUX[g_APinDescription[ulPin].ulPin >> 1].reg) & PORT_PMUX_PMUXE(0xF);
    // Set new muxing
    PORT->Group[g_APinDescription[ulPin].ulPort].PMUX[g_APinDescription[ulPin].ulPin >> 1].reg = temp | PORT_PMUX_PMUXO(ulPeripheral);
    // Enable port mux
    PORT->Group[g_APinDescription[ulPin].ulPort].PINCFG[g_APinDescription[ulPin].ulPin].reg |= PORT_PINCFG_PMUXEN | PORT_PINCFG_DRVSTR;
  } else  // even pin
  {
    uint32_t temp;

    temp = (PORT->Group[g_APinDescription[ulPin].ulPort].PMUX[g_APinDescription[ulPin].ulPin >> 1].reg) & PORT_PMUX_PMUXO(0xF);

    PORT->Group[g_APinDescription[ulPin].ulPort].PMUX[g_APinDescription[ulPin].ulPin >> 1].reg = temp | PORT_PMUX_PMUXE(ulPeripheral);

    PORT->Group[g_APinDescription[ulPin].ulPort].PINCFG[g_APinDescription[ulPin].ulPin].reg |= PORT_PINCFG_PMUXEN | PORT_PINCFG_DRVSTR;  // Enable port mux
  }
}


/*  Sets up interrupts based on the timer channel  */

void GCLKDIVCalc(float Frequency) {
  GCLKDIV = int(1.44 / Frequency);
  if (GCLKDIV < 1) { GCLKDIV = 1; };
  if (GCLKDIV > 255) { GCLKDIV = 255; };
}

void Prescaler(float Frequency) {
  PRESCALC = (1500 / Frequency);

  if (PRESCALC > 256) {
    PRESC = 7;
    PRESVAL = 1024;
  } else if (PRESCALC > 64) {
    PRESC = 6;
    PRESVAL = 256;
  } else if (PRESCALC > 16) {
    PRESC = 5;
    PRESVAL = 64;
  } else if (PRESCALC > 8) {
    PRESC = 4;
    PRESVAL = 16;
  } else if (PRESCALC > 4) {
    PRESC = 3;
    PRESVAL = 8;
  } else if (PRESCALC > 2) {
    PRESC = 2;
    PRESVAL = 4;
  } else if (PRESCALC > 1) {
    PRESC = 1;
    PRESVAL = 2;
  } else {
    PRESC = 0;
    PRESVAL = 1;
  };
}





