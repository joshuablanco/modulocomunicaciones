TemperatureStruct TempHum(DHTNEW dhtpin1){    

    /********************** Temperature code **************************/
    int dhtread = dhtpin1.read();

    TemperatureStruct temperature = TemperatureStruct();

    switch (dhtread)
    {
      case DHTLIB_OK:
        Serial.print("OK,\t");
        Serial.println("Entro");
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
        delay(550);
        Serial.println(temperature.Hint);
        Serial.println(temperature.Hdecimal);
        Serial.println(temperature.Tint);
        Serial.println(temperature.Tdecimal);
        return temperature;
        break;
      case DHTLIB_ERROR_CHECKSUM:
        Serial.print("Checksum error,\t");
        temperature.Tint = 0;
        temperature.Tdecimal = 0;
        temperature.Hint = 0;
        temperature.Hdecimal = 0; 
        //delay because this sensor has a minimum of 2 s to be sensed
        delay(500);
        return temperature;
        break;
      case DHTLIB_ERROR_TIMEOUT_A:
        Serial.print("Time out A error,\t");
        temperature.Tint = 0;
        temperature.Tdecimal = 0;
        temperature.Hint = 0;
        temperature.Hdecimal = 0; 
        //delay because this sensor has a minimum of 2 s to be sensed
        delay(500);
        return temperature;
        break;
      case DHTLIB_ERROR_TIMEOUT_B:
        Serial.print("Time out B error,\t");
        temperature.Tint = 0;
        temperature.Tdecimal = 0;
        temperature.Hint = 0;
        temperature.Hdecimal = 0; 
        //delay because this sensor has a minimum of 2 s to be sensed
        delay(500);
        return temperature;
        break;
      case DHTLIB_ERROR_TIMEOUT_C:
        Serial.print("Time out C error,\t");
        temperature.Tint = 0;
        temperature.Tdecimal = 0;
        temperature.Hint = 0;
        temperature.Hdecimal = 0; 
        //delay because this sensor has a minimum of 2 s to be sensed
        delay(500);
        return temperature;
        break;
      case DHTLIB_ERROR_TIMEOUT_D:
        Serial.print("Time out D error,\t");
        temperature.Tint = 0;
        temperature.Tdecimal = 0;
        temperature.Hint = 0;
        temperature.Hdecimal = 0; 
        //delay because this sensor has a minimum of 2 s to be sensed
        delay(500);
        return temperature;
        break;
      case DHTLIB_ERROR_SENSOR_NOT_READY:
        Serial.print("Sensor not ready,\t");
        temperature.Tint = 0;
        temperature.Tdecimal = 0;
        temperature.Hint = 0;
        temperature.Hdecimal = 0; 
        //delay because this sensor has a minimum of 2 s to be sensed
        delay(500);
        return temperature;
        break;
      case DHTLIB_ERROR_BIT_SHIFT:
        Serial.print("Bit shift error,\t");
        temperature.Tint = 0;
        temperature.Tdecimal = 0;
        temperature.Hint = 0;
        temperature.Hdecimal = 0; 
        //delay because this sensor has a minimum of 2 s to be sensed
        delay(500);
        return temperature;
        break;
      case DHTLIB_WAITING_FOR_READ:
        Serial.print("Waiting for read,\t");
        temperature.Tint = 0;
        temperature.Tdecimal = 0;
        temperature.Hint = 0;
        temperature.Hdecimal = 0; 
        //delay because this sensor has a minimum of 2 s to be sensed
        delay(500);
        return temperature;
        break;
      default:
        Serial.print("Unknown: ");
        Serial.print(dhtread);
        Serial.print(",\t");
        temperature.Tint = 0;
        temperature.Tdecimal = 0;
        temperature.Hint = 0;
        temperature.Hdecimal = 0; 
        //delay because this sensor has a minimum of 2 s to be sensed
        delay(500);
        return temperature;
        break;
    }   
}
