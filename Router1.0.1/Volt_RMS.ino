  void rms_Plot(){
   
    nTC = 0; // using for the main while
    FlagTC = true; // flag to sample ant put into the list
    Comp_State_Low = false;
    Comp_State_change = false;
    last_Comp_State = HIGH;
    Edge_Counter_L = 0;
    Num_Samples = 0; //count numb diff than cero to divide 
    Num_Samples2 = 0; 
    
    unsigned int Value_Prev = 0;
    float Peak_Val = 0;// using
    MaxCurrent = 0;

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

  void Print_Val_Tail_VTC(){
      // se toma el valor RMS hallado en ReadRms()
      byte VTCint = byte(VTC);
      //Serial.print("*********VTC: ");Serial.println(VTC,3);
      
      // se extrae la parte decimal
      unsigned int VTCdec = (VTC - VTCint) * 1000;
      //Serial.print("VTCint: ");Serial.println(VTCint);  
        
      VTCdec = (uint16_t) VTCdec;
      //Serial.print("VTCdec: ");Serial.println(VTCdec);

      //se separa en dos bytes 
      byte LowByte = (VTCdec & 0x00FF);
      //Serial.print("LowByte: ");Serial.print(LowByte,DEC);Serial.print("LowByte: ");Serial.println(LowByte,BIN);           
      byte HighByte = ((VTCdec & 0xFF00) >> 8);
      //Serial.print("HighByte: ");Serial.print(HighByte,DEC);Serial.print("LowByte: ");Serial.println(HighByte,BIN);   

      Serial.print("VTCint: ");Serial.println(VTCint);   
      Serial.print("HighByte: ");Serial.println(HighByte);   
      Serial.print("LowByte: ");Serial.println(LowByte);  
      Xbee_Serial.write(VTCint);delay(10); // we are sending Voltage RMS.
      Xbee_Serial.write(HighByte);
      Xbee_Serial.write(LowByte); 
      
      Serial.print("MaxCurrent: ");Serial.println(MaxCurrent);   
      Serial.print("Num_Samples: ");Serial.println(Num_Samples);   

      Xbee_Serial.write(byte(MaxCurrent));delay(10); // we are sending peak current.
      Xbee_Serial.write(byte(Num_Samples));delay(10); // we are sending Samples.
    
    }
