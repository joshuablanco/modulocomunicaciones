/*
 * Se debe modificar el codigo para el nuevo codigo del router en donde se envia la trama sola y se puede usar la librería XBee 
 */

#include <math.h>
#include <Nextion.h>
//#include <HardwareSerial.h>
#include "ListLib.h"
#include <WiFi.h>
//#include <PubSubClient.h>
#include <XBee.h>

/* comment this if you dont use ubidots */
#define WIFISSID "FAMILIA JEREZ" // Put your WifiSSID here "SAVI INGENIERIA "   ""   Familia Nena
#define PASSWORD "P7P5C6R5X9J5" // Put your wifi password here 63485721  1098634009
#define TOKEN "A1E-ZcXtyZALrFheZNl2gcJL1vV7J2uPWT" // Put your Ubidots' TOKEN
#define MQTT_CLIENT_NAME "EcoTic124" // MQTT client Name, please enter your own 8-12 alphanumeric character ASCII string;       
#define VARIABLE_LABEL0 "temperature1" // Assing the variable label
#define VARIABLE_LABEL1 "humidity" // Assing the variable label
#define VARIABLE_LABEL2 "shuntvoltage" // Assing the variable label
#define VARIABLE_LABEL3 "currentmaint" // Assing the variable label
#define VARIABLE_LABEL4 "ctc" // Assing the variable label
#define VARIABLE_LABEL5 "innun" // Assing the variable label
#define DEVICE_LABEL "esp32" // Assig the device label

char mqttBroker[]  = "things.ubidots.com"; /// comment this if you dont use ubidots
char payload0[100];
char payload1[100];
char payload2[100];
char payload3[100];
char payload4[100];
char payload5[100];
char topic[150];

// Space to store values to send
char str_sensor[10];
char Temperature2_Str[10];
char Humidity1_Str[10];
char Voltage1_Str[10];
char Current1_Str[10];
char CTC1_Str[10];
char Innun_Str[10];

WiFiClient ubidots;   /// comment this if you dont use ubidots
//PubSubClient client(ubidots); /// comment this if you dont use ubidots
HardwareSerial SerialN(2); // second serial port for the screen
#define RXD2 16
#define TXD2 17

/**********Global variables**************** 
 ******************************************/
// Sensors

float Temperature = 0;
float Temperature1= 0;
String Temperature_Str = "";

float Humidity = 0;
String Humidity_Str = "";
float ShuntVoltage = 0;
String ShuntVoltage_Str="";
float CurrentmaInt = 0;
String CurrentmaInt_Str="";
float AnalogRef=1.1;//Analog Reference 
float CTC = 0;
//float CTC1 = 0;
String CTC_Str= "";
String Power_Str="";
int Innun = 0;
String SInnun = "";
int Tc=0;
int MaxCurrent = 0;
String MaxCurrent_Str="";
int iTC=0;
int ValueTC;

int Pflag1 = 0;
int Pflag3 = 0;
int Flag=0;
boolean Up_Flag= false;

char HEADER = 'H';
char TAIL = 'T';
float Resistor = 99.1;//98.9
float AspectRatio = 2000;
float conversorV_I = AspectRatio/Resistor;
List<int> list;
List<int> list1;
List<int> list2_WF;

byte reception = 0;
int var=0;
int n=0;
int i = 0;
boolean Flag1 = false;
boolean Current_Rms = true;

int sizing;

//New in Screen
int Temperature_I = 0;
int Temperature_D = 0;
int Humidity_I = 0;
int Humidity_D = 0;
int Dew_Point = 0;
uint16_t ShuntVoltage_I;
uint16_t ShuntVoltage_D;
uint16_t CurrentmaInt_I;
uint16_t CurrentmaInt_D;
uint16_t Pow_I;
uint16_t Pow_D;
uint16_t Irms_I;
uint16_t Irms_D_I;//Added instead just irms_d
uint16_t Irms_D_D;//Added instead just irms_d
uint16_t MaxCurr;


//Wifi http://
int Reconnect = 0;
/// uncomment this if you dont use ubidots
//const char * networkName = "SAVI INGENIERIA ";
//const char * networkPswd = "1098634009";
//const char * hostDomain = "192.168.0.33";
//const int hostPort = 80;
//const int BUTTON_PIN = 4;
//const int LED_PIN = 5;

/******************************************/

/******************Def pages*********************** 
 *****************************************/
