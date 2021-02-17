// ADC input is tented to change cause depends on the new librarym ADCGain
// ADCGain by default 1
// Sensitivity.  Parameter to INPUT related with the current sensor characterizing
// VoltRange. ADC full scale peak-to-peak is 5.00Volts measure in full operation
// ADC_Gain.        1.05 related with the trigger
// Scale_Plot_Axis. Scale Data to plot in the screen y-axis in Coordinator
GraficaStruct rms_Plot(MCP331 adc, float ADC_Gain, float Scale_Plot_Axis, float VoltRange, float Sensitivity, CurrentData currentdata){   
    
    GraficaStruct graficaStruct = GraficaStruct();

    unsigned int Edge_Counter_L = 0; // using
    bool Comp_State_Low = false;//using
    bool Comp_State_change = false; //using
    bool Comp_State = true;//using
    bool last_Comp_State = true;//using
    
    bool FLAG_SIGNAL_SAMPLED = true; ////using flag to sample ant put into the list //using
    unsigned int nTC = 0; //using
    
    float channel1_2_float;
    int channel1_2 = 0;//A2 ATMEGA energy double checking 
    
    unsigned int Num_Samples = 0;////count numb diff than cero to divide
    float Num_Bits = ((float)pow(2, ADC_14BIT) - 1);
    const int cicles  = 5; //cicles to sample

    unsigned int Value_Prev = 0;
    //unsigned int Value;// valor que se mapea para ser enviado commented
    float Peak_Val = 0;// using
    float MaxCurrent = 0;
    
    while(nTC < 700 && FLAG_SIGNAL_SAMPLED == true ){ // the ntc 700 has to be double checked
    
      channel1_2 = adc.readMCP331();//A2 ATMEGA signal
      channel1_2_float = float(channel1_2) * ADC_Gain * VoltRange/Num_Bits; //ADC gain is used to setting up the trigger
      Comp_State_Low = (channel1_2_float > currentdata.VTC_Mean) ? false:true;   
      
      //Serial.print("channel1_2_float : ");Serial.println(channel1_2_float);
      //Serial.print("Comp_State_Low : ");Serial.println(Comp_State); 
      
      while(Comp_State_Low == true){//Comp_State_change contains logic for knowing the rising edge      
        channel1_2 = adc.readMCP331();
        channel1_2_float = float(channel1_2) *ADC_Gain* VoltRange/Num_Bits;  
        Comp_State_Low = (channel1_2_float > currentdata.VTC_Mean ) ? false:true;// se verifica si esta por encima de la media
        Comp_State_change = (Comp_State_Low == false) ? true:false; // To know if there was a change with respect VTCMEAN
        delay(1);  
        //Serial.print("channel1_2_float : ");Serial.println(channel1_2_float);
        
      }
      // if the signal cross by VTCMEAN, start to sample the signal with the edges  
      while(Edge_Counter_L < cicles  && Comp_State_change == true && Num_Samples < 300){
        //Count_Zero_Logic for sensing zeros on readings  LogValue == true
        //Serial.println("entro : ");
        
        //channel1_2 = adc.readChannel(0);
        channel1_2 = adc.readMCP331();    
        channel1_2_float = float(channel1_2) * ADC_Gain * VoltRange/Num_Bits; 
        /*
         verification of crossing VTCMEAN, if it does that means that 
         changed the edge sense of the signal.
        */
        
        Comp_State =(channel1_2_float > currentdata.VTC_Mean) ? true:false;   
                             
        if (Comp_State != last_Comp_State) {  //edge verification 5 cycles 
          Edge_Counter_L++;    // hubo cambio de flanco
          //Serial.print("Edge_Counter_L:    ");Serial.println(Edge_Counter_L);
          }
        
        // assign current edge or zone
        last_Comp_State = Comp_State; 
        
        /////MAXIMUM VALUE PEAK VALUE//////
        if(channel1_2 > Value_Prev && channel1_2 > Peak_Val){// CAMBIAR CONDICION A SOLAMENTE LA DEL PICO
          Peak_Val = channel1_2; 
          Peak_Val = float(Peak_Val) * Scale_Plot_Axis * VoltRange/Num_Bits;
          //Serial.print("Peak_Val: ");Serial.println((float(Peak_Val) *1.054* VoltRange/1023));
          //Serial.print("VTC_mean: ");Serial.println(VTC_mean,3);
          MaxCurrent = abs(Peak_Val - currentdata.VTC_Mean)/Sensitivity;// PEAK CURRENT VALUE WITHOUT NO OFFSET
          graficaStruct.MaxCurrent = MaxCurrent;
          }
        // the value is saved for future comparaisons
        Value_Prev = channel1_2;
        
        int Value = map(channel1_2, 0, Num_Bits, 0, 255);//160 
        
        Serial.println(Value);        
        //Xbee_Serial.write(byte(Value)); //// SENDING THE SIGNAL WHILST THE PEAK VALUE IS FOUND  commented because changes in paradigma       
        
        graficaStruct.samples[Num_Samples] = Value;
        Num_Samples = Num_Samples +1;          
                        
        FLAG_SIGNAL_SAMPLED = false;
        
        delay(50);// DOUBLE CHECK THIS VALUE

        }   
        if(FLAG_SIGNAL_SAMPLED){graficaStruct.Num_Samples = Num_Samples;}
        
      nTC = nTC+1;
      delay(5);   
    }
}


    
