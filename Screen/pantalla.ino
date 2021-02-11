/***************************************
 * Def libraries
 **************************************/
 


/****************************************** 
 *  Global variables
 ******************************************/
/*float Temperature = 60.70;
String Temperature_Str = "";
float Humidity = 84.30;
String Humidity_Str = "";
float ShuntVoltage = 3.9;
String ShuntVoltage_Str="";
float CurrentmaInt = 50.4;
String CurrentmaInt_Str="";
float Power = (ShuntVoltage*CurrentmaInt) ;
String Power_Str="";
int Innun = 0;
String SInnun = "";
float Tc=0;

int Pflag1 = 0;
int Pflag2 = 0;
int Pflag3 = 0;

int TC1= 0;
int TC2= 10;
int TC3= 40;
int TC4= 80;
int TC5= 120;
int TC6= 80;
int TC7= 40;
int TC8= 10;
int TC9= 0;
*/



/******************Def pages*********************** 
 *****************************************
NexPage page0 = NexPage(0,0,"page0");
NexPage page1 = NexPage(1,0,"page1");
NexPage page2 = NexPage(2,0,"page2");
NexPage page3 = NexPage(3,0,"page3");
NexPage page4 = NexPage(4,0,"page4");
NexPage page5 = NexPage(5,0,"page5");

/********************Component Nextion page 0*********************
 *****************************************
NexButton b0P0 = NexButton(0,1,"b0P0");
NexButton b1P0 = NexButton(0,2,"b1P0");

/******************Component Nextion page 1***********************
 ******************************************
NexButton b0P1 = NexButton(1,6,"b0P1");
NexButton b1P1 = NexButton(1,1,"b1P1");
//Temperature
NexText t2P1 = NexText(1, 8, "t2P1");
NexProgressBar setprogbar_j0P1 = NexProgressBar(1, 7, "j0P1");
//Humidity
NexText t3P1 = NexText(1, 4, "t3P1");
NexGauge setgauge_z0P1  = NexGauge(1, 2, "z0P1");
NexPicture setpic_p0P1 = NexPicture(1, 11, "p0P1");

/*****************Component Nextion page 2************************
 *****************************************
NexButton b0P2 = NexButton(2,1,"b0P2");
NexButton b1P2 = NexButton(2,2,"b1P2");
NexText setinnun_t0P2 = NexText(2, 4, "t0P2");
NexPicture setpic_p0P2 = NexPicture(2, 3, "p0P2");
NexPicture setpic_p1P2 = NexPicture(2, 6, "p1P2");

/****************Component Nextion page 3*************************
 *****************************************
NexButton b0P3 = NexButton(3,6,"b0P3");//back button
NexButton b1P3 = NexButton(3,14,"b1P3");//next button
NexPicture setBatpic_p0P3 = NexPicture(3, 16, "p0P3");//battery picture
NexPicture setpic_p1P3 = NexPicture(3, 18, "p1P3");//Led alarm I = 0
NexText setShuntVoltage_t3P3 = NexText(3, 12, "t3P3");
NexText setCurr_t4P3 = NexText(3, 11, "t4P3");
NexText setCurrMaxplot_t10P3 = NexText(3, 11, "t10P3");// this is not set
NexText setPow_t5P3 = NexText(3, 10, "t5P3");
NexWaveform set_s0 = NexWaveform(3, 16, "s0");


/**************Component Nextion page 4***************************
 *****************************************
NexButton b0P4 = NexButton(4,5,"b0P4");
NexButton b1P4 = NexButton(4,6,"b1P4");


/*******************Registering objects********************** 
 ****************************************
NexTouch *nex_listen_list[] =
{  // page0
  &b0P0, &b1P0,
  // page 1
  &b0P1, &b1P1, &t2P1, &t3P1, &setpic_p0P1, 
  // page 2
  &b0P2, &b1P2, &setinnun_t0P2, &setpic_p0P2, &setpic_p1P2,
  // page 3
  &b0P3, &b1P3, &setShuntVoltage_t3P3, &setCurr_t4P3, &setPow_t5P3, &setBatpic_p0P3, &setpic_p1P3,
  // page 4
  &b0P4, &b1P4,
  NULL
};
 char buffer[10] = {0};
 char buffer2[10] = {0};
 uint32_t numberp01P1 =  11;
 
/**********************Buttons**********************************************
 ********************************************************************
void b1P0PopCallback(void *ptr){
  //dbSerialPrintln("buttonNextPushCallback");
  if(true){Pflag1=1;}
  page1.show();  
  
  uint32_t Humidity_Gauge = int((Humidity*180)/100);//conversion to gauge scale
  uint32_t Temp_PBar = int((Temperature*100)/60);//conversion to progress bar scale
  uint32_t picg_p0P1 = 11;
  uint32_t picr_p0P1 = 12;

  if(Temperature < 50){
    setpic_p0P1.setPic(picg_p0P1);
    }else{setpic_p0P1.setPic(picr_p0P1);}

  setprogbar_j0P1.setValue(Temp_PBar);
  setgauge_z0P1.setValue(Humidity_Gauge); 
  
}

void b0P0PopCallback(void *ptr){//button
  //dbSerialPrintln("buttonNextPushCallback");
  page4.show();  
}

void b0P1PopCallback(void *ptr){//button
  //dbSerialPrintln("buttonNextPushCallback");
  page0.show();  
}

void b1P1PopCallback(void *ptr){//button
  //dbSerialPrintln("buttonNextPushCallback");
  page2.show();  
  uint32_t picg_p0P2 = 11;
  uint32_t picr_p0P2 = 12;
  
  if(Innun == 0){
    setinnun_t0P2.setText("Seco");
    setpic_p0P2.setPic(picg_p0P2);
    
    }else{
      setinnun_t0P2.setText("Mojado");
      setpic_p0P2.setPic(picr_p0P2);
      }  
}

void b0P2PopCallback(void *ptr){//button
  //dbSerialPrintln("buttonNextPushCallback");
  if(true){Pflag1=1;}
  page1.show();  
  
  uint32_t Humidity_Gauge = int((Humidity*180)/100);//conversion to gauge scale
  uint32_t Temp_PBar = int((Temperature*100)/60);//conversion to progress bar scale
  uint32_t picg_p0P1 = 11;
  uint32_t picr_p0P1 = 12;

  if(Temperature < 50){
    setpic_p0P1.setPic(picg_p0P1);
    }else{setpic_p0P1.setPic(picr_p0P1);}

  setprogbar_j0P1.setValue(Temp_PBar);
  setgauge_z0P1.setValue(Humidity_Gauge); 
  
}

void b1P2PopCallback(void *ptr){//button
  //dbSerialPrintln("buttonNextPushCallback");
  if(true){Pflag3=1;}
  page3.show(); 
  uint32_t picBatg_p0P3 = 1; //battery images
  uint32_t picBaty_p0P3 = 2; 
  uint32_t picBato_p0P3 = 3; 
  uint32_t picBatr_p0P3 = 4; 
  
  if(ShuntVoltage >= 4.7){
    setBatpic_p0P3.setPic(picBatg_p0P3);
    }
  if(ShuntVoltage < 4.7 && ShuntVoltage >= 4.4){
    setBatpic_p0P3.setPic(picBaty_p0P3);
    }
  if(ShuntVoltage < 4.5 && ShuntVoltage >=4.1){
    setBatpic_p0P3.setPic(picBato_p0P3);
    } 
  if(ShuntVoltage<4.1){
    setBatpic_p0P3.setPic(picBatr_p0P3);
    }  
  for (int i = 0; i < 2 ; i++){
      TcPlot(TC1);
      TcPlot(TC2);
      TcPlot(TC3);
      TcPlot(TC4);
      TcPlot(TC5);
      TcPlot(TC6);
      TcPlot(TC7);
      TcPlot(TC8);
      TcPlot(TC9);
      }
}

void b0P3PopCallback(void *ptr){//button
  //dbSerialPrintln("buttonNextPushCallback");
  page2.show();  
  uint32_t picg_p0P2 = 11;
  uint32_t picr_p0P2 = 12;
  
  if(Innun == 0){
    setinnun_t0P2.setText("Seco");
    setpic_p0P2.setPic(picg_p0P2);
    
    }else{
      setinnun_t0P2.setText("Mojado");
      setpic_p0P2.setPic(picr_p0P2);
      }
}

void b1P3PopCallback(void *ptr){//button
  //dbSerialPrintln("buttonNextPushCallback");
  page4.show();  
}

void b0P4PopCallback(void *ptr){//button
  //dbSerialPrintln("buttonNextPushCallback");
  if(true){Pflag3=1;}
  page3.show(); 
  uint32_t picBatg_p0P3 = 1; //battery images
  uint32_t picBaty_p0P3 = 2; 
  uint32_t picBato_p0P3 = 3; 
  uint32_t picBatr_p0P3 = 4; 
  
  if(ShuntVoltage >= 4.7){
    setBatpic_p0P3.setPic(picBatg_p0P3);
    }
  if(ShuntVoltage < 4.7 && ShuntVoltage >= 4.4){
    setBatpic_p0P3.setPic(picBaty_p0P3);
    }
  if(ShuntVoltage < 4.5 && ShuntVoltage >=4.1){
    setBatpic_p0P3.setPic(picBato_p0P3);
    } 
  if(ShuntVoltage<4.1){
    setBatpic_p0P3.setPic(picBatr_p0P3);
    }
  for (int i = 0; i < 2 ; i++){
      TcPlot(TC1);
      TcPlot(TC2);
      TcPlot(TC3);
      TcPlot(TC4);
      TcPlot(TC5);
      TcPlot(TC6);
      TcPlot(TC7);
      TcPlot(TC8);
      TcPlot(TC9);
      }
  
}

void b1P4PopCallback(void *ptr){//button
  //dbSerialPrintln("buttonNextPushCallback");
  page0.show();  
}

void SetTemperature(){//send temperature float to string value
  String floatToString( float,int=6,int=2,boolean=false);
  Temperature_Str = floatToString(Temperature,6);
  String command = "t2P1.txt=\""+Temperature_Str+"\"";
  Serial2.print(command);
  endNextionCommand();
  }
  
void SetHumidity(){//send float to string value
  String floatToString( float,int=6,int=2,boolean=false);
  Humidity_Str = floatToString(Humidity,6);
  String command = "t3P1.txt=\""+Humidity_Str+"\"";
  Serial2.print(command);
  endNextionCommand();
  }

void SetVoltage(){//send Voltage float to string value
  String floatToString( float,int=4,int=2,boolean=false);
  ShuntVoltage_Str = floatToString(ShuntVoltage,4);
  String command = "t3P3.txt=\""+ShuntVoltage_Str+"\"";
  Serial2.print(command);
  endNextionCommand();
  }

void SetCurrent(){//send Current float to string value
  String floatToString( float,int=4,int=2,boolean=false);
  CurrentmaInt_Str = floatToString(CurrentmaInt,4);
  String command = "t4P3.txt=\""+CurrentmaInt_Str+"\"";
  Serial2.print(command);
  endNextionCommand();
  }

void SetPower(){//send temperature float to string value
  String floatToString( float,int=4,int=2,boolean=false);
  Power_Str = floatToString(Power,4);
  String command = "t5P3.txt=\""+Power_Str+"\"";
  Serial2.print(command);
  endNextionCommand();
  }
  
void setpic_p1P2PopCallback(void *ptr){//picture that defines the speaker state
  //dbSerialPrintln("buttonNextPushCallback");
  uint32_t picoff_p1P2 = 0;
  
  setpic_p1P2.getPic(&picoff_p1P2);
  
  if(picoff_p1P2==13){
    dbSerialPrintln(picoff_p1P2);
    picoff_p1P2=14;
    }else{
      picoff_p1P2=13;
      }
  setpic_p1P2.setPic(picoff_p1P2);
  
}

void TcPlot(int val){//this is only for one channel TC value (val)
  /*String InttToString( int,int=3,int=0,boolean=false);
  String TC_Str ="";
  TC_Str = String(val);
  *
  String command = "add ";
  command += 16;
  command += ",";
  command += 0;
  command += ",";
  command += val; 
  Serial2.print(command);
  endNextionCommand(); 
  }


void Irms(){
  int Iint = 0;//integral
  float AspectRatio = 40/1;
  float CTC = 0;
  int N=0;
  float Resistor = 0.1;
  while(N<13){
    float VTC = float(list2[N])*(1.1/1023);
    CTC = (VTC/Resistor)*(AspectRatio);
    Iint = Iint + sq(CTC);
    N=N+1;
    }
  Iint = Iint*2; 
  CTC = sqrt((Iint)/N);
    
  }

String floatToString( float n, int l, int d, boolean z){//converts floar to string
  char c[l+1];
  String s;
  dtostrf(n,l,d,c);
  s=String(c);
  return s;
}

void endNextionCommand(){//clean buffers in the nextion 
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
}
