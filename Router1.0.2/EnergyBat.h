Battery EnergyBat(){
    //Monitoring the Battery

    float busVoltage = 0;
    float shuntvoltage = 0;
    float current_mA = 0;
    float TotalVoltage = 0;

    busVoltage = ina219.getBusVoltage_V();
    shuntvoltage = ina219.getShuntVoltage_mV();
    TotalVoltage = busVoltage + (shuntvoltage/1000);
    current_mA = ina219.getCurrent_mA();

    Battery battery = Battery();

    battery.ShuntVoltageInt = (int)TotalVoltage;
    battery.ShuntVoltageDecimal = (int)(TotalVoltage - (byte)TotalVoltage)*100;

    battery.CurrentmaInt = (int)current_mA;
    battery.CurrentmaDecimal = (int)(current_mA - (byte)current_mA)*100;  

    return battery;
}
