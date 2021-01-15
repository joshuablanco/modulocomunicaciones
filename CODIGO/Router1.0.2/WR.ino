Water WaterReads(uint8_t _ADC_PIN){  

  Water wateread;

  uint8_t sensorValue = analogRead(_ADC_PIN);
  delay(10);      
  
  if (sensorValue >= 300){
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