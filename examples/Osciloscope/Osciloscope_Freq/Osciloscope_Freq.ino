
//Maximum meassurable frequency is about 100khz, while lowest is about 20hz with the current code.

#include "Speeduino.h"

const int arramm = 6400;  //How many values to store
const int delayms = 0;    //Delay between each read sequence
const int PosPin = A0;    //Positive Pin
const int NegPin = 127;   //Set to 18 to compare to GND
const int Gain = 1;       //Gain, 1, 2, 4, 8, 16 or 32
const int DivSpeed = 3;   //Set to at least 3, higher value better for lower frequencies

float minBound = 0.3f;  //Boundary fraction value has to go below to register as 0
float maxBound = 0.7f;  //Boundary fraction value has to go below to register as 1

int minBoundTemp;
int maxBoundTemp;

bool is1 = 0;

unsigned long timeBegin;
unsigned long timeEnd;
double timePassedPC;
double Frequency;

float array[arramm] = {};
int16_t arstored = 0;  //tracks how many values are stored

float minav;
float maxav;




void setup() {

  AnalogBeginOsc(DivSpeed);
  CompAttachADC(PosPin, Gain, NegPin);
  Serial.begin(200000);
}



/*  Repeating code  */
void loop() {



  ADC->SWTRIG.bit.START = true;  //Start reading again

  timeBegin = micros();

  while (arstored < arramm) {
    collectloop();
  };

  timeEnd = micros();

  arstored = 0;

  FindFreq();

  arstored = 0;


  AdjustLoop();


  printloop();


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
  minav = minav * 3.3f / (4096.0f) * Gain;
  maxav = maxav * 3.3f / (4096.0f) * Gain;
}


void printloop() {

  Serial.print("Minimal voltage: ");
  Serial.println(minav, 3);

  Serial.print("Maximum voltage: ");
  Serial.println(maxav, 3);

  Serial.print("Frequency: ");
  Serial.println(Frequency);
}

void FindFreq() {
  timePassedPC = (timeEnd - timeBegin - 3.0f);
  Frequency = 0.0;
  minav = array[0];
  maxav = array[0];
  if (array[0] - minav > (maxav - minav) / 2) { is1; };

  findMin();
  findMax();
  findMinMax();

  Freqn();
}

void findMin() {

  while (arstored < arramm) {

    if (array[arstored] < minav) { minav = array[arstored]; };
    arstored += 1;
  };

  arstored = 0;
}

void findMax() {

  while (arstored < arramm) {

    if (array[arstored] > maxav) { maxav = array[arstored]; };
    arstored += 1;
  };

  arstored = 0;
}

void findMinMax() {
  minBoundTemp = (maxav - minav) * minBound;
  maxBoundTemp = (maxav - minav) * maxBound;
}

void Freqn() {
  while (arstored < arramm) {
    if (is1 == true && array[arstored] < minBoundTemp) {
      is1 = false;
      Frequency += 1;
    } else if (is1 == false && array[arstored] > maxBoundTemp) {
      is1 = true;
      Frequency += 1;
    };
    arstored += 1;
  };
  arstored = 0;
  Frequency = Frequency * 1000000 / 2 / timePassedPC;
}
