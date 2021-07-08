Water WaterReads(uint8_t _ADC_PIN){  

  Water wateread;

  int sensorValue = analogRead(_ADC_PIN);
 
  //Serial.print("Agua - Voltaje: ");Serial.println(sensorValue);
        
  
  if (sensorValue >= 100){
      Serial.print("Water - Nivel : ");Serial.println(1);
      //Xbee_Serial.write(byte(1));   
      wateread.WaterState = 1;
  } 
  else {      
      Serial.print("Water - Nivel: ");Serial.println(0);
      //Xbee_Serial.write(byte(0));      
      wateread.WaterState = 0;
  }
  return wateread;
}
