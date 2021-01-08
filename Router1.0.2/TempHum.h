Temperature TempHum(){
    /********************** Temperature code **************************/
    float T = sht31.readTemperature(); delay(5);
    float H = sht31.readHumidity();
    byte TintTemp = byte(T);    
    byte HintTemp = byte(H);

    Temperature temperature = Temperature();

    //check if temperature and humidity ar not a numbers
    if(!isnan (T)){
        temperature.Tint = (int)T;
        temperature.Tdecimal = (int)(TintTemp-T)*-100;
    }
    else{
        //Serial.println("Failed to read Temperature");
        temperature.Tint = 0;
        temperature.Tdecimal = 0;
    }
    
    if (! isnan(H)) {
        temperature.Hint = (int)H;
        temperature.Hdecimal = (int)(HintTemp - H)*-100;    
    }
    else{
        //Serial.println("Failed to reaf humidity");
        temperature.Hint = 0;
        temperature.Hdecimal = 0; 
    }
    return temperature;
}