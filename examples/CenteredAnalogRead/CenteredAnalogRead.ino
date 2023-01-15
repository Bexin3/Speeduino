#include "Speeduino.h"

void setup() {
AnalogBegin(12,1);
FastAttachADC(2, 1);
Serial.begin(9600);
}

void loop() {
Serial.println(AnalogCollect());
}