NexPage page0 = NexPage(0,0,"page0");
NexPage page1 = NexPage(1,0,"page1");
NexPage page2 = NexPage(2,0,"page2");
NexPage page3 = NexPage(3,0,"page3");
NexPage page4 = NexPage(4,0,"page4");
NexPage page5 = NexPage(5,0,"page5");

/********************Component Nextion page 0*********************
 *****************************************/
NexButton b0P0 = NexButton(0,1,"b0P0");
NexButton b1P0 = NexButton(0,2,"b1P0");

/******************Component Nextion page 1***********************
 ******************************************/
NexButton b0P1 = NexButton(1,5,"b0P1");
NexButton b1P1 = NexButton(1,1,"b1P1");
NexButton b2P1 = NexButton(1,17,"b2P1");
//Temperature
NexText t2P1 = NexText(1, 7, "t2P1");// int
NexText t7P1 = NexText(1, 12, "t7P1");// Decimal
NexProgressBar setprogbar_j0P1 = NexProgressBar(1, 6, "j0P1");
//Humidity
NexText t3P1 = NexText(1, 3, "t3P1"); // INT
NexText t8P1 = NexText(1, 15, "t8P1"); // Decimal
// Dew Point
NexText t6P1 = NexText(1, 4, "t6P1"); // 
NexGauge setgauge_z0P1  = NexGauge(1, 2, "z0P1");
NexPicture setpic_p0P1 = NexPicture(1, 9, "p0P1");

/*****************Component Nextion page 2************************
 *****************************************/
NexButton b0P2 = NexButton(2,1,"b0P2");
NexButton b1P2 = NexButton(2,2,"b1P2");
NexButton b2P2 = NexButton(2,7,"b2P2");
NexText setinnun_t0P2 = NexText(2, 4, "t0P2");
NexPicture setpic_p0P2 = NexPicture(2, 3, "p0P2");
NexPicture setpic_p1P2 = NexPicture(2, 6, "p1P2");

/****************Component Nextion page 3*************************
 *****************************************/
#define CH0_OFFSET  (30)

NexButton b0P3 = NexButton(3,6,"b0P3");//back button
NexButton b1P3 = NexButton(3,12,"b1P3");//next button
NexButton b2P3 = NexButton(3,26,"b2P3");//next button

NexPicture setBatpic_p0P3 = NexPicture(3, 11, "p0P3");//battery picture
NexPicture setpic_p1P3 = NexPicture(3, 13, "p1P3");//Led alarm I = 0

NexText setShuntVoltage_t3P3 = NexText(3, 8, "t3P3");
NexText setShuntVoltage_t31P3 = NexText(3, 17, "t31P3");
NexText setCurr_t4P3 = NexText(3, 19, "t4P3");
NexText setCurr_t41P3 = NexText(3, 23, "t41P3");
NexText setPow_t5P3 = NexText(3, 21, "t5P3");
NexText setPow_t51P3 = NexText(3, 24, "t51P3");

NexText setIrms_t9P3 = NexText(3, 2, "t9P3");
NexText setIrms_t91P3 = NexText(3, 29, "t91P3");//D_I
NexText setIrms_t92P3 = NexText(3, 28, "t92P3");//D_I

NexText setCurrMaxplot_t10P3 = NexText(3, 4, "t10P3");

NexWaveform set_s0 = NexWaveform(3, 14, "s0");

/**************Component Nextion page 4***************************
 *****************************************/
NexButton b0P4 = NexButton(4,5,"b0P4");
NexButton b1P4 = NexButton(4,6,"b1P4");

/*******************Registering objects********************** 
 ****************************************/
NexTouch *nex_listen_list[] =
{  // page0
  &b0P0, &b1P0,
  // page 1
  &b0P1, &b1P1, &b2P1, &t2P1, &t6P1, &t3P1, &t8P1, &setpic_p0P1, &t7P1, 
  // page 2
  &b0P2, &b1P2, &b2P2, &setinnun_t0P2, &setpic_p0P2, &setpic_p1P2,
  // page 3
  &b0P3, &b1P3, &b2P3, &setShuntVoltage_t3P3, &setShuntVoltage_t31P3, &setCurr_t4P3, &setCurr_t41P3, &setPow_t5P3, &setPow_t51P3, &setBatpic_p0P3, &setpic_p1P3, &setCurrMaxplot_t10P3, &setIrms_t9P3, &setIrms_t91P3, &setIrms_t92P3,
  // page 4
  &b0P4, &b1P4,
  NULL
};
 // Organized varable names 
 
 char bufferTI[4] = {0};
 char bufferTD[4] = {0};
 char bufferHI[4] = {0};
 char bufferHD[4] = {0};
 char bufferDP[4] = {0};
 
 char bufferSHV_I[4] = {0};
 char bufferSHV_D[4] = {0};
 char bufferCurr_I[4] = {0};
 char bufferCurr_D[4] = {0};
 char bufferPow_I[4] = {0};
 char bufferPow_D[4] = {0};

 char bufferIrms_I[4] = {0};
 char bufferIrms_D_I[4] = {0};
 char bufferIrms_D_D[4] = {0};
 
 char bufferMaxCurr[4] = {0};
 
 uint32_t numberp01P1 =  11;
 
