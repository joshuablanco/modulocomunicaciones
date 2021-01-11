TemperatureStruct TempHum(DHTNEW dhtpin1){    
        
    /********************** Temperature code **************************/
    int dhtread = dhtpin1.read();

    TemperatureStruct temperature = TemperatureStruct();

    if(dhtread == DHTLIB_OK){
        float T = dhtpin1.getTemperature();
        float H = dhtpin1.getHumidity();

        byte TintTemp = byte(T);    
        byte HintTemp = byte(H);

        //check if temperature and humidity ar not a numbers
        if(!isnan (T)){
            temperature.Tint = (int)T;
            float valueTemp = (TintTemp-T)*-100;
            temperature.Tdecimal = valueTemp;
        }
        else{
            //Serial.println("Failed to read Temperature");
            temperature.Tint = 0;
            temperature.Tdecimal = 0;
        }        
        if (! isnan(H)) {
            temperature.Hint = (int)H;
            float valueTemp = (HintTemp - H)*-100;    
            temperature.Hdecimal = (int)valueTemp;
        }
        else{
            //Serial.println("Failed to reaf humidity");
            temperature.Hint = 0;
            temperature.Hdecimal = 0; 
        }
        //delay because this sensor has a minimum of 2 s to be sensed
        delay(500);
        return temperature;
    }
    else{
        temperature.Tint = 0;
        temperature.Tdecimal = 0;
        temperature.Hint = 0;
        temperature.Hdecimal = 0; 
        //delay because this sensor has a minimum of 2 s to be sensed
        delay(500);
        return temperature;
    }    
}
