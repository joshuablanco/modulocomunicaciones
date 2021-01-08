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
 * a slow fluctuation in the rms and power readings will occure.
 * 
*/
#include <Arduino.h>
#include "Adafruit_SHT31.h"
#include <Adafruit_INA219.h>
#include "SPI.h"
#include <TrueRMS.h>
#include <MCP3202.h>
MCP3202 adc = MCP3202(10);


#define LPERIOD 1000    // loop period time in us. In this case 1.0ms
//#define ADC_INPUT 2     // define the used ADC input channel
//#define RMS_WINDOW 40   // rms window of 40 samples, means 2 periods @50Hz
#define RMS_WINDOW 50   // rms window of 50 samples, means 3 periods @60Hz

unsigned long nextLoop;
int adcVal;
int cnt=0;
float VoltRange = 5.00; // The full scale value is set to 5.00 Volts but can be changed when using an
                        // input scaling circuit in front of the ADC.
float RmsMCP;
double RmsMCP_Real;
Rms readRms ; // create an instance of Rms.



void setup() {
  // run once:
  adc.begin();
  
  Serial.begin(9600);

  readRms.begin(VoltRange, RMS_WINDOW, ADC_12BIT, BLR_ON, CNT_SCAN);
  
  readRms.start(); //start measuring
  
  nextLoop = micros() + LPERIOD; // Set the loop timer variable for the next loop interval.
  }

void loop() {
  // run repeatedly:
  boolean FlagNo = false;
  FlagNo = false;
  while(FlagNo == false){
  unsigned long start1 = micros();
  adcVal = adc.readChannel(0); // read the ADC.
  readRms.update(adcVal); // update 
  //readRms.update(adcVal-512); // without automatic baseline restoration (BLR_OFF),

  cnt++;
  if(cnt >= 500) { // publish every 0.5s
    readRms.publish();
    RmsMCP = readRms.rmsVal;
    Serial.print(Fit_Rms(RmsMCP),3);
    Serial.print(", ");
    Serial.println(readRms.dcBias);
    cnt=0;
    FlagNo = true;
    //readRms.start();  // Restart the acquisition after publishing if the mode is single scan.
  }

  while(nextLoop > micros());  // wait until the end of the loop time interval
  nextLoop += LPERIOD;  // set next loop time to current time + LOOP_PERIOD

  unsigned long end1 = micros();
  unsigned long delta = end1 - start1;
  //Serial.println(delta);
  }
  delay(2000);
}


double Fit_Rms(float RmsVal){
  //RmsMCP_Real = 0.1653*pow(RmsVal,4)-0.4892*pow(RmsVal,3)+0.4305*pow(RmsVal,2)+0.8739*RmsVal+0.006338;
  RmsMCP_Real = -1.48*pow(RmsVal,4)+2.381*pow(RmsVal,3)-1.194*pow(RmsVal,2)+1.18*RmsVal-0.01193;
  return RmsMCP_Real; 
  
  }

// end of Measure_rms.ino
