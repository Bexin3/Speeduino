#include "Speeduino.h"

void setup() {
AnalogBegin(12,A1);
FastAttachADC(2, A1);
Serial.begin(9600);
}

void loop() {
Serial.println(AnalogCollect());
}
