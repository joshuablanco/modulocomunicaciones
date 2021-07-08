Battery EnergyBat(Adafruit_INA219 ina219){
    //Monitoring the Battery

    float busVoltage = 0;
    float shuntvoltage = 0;
    float TotalVoltage = 0;
    float current_mA = 0;
    float power_mW = 0;
    
    busVoltage = ina219.getBusVoltage_V();
    shuntvoltage = ina219.getShuntVoltage_mV();
    TotalVoltage = busVoltage + (shuntvoltage/1000);
    current_mA = ina219.getCurrent_mA();
    power_mW = ina219.getPower_mW();
    
    Serial.print("Current***:       ");Serial.print(TotalVoltage,3);Serial.print(",");Serial.println(current_mA,3);
    
    
    Battery battery = Battery();

    battery.ShuntVoltageInt = (int)TotalVoltage;    
    float valueTempVolt = (TotalVoltage - (byte)TotalVoltage)*100;
    battery.ShuntVoltageDecimal = (int)valueTempVolt;

    battery.CurrentmaInt = (int)current_mA;
    float valueTempCurr = (current_mA - (byte)current_mA)*100;  
    battery.CurrentmaDecimal = (int)valueTempCurr;
//    Serial.println("VALORES DE ENERGIA ----> ");
//    Serial.println(battery.ShuntVoltageInt);
//    Serial.println(battery.ShuntVoltageDecimal);
//    Serial.println(battery.CurrentmaInt);
//    Serial.println(battery.CurrentmaDecimal);
    return battery;
}
