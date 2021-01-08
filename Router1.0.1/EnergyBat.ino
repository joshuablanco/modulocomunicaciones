void EnergyBat(){
  //Monitoring the Battery
  float busVoltage = 0;
  float shuntvoltage = 0;
  float current_mA = 0;
  float TotalVoltage = 0;
  
  busVoltage = ina219.getBusVoltage_V();
  shuntvoltage = ina219.getShuntVoltage_mV();
  TotalVoltage = busVoltage + (shuntvoltage/1000);
  current_mA = ina219.getCurrent_mA();

  byte ShuntVoltageInt = byte(TotalVoltage);
  int ShuntDecimal = (TotalVoltage - ShuntVoltageInt)*100;
  
  byte CurrentmaInt = byte(current_mA);
  int CurrentDecimal = (current_mA - CurrentmaInt)*100;  
  
  
  Serial.print("ShuntVoltageInt :");Serial.print(ShuntVoltageInt);Serial.print(",");Serial.println(ShuntDecimal);
  Serial.print("CurrentmaInt :");Serial.print(CurrentmaInt);Serial.print(",");Serial.print(CurrentDecimal); Serial.println(" mA");

  Xbee_Serial.write(byte(ShuntVoltageInt));delay(10);  
  Xbee_Serial.write(byte(ShuntDecimal));delay(10);
  Xbee_Serial.write(byte(CurrentmaInt));delay(10);  
  Xbee_Serial.write(byte(CurrentDecimal));delay(10);
  
  //delay(50);
  
  }
