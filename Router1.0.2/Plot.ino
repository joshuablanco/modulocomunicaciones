void rms_Plot(){   
    
    unsigned int Edge_Counter_L = 0; // using
    boolean Comp_State_Low = false;//using
    boolean Comp_State_change = false; //using
    boolean Comp_State = true;//using
    boolean last_Comp_State = HIGH;//using
    
    int FlagTC = true; ////using flag to sample ant put into the list //using
    unsigned int nTC = 0; //using
    
    float channel1_2_float;
    int channel1_2 = 0;//A2 ATMEGA energy double checking 
    
    float Num_Samples = 0;////count numb diff than cero to divide
    
    
    unsigned int Value_Prev = 0;
    unsigned int Value;// valor que se mapea para ser enviado
    float Peak_Val = 0;// using
    int Peak_Val_Noff;//peak value no offset
    float MaxCurrent = 0;
    
    while(nTC < 700 && FlagTC == true ){
    
      channel1_2 = analogRead(ADC_INPUT);//A2 ATMEGA signal
      channel1_2_float = float(channel1_2) * ADC_Gain *VoltRange/1023; //ADC gain is used to setting up the trigger
      Comp_State_Low = (channel1_2_float > VTC_mean) ? false:true;   
      
      //Serial.print("channel1_2_float : ");Serial.println(channel1_2_float);
      //Serial.print("Comp_State_Low : ");Serial.println(Comp_State); 
      
      while(Comp_State_Low == true){//Comp_State_change contains logic for knowing the rising edge      
        channel1_2 = analogRead(ADC_INPUT);// senal de entrada en puerto A2 
        channel1_2_float = float(channel1_2) *ADC_Gain* VoltRange/1023;  
        Comp_State_Low = (channel1_2_float > VTC_mean ) ? false:true;// se verifica si esta por encima de la media
        Comp_State_change = (Comp_State_Low == false) ? true:false; // To know if there was a change with respect VTCMEAN
        delay(1);  
        //Serial.print("channel1_2_float : ");Serial.println(channel1_2_float);
        
      }
      // if the signal cross by VTCMEAN, start to sample the signal with the edges  
      while(Edge_Counter_L < 5  && Comp_State_change == true && Num_Samples < 300){
        //Count_Zero_Logic for sensing zeros on readings  LogValue == true
        //Serial.println("entro : ");
        
        //channel1_2 = adc.readChannel(0);
        channel1_2 = analogRead(ADC_INPUT);    
        channel1_2_float = float(channel1_2) * ADC_Gain * VoltRange/1023; 
        /*
         verification of crossing VTCMEAN, if it does that means that 
         changed the edge sense of the signal.
        */
        
        Comp_State =(channel1_2_float > VTC_mean) ? true:false;   
                             
        if (Comp_State != last_Comp_State) {  //edge verification 5 cycles 
          Edge_Counter_L++;    // hubo cambio de flanco
          //Serial.print("Edge_Counter_L:    ");Serial.println(Edge_Counter_L);
          }
        
        // assign current edge or zone
        last_Comp_State = Comp_State; 
        
        /////MAXIMUM VALUE PEAK VALUE//////
        if(channel1_2 > Value_Prev && channel1_2 > Peak_Val){
          Peak_Val = channel1_2; 
          Peak_Val = float(Peak_Val) * Scale_Plot_Axis * VoltRange/1023;
          //Serial.print("Peak_Val: ");Serial.println((float(Peak_Val) *1.054* VoltRange/1023));
          //Serial.print("VTC_mean: ");Serial.println(VTC_mean,3);
          MaxCurrent = abs(Peak_Val - VTC_mean)/Sensitivity;// PEAK CURRENT VALUE WITHOUT NO OFFSET
          }
        // the value is saved for future comparaisons
        Value_Prev = channel1_2;
        
        Value = map(channel1_2, 0, 1023, 0, 255);//160 
        
        Serial.println(Value);
        Xbee_Serial.write(byte(Value)); //// SENDING THE SIGNAL WHILST THE PEAK VALUE IS FOUND          
        
        Num_Samples = Num_Samples +1;          
                        
        FlagTC = false;
        
        delay(50);
        }   
      nTC=nTC+1;
      delay(1);   
    }
}

    
