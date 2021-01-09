/*
  TempHum.h - Library for reading temperature and humidity using the DHT22NEW lib.
  Created by Joshua B. Jerez, Enero 9, 2021.
  Released into the public domain.
  This library works with dhtnewlib, its output is set in a structure Temperature
*/
#ifndef TempHum_h_

#define TempHum_h_
#include "Arduino.h"
#include "dhtnew.h"

class TempHum{
    public:
        TempHum();
        void begin(uint8_t pin);    
        int getTempInt() {return _Tint;};
        int getTempDecimal() {return _Tdecimal;};
        int getHumInt(){return _Hint;};
        int getHumDec(){return _Hdecimal;};
                
    private:
        float _Temp = 0.0;
        float _Hum = 0.0;
        int _Tint = 0.0;
        int _Tdecimal = 0.0;
        int _Hint = 0.0;
        int _Hdecimal = 0.0;      
        void TempHumRead(DHTNEW dhtpin);  
        DHTNEW _dhtpin;
};

#endif