/**********************Buttons**********************************************
 ********************************************************************/
void b1P0PopCallback(void *ptr){//button
  //dbSerialPrintln("buttonNextPushCallback");
  if(true){Pflag1=1;}
  page1.show();  
  
  uint32_t Humidity_Gauge = int((Humidity*180)/100);//conversion to gauge scale
  uint32_t Temp_PBar = int((Temperature*100)/60);//conversion to progress bar scale
  uint32_t picg_p0P1 = 11;
  uint32_t picr_p0P1 = 12;
  
  //Serial.println(Humidity_I);
  //Serial.println(Humidity_D);
  
  uint32_t Temperature_IS = Temperature_I ;
  uint32_t Temperature_DS = Temperature_D; 
  
  //Erase the memset and itoa if you want something like before
  memset(bufferTI, 0, sizeof(bufferTI));
  itoa(Temperature_IS, bufferTI, 10);   
  t2P1.setText(bufferTI);
  
  memset(bufferTD, 0, sizeof(bufferTD));
  itoa(Temperature_DS, bufferTD, 10);   
  t7P1.setText(bufferTD);
  
  uint32_t Humidity_IS = Humidity_I;
  
  memset(bufferHI, 0, sizeof(bufferHI));
  itoa(Humidity_IS, bufferHI, 10);   
  t3P1.setText(bufferHI);

  uint32_t Humidity_DS = Humidity_D;
  
  memset(bufferHD, 0, sizeof(bufferHD));
  itoa(Humidity_DS, bufferHD, 10);   
  t8P1.setText(bufferHD);

  uint32_t Dew_PointS = Dew_Point;
  
  memset(bufferDP, 0, sizeof(bufferDP));
  itoa(Dew_PointS, bufferDP, 10);   
  t6P1.setText(bufferDP);
  

  if(Temperature < 50){
    setpic_p0P1.setPic(picg_p0P1);
    }else{setpic_p0P1.setPic(picr_p0P1);}

  setprogbar_j0P1.setValue(Temp_PBar);
  setgauge_z0P1.setValue(Humidity_Gauge); 
  
}

void b2P1PopCallback(void *ptr){//button
  if(true){Pflag1=1;}
  page1.show();  
  
  uint32_t Humidity_Gauge = int((Humidity*180)/100);//conversion to gauge scale
  uint32_t Temp_PBar = int((Temperature*100)/60);//conversion to progress bar scale
  uint32_t picg_p0P1 = 11;
  uint32_t picr_p0P1 = 12;
    
  uint32_t Temperature_IS = Temperature_I ;
  uint32_t Temperature_DS = Temperature_D; 
  
  //Erase the memset and itoa if you want something like before
  memset(bufferTI, 0, sizeof(bufferTI));
  itoa(Temperature_IS, bufferTI, 10);   
  t2P1.setText(bufferTI);
  
  memset(bufferTD, 0, sizeof(bufferTD));
  itoa(Temperature_DS, bufferTD, 10);   
  t7P1.setText(bufferTD);
  
  uint32_t Humidity_IS = Humidity_I;
  
  memset(bufferHI, 0, sizeof(bufferHI));
  itoa(Humidity_IS, bufferHI, 10);   
  t3P1.setText(bufferHI);

  uint32_t Humidity_DS = Humidity_D;
  
  memset(bufferHD, 0, sizeof(bufferHD));
  itoa(Humidity_DS, bufferHD, 10);   
  t8P1.setText(bufferHD);

  uint32_t Dew_PointS = Dew_Point;
  
  memset(bufferDP, 0, sizeof(bufferDP));
  itoa(Dew_PointS, bufferDP, 10);   
  t6P1.setText(bufferDP);
 

  if(Temperature < 50){
    setpic_p0P1.setPic(picg_p0P1);
    }else{setpic_p0P1.setPic(picr_p0P1);}

  setprogbar_j0P1.setValue(Temp_PBar);
  setgauge_z0P1.setValue(Humidity_Gauge); 

}

