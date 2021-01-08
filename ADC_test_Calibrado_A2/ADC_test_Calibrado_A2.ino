#include <MCP3202.h>
#include <Wire.h>
#include "ListLib.h"
#include <Adafruit_INA219.h>
MCP3202 adc = MCP3202(10);

Adafruit_INA219 ina219;

boolean I_Current_signal = true; //using
boolean Comp_State_Low = false;//using
boolean Comp_State_change = false; //using

int channel1_3 = 0;//A3 DC
int channel1_2 = 0;//A2 ATMEGA energy double checking 
int MaxCurrent; // using
int Primario;// using
int FlagTC = true; ////using flag to sample ant put into the list //using
int Comp_State = LOW;//using
int last_Comp_State = HIGH;//using

unsigned int nTC = 0; //using
unsigned int counter_Energy = 0; //using
unsigned int Edge_Counter_L = 0; // using

const int numberOfEntries = 120; // even number that result in even //using
const int SensorPin2 = A2;//using
const int SensorPin3 = A3;//using
const int SensorPin0 = A1;//using
const int Comp_Pin = 2;//using     // the number of the pushbutton pin

unsigned int channel0_MCP; // using

double VTC = 0; //using
double VTC2 = 0;
double V_acc = 0;//using
double V_acc_1 = 0;//using
double V_acc2 = 0;
double channel2_0_MCP = 0;//using
float channel2_2 = 0; //using------
float channel2_3 = 0; //using fgvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvd<<<<<<<<<<<<<<<<<<<<<<<<<<<<<.{-v          p'0´      ,mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmgf7 ------
float y_3_Mean = 0; //using
float y_3 = 0; //using
float y_2 = 0; //using
float y_0_MCP =  0; //using
float V_mean = 0; //using
float V_mean2 = 0; //using
float Samp;//using
float TotalVoltage = 0;//using
float y_INA = 0;//using
float V_mean_INA = 0;//using

float Volt_MCP = 0;//using
float Num_Samples = 0;//using
float Offet_Opam = 0.001;//using
float shuntvoltage = 0;//using
float busvoltage = 0;//using

List<float> results;//using
List<float> results2;//using


void setup() {

  adc.begin();
  Serial.begin(9600);
  
  while (!Serial) {
    delay(1);
  }
  
  ina219.begin();
  ina219.setCalibration_16V_400mA();
  uint32_t currentFrequency;

  pinMode(Comp_Pin, INPUT);
  
  analogReference(EXTERNAL);
}

void mean_Val() {
  
  Samp = 0;
  V_mean = 0;
  V_mean2 = 0;
  
  for (int i = 0; i < (numberOfEntries) - 1 ; i++) {
    
    channel1_3 = analogRead(SensorPin3);// A3 DC
    //channel0_MCP = adc.readChannel(0); //DC
    
    //channel2_0 = channel1_0 * V_mean_INA / 1023;
    //channel2 = channel1 * V_mean_INA / 1023;///ATMEGA
    
    channel2_3 = (float) (channel1_3 * V_mean_INA / 1023);//DC
    //channel2_2 = channel0_MCP * V_mean_INA / 4095; //SIGNAL IN
    //Serial.print("V_mean :   "); Serial.print(channel2_3, 3); Serial.println(" V");
    //Serial.print("V_mean_SPI :   "); Serial.print(channel2_2, 3); Serial.println(" V");
    //results[i] = channel2;
    
    Samp = Samp + 1;
    
    V_mean = V_mean + channel2_3;
    //V_mean2 = V_mean2 + channel2_2;
    //Serial.print(" ");Serial.print(i);
    
    V_mean = V_mean / 2;
    //V_mean2 = V_mean2 / 2;
    //V_mean_2 = V_mean_2 / 2;
    
    delay(50);    
  }
  //This values must be the same in the CheckEnergy() function
  //y_3_Mean = V_mean;
  y_3_Mean = 0.9947*V_mean  + 0.02;
  //y_3_Mean = 0.9949*V_mean + 0.021;// ATMEGA WORKS this measures are under Therorical val
  //y_3_Mean = 0.9802*V_mean + 0.0141;//ATMEGA WORKS this measures are over Theroric val
  //y_3_Mean = 0.9755*V_mean + 0.0881;//ATMEGA WORKS
  //y_3_Mean = 0.9944* V_mean + 0.018;
  //y_3 = 0.9846821*V_mean + 0.00002821247;/// MCP error less than 1%
  
}

