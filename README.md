Compatible with SAMD21, more description will be added soon, check examples to use the code. Its still in alpha.
Tested with Arduino Zero and Seeduino Xiao m0+
PWMDuty shouldnt take more than ~ 8us 
AnalogRead shouldnt take more than ~ 4us


Function descriptions:
Simplified:
AnalogBegin(); - starts the ADC and attaches it to clock number 3. You can add one number inside to set resolution, deffault is 12 bit, possible are 8 10 and 12, and after if you add 1 ADC will run in a freerun mode - it will keep taking reads again and again.
AnalogRead(pin); - Attaches the Analog pin and reads it, returns an integer.