void b0P0PopCallback(void *ptr){//button
  //dbSerialPrintln("buttonNextPushCallback");
  if(true){Pflag3=1;}
  uint32_t picg_p0P3 = 11;
  uint32_t picr_p0P3 = 12;
  page3.show();  

  uint16_t Pow_I;
  uint16_t Pow_D;

  uint32_t ShuntVoltage_IS = ShuntVoltage_I ;
  
  memset(bufferSHV_I, 0, sizeof(bufferSHV_I));
  itoa(ShuntVoltage_IS, bufferSHV_I, 10);   
  setShuntVoltage_t3P3.setText(bufferSHV_I);

  uint32_t ShuntVoltage_DS = ShuntVoltage_D ;
  
  memset(bufferSHV_D, 0, sizeof(bufferSHV_D));
  itoa(ShuntVoltage_DS, bufferSHV_D, 10);   
  setShuntVoltage_t31P3.setText(bufferSHV_D);

  uint32_t CurrentmaInt_IS = CurrentmaInt_I;

  memset(bufferCurr_I, 0, sizeof(bufferCurr_I));
  itoa(CurrentmaInt_IS, bufferCurr_I, 10);   
  setCurr_t4P3.setText(bufferCurr_I);

  uint32_t CurrentmaInt_DS = CurrentmaInt_D;
  
  memset(bufferCurr_D, 0, sizeof(bufferCurr_D));
  itoa(CurrentmaInt_DS, bufferCurr_D, 10);   
  setCurr_t41P3.setText(bufferCurr_D);

  float Power = (ShuntVoltage*CurrentmaInt) ;
  Pow_I = (unsigned int)Power;
  Pow_D = (Power - Pow_I )*100; 

  uint32_t bufferPow_IS = Pow_I;
    
  memset(bufferPow_I, 0, sizeof(bufferPow_I));
  itoa(bufferPow_IS, bufferPow_I, 10);   
  setPow_t5P3.setText(bufferPow_I);

  uint32_t bufferPow_DS = Pow_D;
  
  memset(bufferPow_D, 0, sizeof(bufferPow_D));
  itoa(bufferPow_DS, bufferPow_D, 10);   
  setPow_t51P3.setText(bufferPow_D);

  /** Separation of digits for upload a value, separaion of three digits **/
  float Irms = CTC;
  float Irms_D = 0;
  
  //1.05
  Irms_I = (unsigned int) Irms;//upload this --- 1
  Irms_D = (Irms - Irms_I)*10;//---0.5
  Irms_D_I = (unsigned int) Irms_D;//---0//Upload this
  Irms_D_D = (Irms_D - Irms_D_I)*10;//---5//upload This
  
  uint32_t Irms_IS = Irms_I;
  
  memset(bufferIrms_I, 0, sizeof(bufferIrms_I));
  itoa(Irms_IS, bufferIrms_I, 10);   
  setIrms_t9P3.setText(bufferIrms_I);

  uint32_t Irms_DS = Irms_D_I;
  
  memset(bufferIrms_D_I, 0, sizeof(bufferIrms_D_I));
  itoa(Irms_DS, bufferIrms_D_I, 10);   
  setIrms_t91P3.setText(bufferIrms_D_I);

  uint32_t Irms_D_DS = Irms_D_D;
  
  memset(bufferIrms_D_D, 0, sizeof(bufferIrms_D_D));
  itoa(Irms_D_DS, bufferIrms_D_D, 10);   
  setIrms_t92P3.setText(bufferIrms_D_D);///OJO

  MaxCurr = (uint16_t) MaxCurrent;
  
  memset(bufferMaxCurr, 0, sizeof(bufferMaxCurr));
  itoa(MaxCurr, bufferMaxCurr, 10);   
  setCurrMaxplot_t10P3.setText(bufferMaxCurr);

  uint8_t ch0 = 0;
  if(CTC > 0){
    setpic_p1P3.setPic(picg_p0P3);    
    list2_WF = list1;
    if(list2_WF.Count() > 4){   
      for(int i_WF = 0; i_WF < list2_WF.Count()-1; i_WF ++){
        ch0 = (uint8_t) list2_WF[i_WF];
        set_s0.addValue(0,CH0_OFFSET + ch0);
        delay(4);
        }    
      }
    
    }else{
      setpic_p1P3.setPic(picr_p0P3);
      for(int i_WF = 0; i_WF < 130; i_WF ++){
        ch0 = 0;
        set_s0.addValue(0,CH0_OFFSET + ch0);
        delay(4);
        }
      }   
}