void mean_Val_INA(){ // DOUBLE CHECK THE Y_INA BECAUSE IS INSIDE OF THE FOR LOOP EXTRACT IT
  
  Samp = 0;
  V_mean = 0;
  V_mean_INA =0;
  
  for (int i = 0; i < 30; i++) {
    
    
    TotalVoltage = 0;
    
    
    busvoltage = ina219.getBusVoltage_V();
    
    //y_INA = 0.9842*TotalVoltage + 0.0921 - 0.9842*shuntvoltage / 1000;
    
    
    //Serial.print("busvoltage :   "); Serial.print(busvoltage, 3); Serial.println(" V");
    //Serial.print("y :   "); Serial.print(y, 3); Serial.println(" V");
    Samp = Samp + 1;
    
    V_mean_INA = V_mean_INA + busvoltage;
    
    //Serial.print(" ");Serial.print(i);
    
    V_mean_INA = V_mean_INA / 2;
    
    delay(50);
  }
  //y_INA = 0.9842*V_mean_INA + 0.0921 - 0.9842*shuntvoltage / 1000;
  V_mean_INA=V_mean_INA;
}

void check_Energy(){
  I_Current_signal = true;
  counter_Energy = 0; // how many samples in the forbbiden gap
  
  unsigned int n_numberOfEntries = 0; // for while bounds
  
  while(I_Current_signal == true &&  n_numberOfEntries < numberOfEntries/2 ){
    
    channel1_2 = analogRead(SensorPin2);//A2 ATMEGA signal 
    channel2_2 = channel1_2 * V_mean_INA / 1023;
    
    y_3 = 0.9947* channel2_2 + 0.02;
    //Serial.print("First Read: ");Serial.println(y_3);          
    
    if(y_3 > (y_3_Mean - 3*(V_mean_INA / 1023)) &&  y_3 < (y_3_Mean + 3*(V_mean_INA / 1023))){ // counter to identify empty list
      counter_Energy = counter_Energy + 1;
      I_Current_signal = (counter_Energy > ((numberOfEntries/2) - 5)) ? false:true; /// greater than one nyumber no energy verification
      //Serial.print("counter : ");Serial.println(counter);
      }
    n_numberOfEntries = n_numberOfEntries + 1;  
    delay(2);
    }
  }

