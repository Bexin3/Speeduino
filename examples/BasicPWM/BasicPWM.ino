#include "Speeduino.h"

int pin = 13;
float frequency = 2.0f;


void setup() {
PWMBegin(pin, frequency);
}

void loop() {
PWMDuty(13, 0.2f); //second number is the duty cycle fraction
delay(10000);
PWMFrequency(13, 20.0f);
PWMDuty(13, 0.8f);
delay(10000);
PWMFrequency(13, 2.0f);
}