void b0P1PopCallback(void *ptr){//button
  //dbSerialPrintln("buttonNextPushCallback");
  page0.show();  
}

void b1P1PopCallback(void *ptr){//button
  //dbSerialPrintln("buttonNextPushCallback");
  page2.show();  
  uint32_t picg_p0P2 = 11;
  uint32_t picr_p0P2 = 12;
  ////put inside the if a digital outputto turn on the relay
  
  if(Innun == 0){
    setinnun_t0P2.setText("Seco");
    setpic_p0P2.setPic(picg_p0P2);
    
    }else{
      setinnun_t0P2.setText("Mojado");
      setpic_p0P2.setPic(picr_p0P2);
      }  
      
}

void b2P2PopCallback(void *ptr){//button
  page2.show();  
  uint32_t picg_p0P2 = 11;
  uint32_t picr_p0P2 = 12;
  
  if(Innun == 0){
    setinnun_t0P2.setText("Seco");
    setpic_p0P2.setPic(picg_p0P2);
    
    }else{
      setinnun_t0P2.setText("Mojado");
      setpic_p0P2.setPic(picr_p0P2);
      }  

}

void b0P2PopCallback(void *ptr){//button
  //dbSerialPrintln("buttonNextPushCallback");
  if(true){Pflag1=1;}
  page1.show();  
  
  uint32_t Humidity_Gauge = int((Humidity*180)/100);//conversion to gauge scale
  uint32_t Temp_PBar = int((Temperature*100)/60);//conversion to progress bar scale
  uint32_t picg_p0P1 = 11;
  uint32_t picr_p0P1 = 12;
    
  uint32_t Temperature_IS = Temperature_I ;
  uint32_t Temperature_DS = Temperature_D; 
  
  //Erase the memset and itoa if you want something like before
  memset(bufferTI, 0, sizeof(bufferTI));
  itoa(Temperature_IS, bufferTI, 10);   
  t2P1.setText(bufferTI);
  
  memset(bufferTD, 0, sizeof(bufferTD));
  itoa(Temperature_DS, bufferTD, 10);   
  t7P1.setText(bufferTD);
  
  uint32_t Humidity_IS = Humidity_I;
  
  memset(bufferHI, 0, sizeof(bufferHI));
  itoa(Humidity_IS, bufferHI, 10);   
  t3P1.setText(bufferHI);

  uint32_t Humidity_DS = Humidity_D;
  
  memset(bufferHD, 0, sizeof(bufferHD));
  itoa(Humidity_DS, bufferHD, 10);   
  t8P1.setText(bufferHD);

  uint32_t Dew_PointS = Dew_Point;
  
  memset(bufferDP, 0, sizeof(bufferDP));
  itoa(Dew_PointS, bufferDP, 10);   
  t6P1.setText(bufferDP);
  
  if(Temperature < 50){
    setpic_p0P1.setPic(picg_p0P1);
    }else{setpic_p0P1.setPic(picr_p0P1);}

  setprogbar_j0P1.setValue(Temp_PBar);
  setgauge_z0P1.setValue(Humidity_Gauge); 
  
}

