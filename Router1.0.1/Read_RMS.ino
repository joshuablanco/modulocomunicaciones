void Read_RMS(){
  
  ////// Find Rms value Average     
  boolean FlagNo = false;
  FlagNo = false;  
  
  while(FlagNo == false){  // 500 samples
    
    adcVal_0 = adc.readChannel(0);
    //adcVal_1 = adc.readChannel(1);
    
    readRms.update(adcVal_0);
    MeasAvg.update(adcVal_0);
    
    cnt++;
    
    if(cnt >= 500) { // publish every 0.5s
      
      readRms.publish();     
      MeasAvg.publish();
      
      VTC = readRms.rmsVal;
      VTC_mean = MeasAvg.average;
      
      VTC = Fit_Rms(VTC); // Fitted Value
      
//      Serial.print("VTC: ");
//      Serial.print(VTC,3);
//      Serial.print(", ");
//      Serial.println(VTC_mean,3);
      
      cnt=0;
      
      FlagNo = true;
    
    }
  delay(1);
  }

}

float Fit_Rms(float RmsVal){
  //RmsMCP_Real = 0.1653*pow(RmsVal,4)-0.4892*pow(RmsVal,3)+0.4305*pow(RmsVal,2)+0.8739*RmsVal+0.006338;
  RmsMCP_Real = -1.48*pow(RmsVal,4)+2.381*pow(RmsVal,3)-1.194*pow(RmsVal,2)+1.18*RmsVal-0.01193;  
  return RmsMCP_Real;   
}
