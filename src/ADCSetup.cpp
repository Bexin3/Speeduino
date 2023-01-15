#include "ADCSetup.h"



void ADCSetup(bool DacRef, int Res, int Samp, int ADCClk, int ADCDiv, int BaseV, bool Freerun) {

  genericClockSetup(ADCClk, ADCDiv);        //Sets up ADC clock and divides it
  AttachClock(ADCClk, 0x1E); 

  if (DacRef) {
  DACSetup(BaseV);  //Setup DAC if needed
  };

  /* Calibrate values. */
  uint32_t bias = (*((uint32_t *)ADC_FUSES_BIASCAL_ADDR) & ADC_FUSES_BIASCAL_Msk) >> ADC_FUSES_BIASCAL_Pos;
  uint32_t linearity = (*((uint32_t *)ADC_FUSES_LINEARITY_0_ADDR) & ADC_FUSES_LINEARITY_0_Msk) >> ADC_FUSES_LINEARITY_0_Pos;
  linearity |= ((*((uint32_t *)ADC_FUSES_LINEARITY_1_ADDR) & ADC_FUSES_LINEARITY_1_Msk) >> ADC_FUSES_LINEARITY_1_Pos) << 5;

  /* Wait for bus synchronization. */
  while (ADC->STATUS.bit.SYNCBUSY) {};

  /* Write the calibration data. */
  ADC->CALIB.reg = ADC_CALIB_BIAS_CAL(bias) | ADC_CALIB_LINEARITY_CAL(linearity);

  while (ADC->STATUS.bit.SYNCBUSY) {};

  /* Use the internal VCC reference. This is 1/2 of what's on VCCA.
   since VCCA is typically 3.3v, this is 1.65v.
*/
  ADC->REFCTRL.reg = ADC_REFCTRL_REFSEL_INTVCC1;




  /* Sets resolution and uses smallest possible divider so cDIV has the most control */

  if (Res == 8) {
    ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV4 | ADC_CTRLB_RESSEL_8BIT;
  } else if (Res == 10) {
    ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV4 | ADC_CTRLB_RESSEL_10BIT;
  } else if (Res == 12) {
    ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV4 | ADC_CTRLB_RESSEL_12BIT;
  } else {
    Serial.println("Unsupported resolution, change the value res to 8 10 or 12");
  };
  /*  Allows for Diff mode so values can be negative  */
  if (DacRef) {
    ADC->CTRLB.bit.DIFFMODE = 1;
  };

  /* Sampling time */
  ADC->SAMPCTRL.reg = log2(Samp);

  ADC->CTRLB.bit.FREERUN = Freerun;

  while (ADC->STATUS.bit.SYNCBUSY) {};



  /* Enable the ADC. */
  ADC->CTRLA.bit.ENABLE = true;





}



void AttachADC(int ADCpin, int gain, bool IDACRefon) {


  if (IDACRefon) {
    if (gain < 32) { gain = 2 * gain; };};

  if (gain == 1) {
    gain = 15;
  } else {
    gain = log2(gain / 2);
  }


  if (IDACRefon) {
    ADC->INPUTCTRL.reg = ADC_INPUTCTRL_GAIN(gain) | ADC_INPUTCTRL_MUXNEG(0) | ADC_INPUTCTRL_MUXPOS(ADCpin);
  } else {
    ADC->INPUTCTRL.reg = ADC_INPUTCTRL_GAIN(gain) | ADC_INPUTCTRL_MUXNEG_GND | ADC_INPUTCTRL_MUXPOS(ADCpin);
  };
}



void AnalogBegin(int resolution, bool Freerun) {
  ADCSetup(0, resolution, 1, 3, 5, 0, 0);
  ADC->INPUTCTRL.reg = ADC_INPUTCTRL_GAIN(15) | ADC_INPUTCTRL_MUXNEG_GND;
}




int FastAnalogRead(int pin) {
ADC->INPUTCTRL.reg = ADC_INPUTCTRL_MUXPOS(pin) | ADC_INPUTCTRL_GAIN(15) | ADC_INPUTCTRL_MUXNEG_GND;
//while (ADC->STATUS.bit.SYNCBUSY) {};
ADC->SWTRIG.bit.START = true;           //Start reading again
ADC->INTFLAG.reg = ADC_INTFLAG_RESRDY;  //Wait for new analog value to be ready
return(ADC->RESULT.reg);               //Write it down
}






