/****************** Router       ******************/
/****************** Lybraries    ******************/
#include <Arduino.h>
#include "Adafruit_SHT31.h"
#include <Adafruit_INA219.h>
#include <MCP3202.h>
#include "SPI.h"
#include <TrueRMS.h>
#include <SoftwareSerial.h>
#include <XBee.h>
#include <plot.h>

/********* VALUES TO SET (INPUTS) *********/
float Sensitivity = 0.1;  // Parameter to INPUT related with the current sensor characterizing
float VoltRange = 4.8;    // ADC full scale peak-to-peak is 5.00Volts measure in full operation
float ADC_Gain = 1;       // 1.05 related with the trigger
float Scale_Plot_Axis = 1;// Scale Data to plot in the screen y-axis
 
/* STRUCTS */
struct Temperature{
    int Tint;
    int Tdecimal;
    int Hint;
    int Hdecimal;
};

struct Battery{
    int ShuntVoltageInt;
    int ShuntVoltageDecimal;
    int CurrentmaInt;
    int CurrentmaDecimal;
};

struct Water{
    int WaterState;
};

struct CurrentData{
    float VTCComplete;//RMS Value with decimals  VTC
    double VTCAvg;// MEan value with decimals VTC_mean
    int VTCint;
    int VTCDecMSB;
    int VTCDecLSB;    
};

struct Plotting{
    uint8_t sampless[300];
    int Num_Samples;
    int MaxCurrent;
};

const char HEADER = 'H';
const char TAIL = 'T';

/****** XBEE SETUP  ****/
XBee xbee = XBee();
SoftwareSerial Xbee_Serial(4,3);


/****** RMS SETUP *******/
#define LPERIOD 1000    // loop period time in us. In this case 1.0ms
#define ADC_INPUT1 1    // water pin 
#define ADC_INPUT 2     // define the used ADC input channel
#define RMS_WINDOW 500  // rms window of 50 samples, means 3 periods @60Hz
#define AVG_WINDOW 500  // window of 500 samples.  

MCP3202 adc = MCP3202(10);
Rms2 readRms ;// create an instance of
Average MeasAvg; // 

unsigned long nextLoop;
unsigned long Time_Ex;

unsigned int adcVal_0;

double VTC_mean;

/**** PLOTTING *****/

/****** TEMPERATURE SETUP *****/
Adafruit_SHT31 sht31 = Adafruit_SHT31();

/**** WATER SETUP ****/

/****** CURRENT MONITOR ******/
Adafruit_INA219 ina219;

//using fgvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvd<<<<<<<<<<<<<<<<<<<<<<<<<<<<<.{-v          p'0´      ,mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmgf7 ------

void setup() {    
    adc.begin();  
    Serial.begin(9600);   /// for programming
    Xbee_Serial.begin(9600);   /// Xbee serial output
    /* Current Rms */
    readRms.begin(VoltRange, RMS_WINDOW, ADC_12BIT, BLR_ON, CNT_SCAN);
    readRms.start(); //start measuring
    
    MeasAvg.begin(VoltRange, AVG_WINDOW, ADC_10BIT, CNT_SCAN); // 
    MeasAvg.start(); //start measuring  
    
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
    Temperature temperatureH = Temperature();
    Battery battery = Battery();
    Water water = Water();
    CurrentData currentData = CurrentData();
    Plotting plotting = Plotting();

    temperatureH = TempHum();
    battery = EnergyBat();
    water = WaterRead();
    currentData = Read_RMS();
    //plotting = rms_Plot();

    //Transmission PayLoad
    uint8_t payload[] = {temperatureH.Tint,temperatureH.Tdecimal,
    temperatureH.Hint,temperatureH.Hdecimal,battery.ShuntVoltageInt,
    battery.ShuntVoltageDecimal,battery.CurrentmaInt,battery.CurrentmaDecimal,
    water.WaterState,
    currentData.VTCint,currentData.VTCDecMSB,currentData.VTCDecLSB};
    
    //Addressing Xbee
    XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x41553D44);
    ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));   
    xbee.send(zbTx);

    delay(1000);
    //ZBTxRequest zbTx2 = ZBTxRequest(addr64, payload2, sizeof(payload2)); 
    //xbee.send(zbTx2);
    delay(4000);
}
