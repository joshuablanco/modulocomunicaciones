#include <Arduino.h>
#include "TempHum.h"
#include "dhtnew.h"

void TempHum::begin(uint8_t pin){
    DHTNEW _dhtpin(pin);
}

void TempHum::TempHumRead(DHTNEW dhtpin){
    int chk = dhtpin.read();
    delay(500);
    if(chk == DHTLIB_OK){
        _Temp = dhtpin.getTemperature();        
        _Hum = dhtpin.getHumidity();

        byte TintTemp = byte(_Temp);    
        byte HintTemp = byte(_Hum);

        //check if temperature and humidity ar not a numbers
        if(!isnan (_Temp)){
            _Tint = (int)_Temp;
            _Tdecimal = (int)(TintTemp-_Temp)*-100;
        }
        else{
            //Serial.println("Failed to read Temperature");
            _Tint = 0;
            _Tdecimal = 0;
        }
        
        if (! isnan(_Hum)) {
            _Hint = (int)_Hum;
            _Hdecimal = (int)(HintTemp - _Hum)*-100;    
        }
        else{
            //Serial.println("Failed to reaf humidity");
            _Hint = 0;
            _Hdecimal = 0; 
        }         
    }
}

