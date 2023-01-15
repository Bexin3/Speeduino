Compatible with SAMD21, more description will be added soon, check examples to use the code. Its still in alpha.
Tested with Arduino Zero and Seeduino Xiao m0+
PWMDuty shouldnt take more than ~ 8us 
AnalogRead shouldnt take more than ~ 4us


Function descriptions and time they take:
Simplified:

AnalogBegin(); - starts the ADC and attaches it to clock number 3. You can add one number inside to set resolution, deffault is 12 bit, possible are 8 10 and 12, and after if you add 1 ADC will run in a freerun mode - it will keep taking reads again and again. ~ 30us

FastAnalogRead(pin); - Attaches the Analog pin and reads it, returns an integer. ~ 3us


PWMBegin(pin, frequency) - begins running a pin at a specified frequency while attaching it to clock 8, minimum is 1 hz - calls PWMSetup. ~ 87us

PWMDuty(pin, dutycycle) - Sets the duty cycle at a specified number, in fractions. ~ 7us

PWMFrequency(pin, frequency) - changes the frequency, minimum 1 hz. ~40us

PWMSetup(pin, frequency, clock, Interrupts) - enables PWM, at a specidied pin, frequency which can go down to 0.00281 but it changes clock divisions, use clock 3-8. Enabling interrupts will make it call to Tch(); where you return duty cycle so it changes every cycle. ~ 124us, ~ 80us with frequency above 1hz


