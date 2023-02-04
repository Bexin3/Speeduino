//This example converts incoming Analog signal into PWM using the libraries

#include "Speeduino.h"


const int ADCpin = A2;  //Pin for ADC, 0 cant be used in IDACRed mode as it has the DAC tied to it. AO can be used for ref GND for sound card with sound pin to ADCpin. On zero, 2 stands for A1
int PWMpin = 13;          //PWM pin, 13 is usually connected to LED so you can see it working.

const float Frequency = 10.0f;  //PWM frequency, higher the frequency lower resolution. Wont work below 0.00281 hz wont work
const int ADCDiv = 5;          //Set up dividor of time for ADC, with high PWM frequencies high values may let the Duty period only to change every few cycles, while too low values may lead to less stable output. Up to 255.
const int Samples = 1; //Ammount of ADC samples, can be 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 or 1028
int gain = 1;                  //1, 2, 4, 8, 16, 32, multiplier of input, only goes up to 16 in ICADRef mode
const int res = 12;            //Set up Resolution of the ADC, 8 or 10 or 12 bits

/*  Calibration  */
int16_t minv = -2048;     //Minimum meassured value of the input signal, make sure the value doesnt go below
int16_t maxv = 2047;  //Maximum meassured value og the input signal

/*  DAC AREF */
const bool IDACRef = 1;     //Use DAC as a reference instead of GND
const int BaseV = 512;      //0-1024 base voltage, 512 works the best as VCC/2

const bool Interrupt = 1;  //Enable PWM Interrupts

const int ADCClk = 3;  //Selects ADC clock generator, both to be between 3-8
const int PWMClk = 4;  //Selects PWM clock generator, they cant be the same.

//Not to be changed
int16_t Range;       //Value dividor here Select between 3-8
int16_t Analog;  //Analog read values go here
int Period;      //Time period calculated here


void setup() {


  Range = (maxv - minv);
  Period = PWMSetup(PWMpin, Frequency, PWMClk, 1);  //Sets up PWM
  ADCSetup(IDACRef, res, Samples, ADCClk, ADCDiv, BaseV, 0, 0);                                       
  AttachADC(ADCpin, IDACRef, gain);                                   

                   
}


//Shared TCC handler
int Tch() {
  ADC->INTFLAG.reg = ADC_INTFLAG_RESRDY;  //Wait for new analog value to be ready
  Analog = ADC->RESULT.reg;               //Write it down
  ADC->SWTRIG.bit.START = true;           //Start reading again
return (Period * (Analog - minv) / Range);    //Value to be set for next Period
}


/*  Repeating code  */
void loop() {
}


