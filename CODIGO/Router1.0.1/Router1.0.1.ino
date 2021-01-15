/****************** SERIAL WRITE ******************/
/****************** Router       ******************/
/****************** Lybraries    ******************/

#include <Arduino.h>
#include "Adafruit_SHT31.h"
#include <Adafruit_INA219.h>
#include <MCP3202.h>
#include "SPI.h"
#include <TrueRMS.h>
#include <SoftwareSerial.h>

MCP3202 adc = MCP3202(10);

const char HEADER = 'H';
const char TAIL = 'T';

#define LPERIOD 1000    // loop period time in us. In this case 1.0ms
#define ADC_INPUT1 1    // water pin 
#define ADC_INPUT 2     // define the used ADC input channel
#define RMS_WINDOW 500  // rms window of 50 samples, means 3 periods @60Hz
#define AVG_WINDOW 500  // window of 500 samples.  

/********* Values to Introduce (INPUTS) *********/
float Sensitivity = 0.1;  // Parameter to INPUT related with the current sensor characterizing
float VoltRange = 4.8;    // ADC full scale peak-to-peak is 5.00Volts measure in full operation
float ADC_Gain = 1;       // 1.05 related with the trigger
float Scale_Plot_Axis = 1;    // Scale Data to plot in the screen y-axis
 
/****Temperature init *****/
Adafruit_SHT31 sht31 = Adafruit_SHT31();
int heat = 0;

/**** Water Level init ****/
int sensorValue;

/**** Read RMS ****/
unsigned long nextLoop;
unsigned long Time_Ex;

unsigned int adcVal_0;
unsigned int adcVal_1;

int cnt=0;
int Inst_Value;

double VTC_Add;
double VTC_mean;
double RmsMCP_Real;

float V_mean;
float RmsMCP;
float VTC; //using

Rms2 readRms ;// create an instance of
Average MeasAvg; // 

/**** Plotting *****/
boolean Comp_State_Low = false;//using
boolean Comp_State_change = false; //using
boolean Comp_State = true;;//using
boolean last_Comp_State = HIGH;//using

float Num_Samples = 0;//using
float Num_Samples2 = 0;
float channel1_2_float;
float MaxCurrent; // using

int channel1_2 = 0;//A2 ATMEGA energy double checking 
int Peak_Val_Noff;//peak value no offset
int FlagTC = true; ////using flag to sample ant put into the list //using

unsigned int nTC = 0; //using
unsigned int Edge_Counter_L = 0; // using
unsigned int Value;

const int Comp_Pin = 3;//using     // the number of the pushbutton pin

/**** BATTERY SENSE  ****/


/**********Current Monitor*************/
Adafruit_INA219 ina219;
float TotalVoltage = 0;//using
float shuntvoltage = 0;//using
float busvoltage = 0;//using

//using fgvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvd<<<<<<<<<<<<<<<<<<<<<<<<<<<<<.{-v          p'0´      ,mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmgf7 ------

SoftwareSerial Xbee_Serial(4,3);

void setup() {       
  /***********TC**********/
  adc.begin();  
  Serial.begin(9600);   /// for programming
  Xbee_Serial.begin(9600);   /// Xbee serial output
  
  pinMode(Comp_Pin, INPUT);   // Comprator
  
  readRms.begin(VoltRange, RMS_WINDOW, ADC_12BIT, BLR_ON, CNT_SCAN);
  readRms.start(); //start measuring
  
  MeasAvg.begin(VoltRange, AVG_WINDOW, ADC_10BIT, CNT_SCAN); // 
  MeasAvg.start(); //start measuring
  
  nextLoop = micros() + LPERIOD; // Set the loop timer variable for the next loop interval.

  /***********SHT31**********/
  sht31.begin(0x44);
  if(! sht31.begin(0x44)) {
    //Serial.println("Couldnt find SHT31");
    while(1) delay(1);
    }  

  /*****CURRENT MONITOR*****/
  ina219.begin();
  ina219.setCalibration_16V_400mA();  
}

void loop() {
  
  Serial.println("HEADER");
  Xbee_Serial.write(HEADER);
  
  //TempHum();//Reading temperature
  
  Serial.println(1);delay(10);
  Serial.print("Temp: ");Serial.print(20);Serial.print(",");Serial.println(30);delay(10);
  Serial.println(2);delay(10);
  Serial.print("Humi: ");Serial.print(70);Serial.print(",");Serial.println(50);delay(10);
  
  Xbee_Serial.write(1);delay(10);
  Xbee_Serial.write(20);delay(10);Serial.write(byte(30));
  Xbee_Serial.write(byte(2));delay(10);
  Xbee_Serial.write(byte(30));delay(10);Serial.write(byte(90));
  
  EnergyBat();//Reading Volage and current battery  
  
  WaterRead();  // Reading innundation state  
  
  Read_RMS();
  
  //Check if equipment is working
  
  if(VTC >= 0.008){
    rms_Plot();
    Print_Val_Tail_VTC();
    }
  else{    
    MaxCurrent = 0;
    Num_Samples = 0;
    
    Serial.print("MaxCurrent : ");Serial.println(byte(MaxCurrent));delay(20);
    Serial.println("No ENERGY :( ");
    Serial.println(255);
    
    Xbee_Serial.write(byte(255));// no current, current 101
    Xbee_Serial.write(byte(MaxCurrent)); delay(10);
    Xbee_Serial.write(byte(Num_Samples)); delay(10);
    
    } 
    
  /********  ********/ 
  
  Serial.println("TAIL");
  Serial.print(0);Serial.print(0);Serial.println(0);
  
  Xbee_Serial.write(TAIL);  
  Xbee_Serial.write(byte(0));Serial.write(byte(0));Serial.write(byte(0));  
  
  delay(2000);  
}