void rms_Val(){
 
  nTC = 0; // using for the main while
  FlagTC = 1; // flag to sample ant put into the list
  Comp_State_Low = false;
  Comp_State_change = false;
  last_Comp_State = HIGH;
  Edge_Counter_L = 0;
  Num_Samples = 0; //count numb diff than cero to divide 
  V_acc = 0; 
  V_acc2 = 0; 
  channel2_0_MCP = 0;
  
//  double VTCa = 0; //Component a of the Fourier Series
//  double VTCb = 0; //Component b of the Fourier Series
//  double VTC1 = 0; // first Harmonic current 
//  double Iinta;// init variable in zero for Add "a" series coeffitient 
//  double Iintb;// init variable in zero for Add "b" series coeffitient

  while(nTC < 700 && FlagTC == true ){
    
    Comp_State = digitalRead(Comp_Pin);    
    Comp_State_Low = (Comp_State == HIGH ) ? false:true;   
    //Serial.print("Comp_State : ");Serial.println(Comp_State); 
    
    while(Comp_State_Low == true){//Comp_State_change contains logic for knowing the rising edge      
      Comp_State = digitalRead(Comp_Pin);    
      Comp_State_Low = (Comp_State == HIGH ) ? false:true;
      //Serial.print("Comp_State_Low : ");Serial.println(Comp_State_Low); 
      Comp_State_change = (Comp_State_Low == false) ? true:false; //if comp is High provisional  
    }

    Num_Samples = 0;
    while(Edge_Counter_L < 4  && Comp_State_change == true && Num_Samples < 800){//Count_Zero_Logic for sensing zeros on readings  LogValue == true
      //Serial.println("entro : ");
      
      Comp_State = digitalRead(Comp_Pin);
                                      
      if (Comp_State != last_Comp_State) {  //edge verification 5 cycles 
        Edge_Counter_L++;    
        Serial.print("Edge_Counter_L: ");Serial.println(Edge_Counter_L);
        }
        
      last_Comp_State = Comp_State;     

      channel1_2 = analogRead(SensorPin2);// A2 SIG
      channel0_MCP = adc.readChannel(0);
      
      channel2_2 = (float)(channel1_2 * 3.27 / 1024)-0.76 - Offet_Opam;//DC      
      channel2_0_MCP = (float)(channel0_MCP * (3.27 / 4096)-0.76 - Offet_Opam); //MCP  

      //channel1_2 = analogRead(SensorPin2);//A2 ATMEGA signal 
      //channel2_2 = channel1_2 * (V_mean_INA / 1023) - y_3_Mean - Offet_Opam;
      
      //results.Add(channel2_0_MCP);
      //results2.Add(channel2_2);
      
      //y_0_MCP = (0.9846*channel2_0_MCP + 0.00002821247);/// MCP error less than 1%
      //y_3 = 0.9944*channel2_2  + 0.018;
      V_acc = V_acc + (sq(channel2_0_MCP));
      V_acc2 = V_acc2 + (sq(channel2_2));
      //list.Add(channel1);
      //Value = map(channel1, 0 , 4095, 0,  255);
      //Serial.write(Value);
      //Serial.println(channel1);
      
      //Serial.println(channel2_0_MCP);
      
      Num_Samples = Num_Samples +1;
      FlagTC = false;

      delay(50);
       
      }   
    nTC=nTC+1;
    delay(2);   
  }
  //Serial.println(" ");
  //Serial.print("Iint: ");//Serial.println(Iint);
  //Serial.print("iTC: ");//Serial.println(iTC);
  //Serial.print("Num_Samples: ");//Serial.println(Num_Samples);
   
  /// if its an empty list is going to send 0xFF
    
  if (Num_Samples > 0 ){
    //V_acc = (0.9846821*V_acc + 0.00002821247);/// MCP error less than 1%
    //V_acc = 0.9802*V_acc + 0.0141;
    //V_acc = 0.9942*V_acc + 0.0205;
    Serial.print("V_acc: ");Serial.println(V_acc);
    Serial.print("V_acc2: ");Serial.println(V_acc2);
    //V_acc = 0.9940*V_acc + 0.02;
    Serial.print("V_acc: ");Serial.println(V_acc);
    Serial.print("Num_Samples: ");Serial.println(Num_Samples,3);  
    //Serial.print("V_acc: ");Serial.println(V_acc,3);  
    VTC = 0.94*(sqrt(V_acc/ Num_Samples));///square root of Int of curr over the samples
    VTC2 = 0.94*(sqrt(V_acc2/ Num_Samples));
    Serial.print("VTC: ");Serial.println(VTC,3);  
    Serial.print("VTC_2: ");Serial.println(VTC2,3);   
    byte VTCint = byte(VTC);
    //Serial.print("VTCint: ");//Serial.println(VTCint);   
    int VTCdec = (VTC - VTCint) * 1000;
    //Serial.print("VTCdec: ");//Serial.println(VTCdec);   
    //Serial.write(VTCint);delay(20); // we are sending Voltage RMS
    //Serial.write(VTCdec);delay(20);
    }
      
    //Serial.write(byte(MaxCurrent));delay(20);
    //Serial.print("Empty list :::::::::::::: ");Serial.println(byte(0xFF));
    //Serial.write(byte(255));delay(20); // no current, current 101
    
    //Serial.print("MaxCurrent : ");Serial.println(byte(MaxCurrent));delay(20);
    //Serial.print("Empty list : ");Serial.println(byte(0b11111111));delay(20);
  
    else {
      Serial.println("Something is wrong--------->ERROR :( ");
      Serial.print("Num_Samples : ");Serial.println(Num_Samples);
      Serial.print("V_acc : ");Serial.println(V_acc);
      Serial.print("Edge_Counter_L : ");Serial.println(Edge_Counter_L);
      if(Edge_Counter_L > 5) Serial.println("error --->check signals");   
      MaxCurrent = int(Primario); 
      //Serial.write(byte(MaxCurrent)); delay(20);  
      //Serial.print("MaxCurrent : ");Serial.println(byte(MaxCurrent));delay(20);
      //Serial.write(byte(iTC)); delay(20);
      //Serial.print("Count list : ");Serial.println(byte(list.Count()));delay(20);
     }
  }

void loop() {
  
  mean_Val_INA();  
  mean_Val();
  Serial.print("V_mean_INA :   "); Serial.print(V_mean_INA, 3); Serial.println(" V");
  Serial.print("y_3_Mean :   ");Serial.print(y_3_Mean, 3); Serial.println(" V");
  VTC=0;
  VTC2=0;
  V_mean_INA = 3.241;
  y_3_Mean = 0.761;
  check_Energy();
  Num_Samples =0;
  Serial.print("I_Current_signal :   "); Serial.println(I_Current_signal);
  if(I_Current_signal == true){rms_Val();}else{Serial.println("No ENERGY :( ");Serial.write(byte(255));}//}Serial.write(byte(255));delay(20); // no current, current 101}
//  for(int i = 0; i < (results.Count() - 1); i++)
//  {
//    //V_samp = V_samp + (sq(results[i] - 1.506));
//    
//    Serial.print(results[i]);Serial.print(",");
//    Serial.println(results2[i]);
//    
//    delay(50); 
//    
//    } 
  
  
  //Serial.print("V_mean_SPI :   "); Serial.print(V_mean2, 3); Serial.println(" V");
  Serial.println("****************************");
  //Serial.print("V_rms = "); Serial.println(V_rms, 3);
  //Serial.print("V_mean_MCP= "); Serial.println(y_3, 3);
  //Serial.print("y_2= "); Serial.println(y_2, 3);
  
  delay(2000);
  
  //Serial.print("\t");
  //Serial.println(channel2);
  
}
