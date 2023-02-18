
#include "Speeduino.h"

const int arramm = 6000;  //How many values to store
const int delayms = 100;  //Delay between each read sequence
const int PosPin = A0;    //Positive Pin
const int NegPin = 127;   //Set to 127 to compare to GND
const int Gain = 1;       //Gain
const int DivSpeed = 3;   //Set to at least 3, higher value better for lower frequencies

float array[arramm] = {};
int16_t arstored = 0;  //tracks how many values are stored


void setup() {

  AnalogBeginOsc(DivSpeed);
  CompAttachADC(PosPin, Gain, NegPin);
  Serial.begin(200000);
}



/*  Repeating code  */
void loop() {



  ADC->SWTRIG.bit.START = true;  //Start reading again


  while (arstored < arramm) {
    collectloop();
  }
  arstored = 0;

  while (arstored < arramm) {
    AdjustLoop();
  }
  arstored = 0;

  while (arstored < arramm) {
    printloop();
  };

  arstored = 0;

  delay(delayms);
}


void collectloop() {

  while (ADC->INTFLAG.reg == ADC_INTFLAG_RESRDY) {};
  array[arstored] = ADC->RESULT.reg;
  ADC->SWTRIG.bit.START = true;
  arstored += 1;
}

void AdjustLoop() {
  array[arstored] = array[arstored] * 3.3f / (4096.0f) * Gain;
  arstored += 1;
}


void printloop() {

  Serial.println((array[arstored]), 3);
  arstored += 1;
}
