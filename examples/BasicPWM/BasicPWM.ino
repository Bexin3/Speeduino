#include "Speeduino.h"

int pin = 13;
float frequency = 2.0f;


void setup() {
PWMBegin(pin, frequency);
}

void loop() {
PWMDuty(13, 0.2f); //second number is the duty cycle fraction
delay(10000);
PWMDuty(13, 1.0f);
delay(10000);
}