void b2P3PopCallback(void *ptr){//button
  if(true){Pflag3=1;}
  uint32_t picg_p0P3 = 11;
  uint32_t picr_p0P3 = 12;
  page3.show(); 
  
  uint16_t Pow_I;
  uint16_t Pow_D;

  uint32_t ShuntVoltage_IS = ShuntVoltage_I ;
  
  memset(bufferSHV_I, 0, sizeof(bufferSHV_I));
  itoa(ShuntVoltage_IS, bufferSHV_I, 10);   
  setShuntVoltage_t3P3.setText(bufferSHV_I);

  uint32_t ShuntVoltage_DS = ShuntVoltage_D ;
  
  memset(bufferSHV_D, 0, sizeof(bufferSHV_D));
  itoa(ShuntVoltage_DS, bufferSHV_D, 10);   
  setShuntVoltage_t31P3.setText(bufferSHV_D);

  uint32_t CurrentmaInt_IS = CurrentmaInt_I;

  memset(bufferCurr_I, 0, sizeof(bufferCurr_I));
  itoa(CurrentmaInt_IS, bufferCurr_I, 10);   
  setCurr_t4P3.setText(bufferCurr_I);

  uint32_t CurrentmaInt_DS = CurrentmaInt_D;
  
  memset(bufferCurr_D, 0, sizeof(bufferCurr_D));
  itoa(CurrentmaInt_DS, bufferCurr_D, 10);   
  setCurr_t41P3.setText(bufferCurr_D);

  float Power = (ShuntVoltage*CurrentmaInt) ;
  Pow_I = (unsigned int)Power;
  Pow_D = (Power - Pow_I )*100; 

  uint32_t bufferPow_IS = Pow_I;
    
  memset(bufferPow_I, 0, sizeof(bufferPow_I));
  itoa(bufferPow_IS, bufferPow_I, 10);   
  setPow_t5P3.setText(bufferPow_I);

  uint32_t bufferPow_DS = Pow_D;
  
  memset(bufferPow_D, 0, sizeof(bufferPow_D));
  itoa(bufferPow_DS, bufferPow_D, 10);   
  setPow_t51P3.setText(bufferPow_D);

  /** Separation of digits for upload a value, separaion of three digits **/
  float Irms = CTC;
  float Irms_D = 0;
  
  //1.05
  Irms_I = (unsigned int) Irms;//upload this --- 1
  Irms_D = (Irms - Irms_I)*10;//---0.5
  Irms_D_I = (unsigned int) Irms_D;//---0//Upload this
  Irms_D_D = (Irms_D - Irms_D_I)*10;//---5//upload This
  
  uint32_t Irms_IS = Irms_I;
  
  memset(bufferIrms_I, 0, sizeof(bufferIrms_I));
  itoa(Irms_IS, bufferIrms_I, 10);   
  setIrms_t9P3.setText(bufferIrms_I);

  uint32_t Irms_DS = Irms_D_I;
  
  memset(bufferIrms_D_I, 0, sizeof(bufferIrms_D_I));
  itoa(Irms_DS, bufferIrms_D_I, 10);   
  setIrms_t91P3.setText(bufferIrms_D_I);

  uint32_t Irms_D_DS = Irms_D_D;
  
  memset(bufferIrms_D_D, 0, sizeof(bufferIrms_D_D));
  itoa(Irms_D_DS, bufferIrms_D_D, 10);   
  setIrms_t92P3.setText(bufferIrms_D_D);///OJO

  MaxCurr = (uint16_t) MaxCurrent;
  
  memset(bufferMaxCurr, 0, sizeof(bufferMaxCurr));
  itoa(MaxCurr, bufferMaxCurr, 10);   
  setCurrMaxplot_t10P3.setText(bufferMaxCurr);
  
  uint8_t ch0 = 0;
  if(CTC > 0){
    setpic_p1P3.setPic(picg_p0P3);
    list2_WF = list1;
    if(list2_WF.Count() > 4){   
      for(int i_WF = 0; i_WF < list2_WF.Count()-1; i_WF ++){
        ch0 = (uint8_t) list2_WF[i_WF];
        set_s0.addValue(0,CH0_OFFSET + ch0);
        delay(4);
        }    
      }
    
    }else{
      setpic_p1P3.setPic(picr_p0P3);
      for(int i_WF = 0; i_WF < 130; i_WF ++){
        ch0 = 0;
        set_s0.addValue(0,CH0_OFFSET + ch0);
        delay(4);
        }        
      }
  
}

