/******************   Router      ******************/
/******************   Lybraries   ******************/
#include <Arduino.h>
#include <dhtnew.h>
#include <Adafruit_INA219.h>
#include <MCP3202.h>
#include <TrueRMS.h>
#include <SoftwareSerial.h>
#include <XBee.h>
#include <MCP331.h>
#include <SPI.h>

/******************   STRUCTS     ******************/
struct TemperatureStruct{
    int Tint = 0;
    int Tdecimal = 0;
    int Hint = 0;
    int Hdecimal = 0;
};

struct Battery{
    int ShuntVoltageInt = 0;
    int ShuntVoltageDecimal = 0;
    int CurrentmaInt = 0;
    int CurrentmaDecimal = 0;
};

struct Water{
    int WaterState = 0;
};

struct CurrentData{
    float VTCComplete = 0.0;//RMS Value with decimals  VTC
    float VTC_Mean = 0.0;
    int VTCint = 0;
    int VTCDecMSB = 0;
    int VTCDecLSB = 0; 

};

struct GraficaStruct{
    uint8_t samples[300];
    int Num_Samples = 0;
    int MaxCurrent  = 0;
};

const char HEADER = 'H';
const char TAIL = 'T';
 
/********* VALUES TO SET (INPUTS) *********/
float Sensitivity = 0.1;  // Parameter to INPUT related with the current sensor characterizing
float VoltRange = 4.8;    // ADC full scale peak-to-peak is 5.00Volts measure in full operation
float ADC_Gain = 1;       // 1.05 related with the trigger
float Scale_Plot_Axis = 1;// Scale Data to plot in the screen y-axis
 

/****** XBEE SETUP  ****/
XBee xbee = XBee();
SoftwareSerial Xbee_Serial(4,3);

/****** RMS SETUP *******/
#define LPERIOD 1000    // loop period time in us. In this case 1.0ms
#define ADC_INPUT1 A1    // water pin 
#define ADC_INPUT A2     // define the used ADC input channel
#define RMS_WINDOW 500  // rms window of 50 samples, means 3 periods @60Hz
#define AVG_WINDOW 500  // window of 500 samples.  
#define CLOCK_DIVISION 2
#define NUM_BITS 14
MCP331 adc = MCP331(10,CLOCK_DIVISION,NUM_BITS);
Rms2 readRms ;// create an instance of
Average MeasAvg; // 

unsigned long nextLoop;
unsigned long Time_Ex;

unsigned int adcVal_0;

double VTC_mean;

/**** PLOTTING *****/

/****** TEMPERATURE SETUP *****/
DHTNEW dhtpin1(8);

/**** WATER SETUP ****/
#define WATER_1 A1

/****** CURRENT MONITOR ******/
Adafruit_INA219 ina219;

//using fgvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvd<<<<<<<<<<<<<<<<<<<<<<<<<<<<<.{-v          p'0´      ,mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmgf7 ------

void setup() {    
    adc.begin();  
    Serial.begin(9600);   /// for programming
    Xbee_Serial.begin(9600);   /// Xbee serial output

    /*****CURRENT MONITOR*****/
    ina219.begin();
    ina219.setCalibration_16V_400mA(); 
    
    /* Current Rms */
    readRms.begin(VoltRange, RMS_WINDOW, ADC_12BIT, BLR_ON, CNT_SCAN);
    readRms.start(); //start measuring
    
    MeasAvg.begin(VoltRange, AVG_WINDOW, ADC_10BIT, CNT_SCAN); // 
    MeasAvg.start(); //start measuring      
    
    
}

void loop() {
    // instance of the sensors in field
    TemperatureStruct temperatureH = TemperatureStruct();
    Battery battery = Battery();
    Water water1 = Water();
    
    CurrentData currentData = CurrentData();
    GraficaStruct graf = GraficaStruct();
    float a =9.0;
    // Reading sensors
    
    temperatureH = TempHum(dhtpin1);
    delay(5);
    battery = EnergyBat(ina219);
    delay(5);
    water1 = WaterReads(WATER_1);
    /*
    delay(5);
    currentData = Read_RMS(readRms,MeasAvg, adc);
    rms_Plot();*/
    //Transmission PayLoad

    /* Dummy payload */
    uint8_t payload[] = {}
    /*uint8_t payload[] = {
        temperatureH.Tint,temperatureH.Tdecimal,
        temperatureH.Hint,temperatureH.Hdecimal/*,battery.ShuntVoltageInt,
        battery.ShuntVoltageDecimal,battery.CurrentmaInt,battery.CurrentmaDecimal,
        water1.WaterState,
        currentData.VTCint,currentData.VTCDecMSB,currentData.VTCDecLSB
    };*/
    
    //Addressing Xbee
    /*XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x41553D44);
    ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));   
    xbee.send(zbTx)*/;

    delay(1000);
    //ZBTxRequest zbTx2 = ZBTxRequest(addr64, payload2, sizeof(payload2)); 
    //xbee.send(zbTx2);
    delay(4000);
    Serial.println("Termina programa");
}
