/*
  WaterRead.h - Library for Detecting water.
  Created by Joshua B. Jerez, Enero 8, 2021.
  Released into the public domain.
*/
#ifndef WaterRead_h_
#define WaterRead_h_
#include "Arduino.h"
/// <summary>
/// Header de la clase para instanciar la lectura de agua
/// </summary>
class WaterRead {
    public:
        WaterRead();
        void begin(uint8_t ADC_INPUT1);
        int WaterState();     

    private:
        int _waterRead;
        int _ADC_INPUT = 0;        
};
#endif 