void b1P2PopCallback(void *ptr){//button
  //dbSerialPrintln("buttonNextPushCallback");
  if(true){Pflag3=1;}
  uint32_t picg_p0P3 = 11;
  uint32_t picr_p0P3 = 12;
  page3.show(); 

  uint16_t Pow_I;
  uint16_t Pow_D;

  uint32_t ShuntVoltage_IS = ShuntVoltage_I ;
  
  memset(bufferSHV_I, 0, sizeof(bufferSHV_I));
  itoa(ShuntVoltage_IS, bufferSHV_I, 10);   
  setShuntVoltage_t3P3.setText(bufferSHV_I);

  uint32_t ShuntVoltage_DS = ShuntVoltage_D ;
  
  memset(bufferSHV_D, 0, sizeof(bufferSHV_D));
  itoa(ShuntVoltage_DS, bufferSHV_D, 10);   
  setShuntVoltage_t31P3.setText(bufferSHV_D);

  uint32_t CurrentmaInt_IS = CurrentmaInt_I;

  memset(bufferCurr_I, 0, sizeof(bufferCurr_I));
  itoa(CurrentmaInt_IS, bufferCurr_I, 10);   
  setCurr_t4P3.setText(bufferCurr_I);

  uint32_t CurrentmaInt_DS = CurrentmaInt_D;
  
  memset(bufferCurr_D, 0, sizeof(bufferCurr_D));
  itoa(CurrentmaInt_DS, bufferCurr_D, 10);   
  setCurr_t41P3.setText(bufferCurr_D);

  float Power = (ShuntVoltage*CurrentmaInt) ;
  Pow_I = (unsigned int) Power;
  Pow_D = (Power - Pow_I )*100; 

  uint32_t bufferPow_IS = Pow_I;
    
  memset(bufferPow_I, 0, sizeof(bufferPow_I));
  itoa(bufferPow_IS, bufferPow_I, 10);   
  setPow_t5P3.setText(bufferPow_I);

  uint32_t bufferPow_DS = Pow_D;
  
  memset(bufferPow_D, 0, sizeof(bufferPow_D));
  itoa(bufferPow_DS, bufferPow_D, 10);   
  setPow_t51P3.setText(bufferPow_D);
/** Separation of digits for upload a value, separaion of three digits **/
  float Irms = CTC;
  float Irms_D = 0;
  
  //1.05
  Irms_I = (unsigned int) Irms;//upload this --- 1
  Irms_D = (Irms - Irms_I)*10;//---0.5
  Irms_D_I = (unsigned int) Irms_D;//---0//Upload this
  Irms_D_D = (Irms_D - Irms_D_I)*10;//---5//upload This
  
  uint32_t Irms_IS = Irms_I;
  
  memset(bufferIrms_I, 0, sizeof(bufferIrms_I));
  itoa(Irms_IS, bufferIrms_I, 10);   
  setIrms_t9P3.setText(bufferIrms_I);

  uint32_t Irms_DS = Irms_D_I;
  
  memset(bufferIrms_D_I, 0, sizeof(bufferIrms_D_I));
  itoa(Irms_DS, bufferIrms_D_I, 10);   
  setIrms_t91P3.setText(bufferIrms_D_I);

  uint32_t Irms_D_DS = Irms_D_D;
  
  memset(bufferIrms_D_D, 0, sizeof(bufferIrms_D_D));
  itoa(Irms_D_DS, bufferIrms_D_D, 10);   
  setIrms_t92P3.setText(bufferIrms_D_D);///OJO

  MaxCurr = (uint16_t) MaxCurrent;
  
  memset(bufferMaxCurr, 0, sizeof(bufferMaxCurr));
  itoa(MaxCurr, bufferMaxCurr, 10);   
  setCurrMaxplot_t10P3.setText(bufferMaxCurr);

  
  uint8_t ch0 = 0;
  if(CTC > 0){
    setpic_p1P3.setPic(picg_p0P3);
    list2_WF = list1;
    if(list2_WF.Count() > 4){   
      for(int i_WF = 0; i_WF < list2_WF.Count()-1; i_WF ++){
        ch0 = (uint8_t) list2_WF[i_WF];
        set_s0.addValue(0,CH0_OFFSET + ch0);
        delay(4);
        }    
      }
    }else{
      setpic_p1P3.setPic(picr_p0P3);
      for(int i_WF = 0; i_WF < 130; i_WF ++){
        ch0 = 0;
        set_s0.addValue(0,CH0_OFFSET + ch0);
        delay(4);
        }
      }    
    
}

void b0P3PopCallback(void *ptr){//button
  //dbSerialPrintln("buttonNextPushCallback");
  page2.show();  
  uint32_t picg_p0P2 = 11;
  uint32_t picr_p0P2 = 12;
  
  if(Innun == 0){
    setinnun_t0P2.setText("Seco");
    setpic_p0P2.setPic(picg_p0P2);
    
    }else{
      setinnun_t0P2.setText("Mojado");
      setpic_p0P2.setPic(picr_p0P2);
      }
}

void b1P3PopCallback(void *ptr){//button
  //dbSerialPrintln("buttonNextPushCallback");
  page0.show();  
}

