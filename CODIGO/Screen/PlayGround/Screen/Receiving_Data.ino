void SerialData( ){ 
  Current_Rms = true;

  if(Serial.available() > 0){
    reception = Serial.read();
    var=reception;
    //Serial.print(var);Serial.print(",");   
    list.Add(var);
    //Serial.print("Added: ");Serial.println(var);
    //delay(20);  
    
    if(list[list.Count()-2] == TAIL && list[list.Count()-1] == 0)//&& list.Count()
      {
  //    Serial.print("list[list.Count()-3]: "); Serial.println(list[list.Count() - 3]);
        if ((list[list.Count() - 3] > 15) || (list[list.Count() - 3] == 0 && list[list.Count() - 5] == 255)) {
          Current_Rms = (list[list.Count() - 3] == 0 && list[list.Count() - 5] == 255) ? false:true;
//          Serial.println(" ");
//          Serial.print("VTC,Num_Samp: "); Serial.print(list[list.Count() - 5]);Serial.println(list[list.Count() - 3]);
//          Serial.print("Current_Rms: "); Serial.println(Current_Rms);
          GettingData();       
          } else {        
            list.Clear(); //double checks the itc value
            Serial.println(" :(");
            }
        }
  } 
}          

void GettingData(){
//  Serial.println("Enteed GettingData");
//  for(int i =0; i < (list.Count()-1); i++){
//    Serial.print(list[i]);Serial.print(" ");delay(25);    
//  }
    
// Serial.println("");
 
  if((list[2] == HEADER) && (list.Count() > 13)){
    Up_Flag = true;
    Temperature_I = (int)list[4];
    Temperature_D = (int)list[5];
    Temperature=list[4]+float(list[5])/100;
    
    Humidity_I = (int)list[7];
    Humidity_D = (int)list[8];
    Humidity = list[7]+float(list[8])/100; //value + its decimal 
    
    ShuntVoltage_I = (int)list[9];
    ShuntVoltage_D = (int)list[10];
    ShuntVoltage = list[9]+float(list[10])/100; //value + its decimal
    
    CurrentmaInt_I = (int)list[11];
    CurrentmaInt_D = (int)list[12];    
    CurrentmaInt = list[11]+float(list[12])/100; //value + its decimal
    
    Innun = list[13];
    //if(Innun == 0){SInnun="Seco";}else{SInnun="Mojado";}
    SInnun = (Innun == 0) ? "Seco":"Mojado";
    
    MaxCurrent = (int) ((map(list[list.Count()-4],0,255,0,1023)*(3.27/1023))*conversorV_I*1.5);
    if(MaxCurrent == 0){MaxCurrent = 1 ;}else{MaxCurrent = (int) ((map(list[list.Count()-4],0,255,0,1023)*(3.27/1023))*conversorV_I*1.5);}
    //Serial.print("iTC: ");Serial.println(iTC);
    if (Current_Rms == false){
      CTC = 0; 
      Up_Flag = true; // for avoiding entrance and to print by mistake        
      } else {      
        CTC = 0;
        Up_Flag = true;
        //Serial.println(" FOR CTC********** :");
        //Serial.print("VTC int: ");Serial.print((list[list.Count()-6]));Serial.print("VTC dec: ");Serial.println((list[list.Count()-5]));     

        uint16_t VTCdec = 0;
        byte LowByte = list[list.Count()-5];
        byte HighByte = list[list.Count()-6];
        
        VTCdec = (HighByte &  0x00FF) << 8;
        VTCdec = VTCdec | LowByte ;
        
        Serial.print("HighByte: ");Serial.println(HighByte); 
        CTC = list[list.Count()-7]+(float(VTCdec))/1000; //value + its decimal
        CTC = CTC *(conversorV_I);        
        list1.Clear();
        for (int ni=0 ; ni <= (list.Count()-25); ni++){//(list.Count()-21)
          //TClist[ni]= list[13+ni];
          list1.Add(list[14+ni]);
          //Serial.print(list1[ni]);Serial.print(" ");
          delay(10);                
          }
          //Serial.println(" ");                              
          }
  Dew_Point = Temperature - ((100-Humidity)/5);          
//  Serial.print("Temperature: ");Serial.println(Temperature);
//  Serial.print("Humidity: ");Serial.println(Humidity);
//  Serial.print("ShuntVoltage: ");Serial.println(ShuntVoltage);
//  Serial.print("CurrentmaInt: ");Serial.println(CurrentmaInt); 
//  Serial.print("SInnun: ");Serial.println(SInnun);
//  Serial.print("MaxCurrent: ");Serial.println(MaxCurrent);           
//  Serial.print("CTC: ");Serial.print(CTC);
//  Serial.print("Dew Point: ");Serial.println(Dew_Point);    
    }    
  list.Clear();   
  
  }
  
