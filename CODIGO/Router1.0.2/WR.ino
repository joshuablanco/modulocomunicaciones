Water WaterReads(uint8_t _ADC_PIN){  

  Water wateread;

  uint8_t sensorValue = analogRead(_ADC_PIN);
  Serial.print("Water : ");Serial.println(sensorValue);
  delay(10);      
  
  if (sensorValue >= 100){
      //Serial.print("Water : ");Serial.println(1);
      //Xbee_Serial.write(byte(1));   
      wateread.WaterState = 1;
  } 
  else {      
      //Serial.print("Water : ");Serial.println(0);
      //Xbee_Serial.write(byte(0));      
      wateread.WaterState = 0;
  }
  return wateread;
}
