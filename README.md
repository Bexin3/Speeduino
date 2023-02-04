Compatible with SAMD21, more description will be added soon, check examples to use the code. Its still in alpha.
Tested with Arduino Zero and Seeduino Xiao m0+
With centered analog read you can have relative ground on A0 which is half of supply voltage to compare against.

Function descriptions and time they take:
Simplified:

AnalogBegin(); - starts the ADC and attaches it to clock number 3. You can add one number inside to set resolution, deffault is 12 bit, possible are 8 10 and 12, then if you add one it will enable mode that centers values at half of the supply voltage, which now appears at pin A0, so you have negative and positive values, and after if you add 1 ADC will run in a freerun mode - it will keep taking reads again and again. Full form is AnalogBegin(Resolution, Centering, Freerun) ~ 30us

FastAnalogRead(pin); - Attaches the Analog pin and reads it, returns an integer. ~ 3us

AttachADC(pin, centering, gain) - Attaches to an analog pin and sets gain ~ 20us

FastAttachADC(pin, centering) - Attaches to an analog pin ~ 3us, less than FastAnalogRead

AnalogCollect() - Reads and collects an analog value from last attached pin ~ 3us, but bit less than FastAnalogRead


PWMBegin(pin, frequency) - begins running a pin at a specified frequency while attaching it to clock 8, minimum is 1 hz - calls PWMSetup. ~ 87us

PWMDuty(pin, dutycycle) - Sets the duty cycle at a specified number, in fractions. ~ 7us

PWMFrequency(pin, frequency) - changes the frequency, minimum 2 hz, if the pin previously had lower frequency selected may cause issues. ~40us

PWMSetup(pin, frequency, clock, Interrupts) - enables PWM, at a specidied pin, frequency which can go down to 0.00281 but it changes clock divisions, use clock 3-8. Enabling interrupts will make it call to Tch(); where you return duty cycle so it changes every cycle. ~ 124us, ~ 80us with frequency above 1hz


