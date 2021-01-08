#include <MCP3202.h>
MCP3202 adc = MCP3202(10);

#include "ListLib.h"

List<int> list;

const int sensorPin=A0;

int Value;
int i;//--
int channel1 = 0;//--
int counter = 0;//--
int Count_Zero = 0;
int n=0;
int Flag = 1;
int Flag1 =1;
int Num_Samples = 0;

float New;
double Iint = 0;
double VTC = 0;
double channel2 = 0;

boolean Count_Zero_Logic = true;
boolean LogValue = true;
boolean Channel1_Logic = true;


double polinom;
void setup() {
  adc.begin();
  Serial.begin(9600);
  analogReference(INTERNAL);
}

void loop() { 
  //polinom = 0.005562738 + 0.9896483*x + 0.004373228*x^2
  i = 0;
  n = 0;//--
  Flag = 1;
  counter = 0;
  Count_Zero = 0;
  Count_Zero_Logic = true;
  channel2 = 0;
  
  while(n < 200 && Flag ==1 ){
    channel1 = adc.readChannel(0);
    //channel1 = analogRead(sensorPin);
    //Serial.print("First Read: ");Serial.println(channel1); 
    delay(50);
    if(channel1 == 0){
      counter = counter+1;   
      //Serial.print("counter : ");Serial.println(counter);
      }
    Channel1_Logic = (counter && channel1) ? false:true;   //channel logic is used to identify where is a positive value
    //Serial.print("Channel1_Logic : ");Serial.println(Channel1_Logic);
    
    while(i < 400 && counter > 14 && Channel1_Logic == false && Count_Zero_Logic == true){//Count_Zero_Logic for sensing zeros on readings  LogValue == true
      //Serial.println("entro : "); 
      channel1 = adc.readChannel(0);
      
      //channel1 = analogRead(sensorPin);
      channel2 = (double) channel1;
      channel2 = channel2 *(3.241/4095);
      Serial.println(channel2);
      if(channel1 == 0){Count_Zero = Count_Zero + 1; }else{Count_Zero = 0; Num_Samples = Num_Samples +1;}//count zero check zeros in a cycle of the signal
      Count_Zero_Logic = (Count_Zero > 10) ? false:true;
      //polinom = 0.005562738 + 0.9896483*channel2 + 0.004373228*pow(channel2,2);
      polinom =  1.00066*channel2 + 0.0002008773;
      Serial.println(polinom,4);
      Iint = Iint + (sq(polinom));      
      delay(50);
      //Serial.println(channel1);
      //Value = map(channel1, 0 , 4095, 0,  255);
      //Serial.write(Value);
      //Serial.println(channel1);
      //LogValue = true;
      //Serial.print("LogValue: ");Serial.println(LogValue);
      //list.Add(channel1);
      
      Flag = 0;
      i=i+1;      
      
      }   
    n=n+1;   
  }
  
  if(Num_Samples > 0){
    //VTC = 1.18*(sqrt(Iint / Num_Samples))*(1.1/1023);
    VTC = (sqrt(Iint / Num_Samples))*(3.3/4095);
    
    Serial.println(VTC,3);
    
    }
  
  if(Num_Samples == 500){
    Num_Samples=0;
    VTC=0;
    Iint=0;
    }

  } 
 
