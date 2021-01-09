#include <Arduino.h>
#include "WaterRead.h"

void WaterRead::begin(uint8_t ADC_INPUT){
    _ADC_INPUT = ADC_INPUT;   
}

int WaterRead::WaterState(){
 
    int waterState=0;
    uint8_t sensorValue = analogRead(_ADC_INPUT);   
    
    
    if (sensorValue >= 300){
        //Serial.print("Water : ");Serial.println(1);
        //Xbee_Serial.write(byte(1));   
        waterState = 1;
    } 
    else {      
        //Serial.print("Water : ");Serial.println(0);
        //Xbee_Serial.write(byte(0));      
        waterState = 0;
    }
    return waterState;
}

