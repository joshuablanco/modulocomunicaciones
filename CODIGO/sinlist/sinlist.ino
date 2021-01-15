#include "ListLib.h"

boolean Current_Rms = true;

float Temperature = 60.70;
float Temperature1 = 0;
String Temperature_Str = "";
char HEADER = 'H';
char TAIL = 'T';

float Humidity = 84.30;
String Humidity_Str = "";
float ShuntVoltage = 3.9;
String ShuntVoltage_Str = "";
float CurrentmaInt = 50.4;
String CurrentmaInt_Str = "";
float AnalogRef = 1.1; //Analog Reference
float CTC = 0;////neww
String CTC_Str = "";
String Power_Str = "";
int Innun = 0;
String SInnun = "";
float Tc = 0;
int MaxCurrent = 0;
String MaxCurrent_Str = "";

int Pflag1 = 0;
int Pflag2 = 0;
int Pflag3 = 0;

int Flag = 0;
const float Resistor = 959;
const float AspectRatio = 100 / 0.05;

List<int> list;
List<int> list1;

byte reception = 0;
float var = 0;
int n = 0;
int i = 0;

unsigned int Value;

void setup() {
  Serial.begin(9600);
}

void SerialData() {
  Current_Rms = true;
  if (Serial.available() > 0) {
    reception = Serial.read();
    var = reception;
    Serial.print("var: ");Serial.println(var);

    list.Add(var);
    //Serial.print("Added: ");Serial.println(var);
    delay(20);

    if (list[list.Count() - 2] == TAIL && list[list.Count() - 1] == 0)
    {
      //Serial.print("list[list.Count()-2]: ");Serial.println(list[list.Count()-2]);
      Serial.print("list[list.Count()-3]: "); Serial.println(list[list.Count() - 3]);
      if ((list[list.Count() - 3] > 15) || (list[list.Count() - 3] == 0 && list[list.Count() - 5] == 255)) {
        Current_Rms = (list[list.Count() - 3] == 0 && list[list.Count() - 5] == 255) ? false:true;
        Serial.print("VTC,Num_Samp: "); Serial.print(list[list.Count() - 5]);Serial.println(list[list.Count() - 3]);
        Serial.print("Current_Rms: "); Serial.println(Current_Rms);
        GettingData();       
      } else {        
        list.Clear(); //double checks the itc value
      }
    }
  }
}

void GettingData() {

  for (int i = 0; i < (list.Count() - 1); i++) {
    Serial.print(list[i]); Serial.print(" ");
    delay(25);
  }

  Serial.println("");

  if ((list[2] == HEADER) && (list.Count() > 13)) {
    Temperature = list[4] + float(list[5]) / 100;
    Humidity = list[7] + float(list[8]) / 100; //value + its decimal
    ShuntVoltage = list[9] + float(list[10]) / 100; //value + its decimal
    CurrentmaInt = list[11] + float(list[12]) / 100; //value + its decimal
    Innun = list[13];
    if (Innun == 0) {
      SInnun = "Seco";
    } else {
      SInnun = "Mojado";
    }
    MaxCurrent = list[list.Count() - 4];
    if (Current_Rms == false) {
      CTC = 0;
      } else {
        Serial.println(" FOR CTC********** :");
        CTC = list[list.Count() - 6] + float(list[list.Count() - 5]) / 100; //value + its decimal
        for (int ni = 0 ; ni <= (list.Count() - 21); ni++) {
          list1.Add(list[14 + ni]);
          Serial.print(list1[ni]); Serial.print(" ");
          delay(20);
          }
        Serial.println(" ");
        }
    Serial.print("Temperature: "); Serial.println(Temperature);
    Serial.print("Humidity: "); Serial.println(Humidity);
    Serial.print("ShuntVoltage: "); Serial.println(ShuntVoltage);
    Serial.print("CurrentmaInt: "); Serial.println(CurrentmaInt);
    Serial.print("SInnun: "); Serial.println(SInnun);
    Serial.print("MaxCurrent: "); Serial.println(MaxCurrent);
    Serial.print("VTC: "); Serial.println(CTC);
  }
  list.Clear();
  
}

void loop(void) {
  //SerialData();
//  list1.Clear();

  if(Serial.available() > 0){
    reception=Serial.read();
    var = reception;
    //Serial.print("var: ");
    Serial.println(var);
  }

}
