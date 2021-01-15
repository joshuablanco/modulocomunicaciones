Battery EnergyBat(Adafruit_INA219 ina219){
    //Monitoring the Battery

    float busVoltage = ina219.getBusVoltage_V();
    float shuntvoltage = ina219.getShuntVoltage_mV();
    float TotalVoltage = busVoltage + (shuntvoltage/1000);
    float current_mA = ina219.getCurrent_mA();

    Battery battery = Battery();

    battery.ShuntVoltageInt = (int)TotalVoltage;    
    float valueTempVolt = (TotalVoltage - (byte)TotalVoltage)*100;
    battery.ShuntVoltageDecimal = (int)valueTempVolt;

    battery.CurrentmaInt = (int)current_mA;
    float valueTempCurr = (current_mA - (byte)current_mA)*100;  
    battery.CurrentmaDecimal = (int)valueTempCurr;

    return battery;
}

CurrentData Grafica(/*int ADC_INPUT, float VTC_Mean*/){
    
    CurrentData plott = CurrentData();

    return plott;
}