/*
 *
 * File: Measure_rms.ino
 * Purpose: TrueRMS library example project
 * Version: 1.0.2
 * Date: 23-05-2019
 * URL: https://github.com/MartinStokroos/TrueRMS
 * License: MIT License
 *
 *
 * This example illustrates the measurement of the rms value of a signal at the ADC input. To test, apply a sine- or a 
 * square wave of 50Hz/60Hz with 1V amplitude, biased on 2.5Vdc to input ADC0. The dcBias reading should be stable around 
 * the value 512 decimal (the middle of the ADC range) and the rms value of the sine wave should read about 0.71V and for a 
 * square wave about 1.00V.
 * 
 * The number of samples used to capture the input signal, must be a whole number. The sample window, expressed in 
 * number of samples, must have a length equal to at least one cycle of the input signal. If this is not the case, 
 * slow fluctuations in the rms and power readings will occure.
 * 
*/

#include <TrueRMS.h>
#include <digitalWriteFast.h>
#include <MCP3202.h>
#include "SPI.h"
#define LPERIOD 100    // loop period time in us. In this case 1.0ms
#define ADC_INPUT 0     // define the used ADC input channel
//#define RMS_WINDOW 40   // rms window of 40 samples, means 2 periods @50Hz
#define RMS_WINDOW 500   // rms window of 50 samples, means 3 periods @60Hz

#define PIN_DEBUG 4


unsigned long nextLoop;
int adcVal;
int cnt=0;
float VoltRange = 5.00; // The full scale value is set to 5.00 Volts but can be changed when using an
                        // input scaling circuit in front of the ADC.

Rms readRms; // create an instance of Rms.
MCP3202 adc = MCP3202(10);

void setup() {
  // run once:
  Serial.begin(9600);
  pinMode(PIN_DEBUG, OUTPUT);
  adc.begin();

  // configure for automatic base-line restoration and continuous scan mode:
  //readRms.begin(VoltRange, RMS_WINDOW, ADC_10BIT, BLR_ON, CNT_SCAN);
  digitalWriteFast(PIN_DEBUG, HIGH);
  //readRms.begin(VoltRange, RMS_WINDOW, ADC_10BIT, BLR_OFF, CNT_SCAN);
  digitalWriteFast(PIN_DEBUG, LOW);
  
  // configure for no base-line restauration and single scan mode:
  readRms.begin(VoltRange, RMS_WINDOW, ADC_12BIT, BLR_ON, CNT_SCAN);
  
  readRms.start(); //start measuring
  
  nextLoop = micros() + LPERIOD; // Set the loop timer variable for the next loop interval.
  }



void loop() {
  // run repeatedly:
  unsigned int vectorDatos[500];
  adcVal=0;
  for(int i = 0; i< 500; i++)
  {
    adcVal = adc.readChannel(0); // read the ADC.
    readRms.update(adcVal);    
  }
  readRms.publish();
  Serial.println(readRms.rmsVal,3);
  //readRms.update(adcVal); // update
  
}

// end of Measure_rms.ino
