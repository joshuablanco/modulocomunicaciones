 #include <MCP3202.h>
MCP3202 adc = MCP3202(10);
#include <Wire.h>
#include <Adafruit_INA219.h>

int channel1_3 = 0;//A3 DC
int channel1_2 = 0;//A2 ATMEGA energy double checking 
int Comp_State =0;

const int numberOfEntries = 250; // even number//using
const int SensorPin2 = A2;//using
const int SensorPin3 = A3;//using
const int SensorPin0 = A1;//using
const int Comp_Pin = 3;//using     // the number of the pushbutton pin

unsigned int channel0_MCP; // using

Adafruit_INA219 ina219;

float channel2_0_MCP = 0;
float channel2_2 = 0; // //using------
float channel2_3 = 0; // //using fgvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvd<<<<<<<<<<<<<<<<<<<<<<<<<<<<<.{-v          p'0´      ,mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmgf7 ------
float y_3 = 0; //using
float y_2 = 0; //using
float y_0_MCP =  0; //using
float V_mean = 0; //using
float Samp;//using
float TotalVoltage = 0; //using
float y_INA = 0;//using
float V_mean_INA = 0; //using
float Offet_Opam = 0.001; //using important measure the offset of the opamp 
float results[numberOfEntries];//using
float results2[numberOfEntries];//using
float results3[numberOfEntries];

void setup() {

  adc.begin();
  Serial.begin(115200);
  
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

  
  for (int i = 0; i < (numberOfEntries) - 1 ; i++) {
    //channel1_3 = analogRead(SensorPin3);// A3 DC
    //channel1_2 = analogRead(SensorPin2);// A2 SIG
    Comp_State = digitalRead(Comp_Pin); 
    
    channel0_MCP = adc.readChannel(0);///SIGNAL   
    
    //channel2_0 = channel1_0 * V_mean_INA / 1023;
    
    
    //channel2_3 = channel1_3 * 3.27 / 1023;//DC
    //channel2_2 = channel1_2 * 3.27 / 1023;//DC
    //y_2 = 0.9802*channel2_2 + 0.0141;//ATMEGA WORKS
    //channel2_0_MCP = channel0_MCP * 3.27 / 4095; //MCP  
    
    //y_0_MCP = 0.9846821*channel2_0_MCP + 0.00002821247;/// MCP error less than 1% 
    
    results[i]  = channel0_MCP;//MCP
    results2[i] = Comp_State*100 ;//ATMEGA
    //results3[i] = channel1_3 *4;//DC
    //Samp = Samp + 1;
    
    //V_mean = V_mean + channel2_3;
    
    //V_mean = V_mean / 2;
    
    delay(33);    
  }  
  //y_3 = 0.9949*V_mean + 0.021;
  //y_3 = 0.9802*V_mean + 0.0141;//ATMEGA WORKS
  //y_3 = 0.9846821*V_mean + 0.00002821247;/// MCP error less than 1%
  
}

void mean_Val_INA(){// DOUBLE CHECK THE Y_INA BCAUSE IS INSIDE OF THE FOR LOOP EXTRACT IT
  
  Samp = 0;
  V_mean = 0;
  
  for (int i = 0; i < 20; i++) {
    
    float shuntvoltage = 0;
    float busvoltage = 0;
    TotalVoltage = 0;
    
    shuntvoltage = ina219.getShuntVoltage_mV();
    busvoltage = ina219.getBusVoltage_V();
    TotalVoltage = busvoltage + (shuntvoltage / 1000);    
    
    y_INA = 0.9842*TotalVoltage + 0.0921;
    
    //Serial.print("TotalVoltage :   "); Serial.print(TotalVoltage, 3); Serial.println(" V");
    //Serial.print("y :   "); Serial.print(y, 3); Serial.println(" V");
    Samp = Samp + 1;
    
    V_mean_INA = V_mean_INA + y_INA;
    
    //Serial.print(" ");Serial.print(i);
    
    V_mean_INA = V_mean_INA / 2;
    
    delay(2);
  }

  
}

void loop() {
  
//  V_rms = 0;  
//  V_samp = 0;
  
  //mean_Val_INA();  
  //mean_Val();
//  
  for(int i = 0; i < (numberOfEntries) - 1; i++)
  {
    //V_samp = V_samp + (sq(results[i] - 1.506));
       
    //Serial.print(y_3*100);Serial.print(",");
    //Serial.print(results[i]);Serial.print(",");Serial.println(results2[i]);//Serial.print(",");Serial.println(results3[i]);
    channel0_MCP = adc.readChannel(0);///SIGNAL 
    
    //Comp_State = digitalRead(Comp_Pin); 
    //channel2_0_MCP = (channel0_MCP * (3.2 / 4095) )- (analogRead(SensorPin3)*(3.2 / 1023)) - Offet_Opam; //MCP 
    Serial.println(channel0_MCP);//Serial.print(",");Serial.println(Comp_State*10);
    delay(50); 
    
    } 
//  //channel1_3 = analogRead(SensorPin3);// A3 DC
//  
//  for(int i = 0; i < (numberOfEntries) - 1; i++)
//  {
//    //V_samp = V_samp + (sq(results[i] - 1.506));
//       
//    //Serial.print(y_3*100);Serial.print(",");
//    //Serial.print(results[i]);Serial.print(",");Serial.print(results2[i]);Serial.print(",");Serial.println(results3[i]);
//    channel1_2 = analogRead(SensorPin2);// A2 SIG
//    Serial.println(channel1_2);
//    delay(33); 
//    
    //} 
  
      
  //V_rms = (sqrt(V_samp / numberOfEntries));
    
  //put your main code here, to run repeatedly:
  //channel1 = adc.readChannel(0);
  //channel1 = analogRead(SensorPin1);

  //channel2 = channel1 * V_mean_INA / 1023;
  
  //y = 0.9667298*channel2 + 0.1106196;
  //y = 34.82459 + (0.1922545 - 34.82459)/(1 + pow((channel2/26.05911),1.120971));// ADC A2

  //y = 0.04552349 - (-0.9881568/-0.00106696)*(1 - pow(2.718281828,(0.00106696*channel2)));
  //y = 0.9902*channel2 + 0.0439;
  //y = 0.990353*channel2 + 0.04345021;
  //y = 0.0243711 + 1.027849*channel2 - 0.02148362*pow(channel2,2) + 0.003729733*pow(channel2,3);

  //y = -0.06898462 - (-1.047894/0.02126661)*(1 - pow(2.718281828,(-0.02126661*channel2)));
  //y = -0.06889697 + 1.047535*channel2 - 0.01081482*pow(channel2,2);
  //y = 13.51108 + (0.1078404 - 13.51108)/(1 + pow((channel2/8.468104),1.257299));
  //channel2 = adc.readChannel(1);

  //Serial.print("V_rms = "); Serial.println(V_rms, 3);
  //Serial.print("V_mean_MCP= "); Serial.println(y_3, 3);
  //Serial.print("y_2= "); Serial.println(y_2, 3);
  
  //delay(33);
  
  //Serial.print("\t");
  //Serial.println(channel2);
  
}
