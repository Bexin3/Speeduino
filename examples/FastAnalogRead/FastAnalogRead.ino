
#include "ADCSetup.h"



void setup() {
  AnalogBegin();
  Serial.begin(115200);
}



/*  Repeating code  */
void loop() {
  Serial.println(FastAnalogRead(A0));
}


