void TempHum(){  
  /********************** Temperature code **************************/
  float T = sht31.readTemperature(); delay(5);
  float H = sht31.readHumidity();
  byte Tint = byte(T);
  int Tdecimal = (Tint-T)*-100;
  byte Hint = byte(H);
  int Hdecimal = (Hint - H)*-100;
  
  if(!isnan (T)){//check if ;is not a number
    heat = heat + 1;
    //Serial.write(byte(1));
    //Serial.println(1);
    delay(10);
    
    //Serial.write(Tint);delay(10);Serial.write(byte(Tdecimal));
    //Serial.print("Temperature :");Serial.print(Tint);Serial.print(",");Serial.print(Tdecimal);Serial.println("°C");
    delay(10);
    }else{
      //Serial.println("Failed to read Temperature");
      }
    
  if (! isnan(H)) {//check if ;is not a number
    //Serial.println(2);
    //Serial.print("Humidity :");Serial.print(Hint);Serial.print(",");Serial.print(Hdecimal);Serial.println("%");
    //Serial.write(byte(2));delay(10);
    //Serial.write(byte(Hint));delay(10);Serial.write(byte(Hdecimal));
    delay(10);
    
    }else{//Serial.println("Failed to reaf humidity");
      }
      
  if(heat >= 1000){// HEATER
    sht31.heater(true);
    //Serial.println("heater activated************************");
    delay(6000);
    heat = 0;
    }else{
      sht31.heater(false);//Serial.println("heater off");
    } 
    delay(10);
    }
    