void setpic_p1P2PopCallback(void *ptr){//picture that defines the speaker state
  //dbSerialPrintln("buttonNextPushCallback");
  uint32_t picoff_p1P2 = 0;
  
  setpic_p1P2.getPic(&picoff_p1P2);
  
  if(picoff_p1P2==13){
    dbSerialPrintln(picoff_p1P2);
    picoff_p1P2=14;
    }else{
      picoff_p1P2=13;
      }
  setpic_p1P2.setPic(picoff_p1P2);
  
}

void setup(void) {//// SET UP
  Up_Flag= false;
  nexInit();
  Serial.begin(9600);
  SerialN.begin(9600,SERIAL_8N1,RXD2,TXD2);
  WiFi.begin(WIFISSID, PASSWORD);
  Serial.println();
  Serial.print("Wait for WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);   
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  //client.setServer(mqttBroker, 1883);
  //client.setCallback(callback);
  
  
  b0P0.attachPop(b0P0PopCallback);
  b1P0.attachPop(b1P0PopCallback);
  b0P1.attachPop(b0P1PopCallback);
  b2P1.attachPop(b2P1PopCallback);// refresh 
  b1P1.attachPop(b1P1PopCallback);
  b0P2.attachPop(b0P2PopCallback);
  b2P2.attachPop(b2P2PopCallback);// refresh
  b1P2.attachPop(b1P2PopCallback);
  b0P3.attachPop(b0P3PopCallback);
  b2P3.attachPop(b2P3PopCallback);//refresh
  b1P3.attachPop(b1P3PopCallback);
  setpic_p1P2.attachPop(setpic_p1P2PopCallback);

  //connectToWiFi(networkName, networkPswd);
  //Serial.println(hostDomain);
  
}

void loop(void) {//// LOOOOOOOOP
  
  Up_Flag = false;
  SerialData();
  nexLoop(nex_listen_list);
             
  if(Pflag1==1){//this flag indicates when the data should be sent and to know if page1 its showing up
    Pflag1=0;
    }  
      
  if(Pflag3==1){//"IF" RELATED WITH THE BATTERY INFORMATION   
    uint32_t picBatg_p0P3 = 1; //battery images
    uint32_t picBaty_p0P3 = 2; 
    uint32_t picBato_p0P3 = 3; 
    uint32_t picBatr_p0P3 = 4; 
    
    if(ShuntVoltage >= 4.2){
      setBatpic_p0P3.setPic(picBatg_p0P3);
      }
    if(ShuntVoltage < 4.2 && ShuntVoltage >= 3.8){
      setBatpic_p0P3.setPic(picBaty_p0P3);
      }
    if(ShuntVoltage < 3.8 && ShuntVoltage >= 3.6){
      setBatpic_p0P3.setPic(picBato_p0P3);
      } 
    if(ShuntVoltage < 3.6){
      setBatpic_p0P3.setPic(picBatr_p0P3);
      }
      Pflag3=0;
    }
              
  if(Temperature != 0.0 && Up_Flag == true){// "IF" RELATED WITH GETTING DATA 
      //Adjust the offset CH0_OFFSET to fit you plot into the scale 
      /**** PLOTTING THE DATA INTO THE SCREEN ****/
      uint8_t ch0 = 0;
      list2_WF = list1;
      if(CTC == 0){ //Check if there is Current
        for(int i_WF = 0; i_WF < 130 ; i_WF ++){
          ch0 = 0;
          set_s0.addValue(0,CH0_OFFSET + ch0);
          delay(4);
          }              
        }
     
      if(list2_WF.Count() > 4 && CTC > 0){   //Plot signal
        for(int i_WF = 0; i_WF < list2_WF.Count()-1; i_WF ++){
          ch0 = (uint8_t) list2_WF[i_WF];
          set_s0.addValue(0,CH0_OFFSET + ch0);
          delay(4);
          }   
      }   
      //requestURL(hostDomain, hostPort);
      //Serial.println(listsum);
      if((WiFi.status() != WL_CONNECTED) == 0){
        //Ubiupload();
      }
      //if (client.connected()) {Ubiupload();Reconnect = 0;}
      //else{Reconnect = Reconnect + 1; Serial.println("WiFi Disconnected"); if (Reconnect > 10){reconnect();Reconnect = 0;}}
      //Serial.println(" "); 
  }
 
}  

    
