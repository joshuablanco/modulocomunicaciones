CurrentData Read_RMS(Rms2 readRms, Average MeasAvg , MCP331 adc){
    
    CurrentData currentdata = CurrentData(); 
    
    ////// Find Rms value Average     
    uint16_t adcVal_0;
    int cnt = 0;
    float VTC_mean = 0.0;    
    float VTC; //using
    boolean FlagNo = false;

    while(FlagNo == false){  // 500 samples
        adcVal_0 = adc.readMCP331();
        
        readRms.update(adcVal_0);
        MeasAvg.update(adcVal_0);

        cnt++;

        if(cnt >= 500) { // publish every 0.5s
            
            readRms.publish();     
            MeasAvg.publish();
            
            VTC = readRms.rmsVal;
            VTC_mean = MeasAvg.average;//change this to double to increase accuracy, probably
            
            VTC = Fit_Rms(VTC); // Fitted Value   
            cnt=0;        
            FlagNo = true;
        }
        delay(1);
    }
    

    unsigned int VTCdec = (uint16_t)((VTC - (byte)VTC) * 1000);
    byte LowByte = (VTCdec & 0x00FF);
    byte HighByte = ((VTCdec & 0xFF00) >> 8);

    currentdata.VTC_Mean = VTC_mean;
    currentdata.VTCComplete = VTC;
    currentdata.VTCint = (int)VTC;
    currentdata.VTCDecLSB = (int)LowByte;
    currentdata.VTCDecMSB = (int)HighByte;
    return currentdata;
}

float Fit_Rms(float RmsVal){
    float RmsMCP;
    float RmsMCP_Real;
    //RmsMCP_Real = 0.1653*pow(RmsVal,4)-0.4892*pow(RmsVal,3)+0.4305*pow(RmsVal,2)+0.8739*RmsVal+0.006338;
    RmsMCP_Real = -1.48*pow(RmsVal,4)+2.381*pow(RmsVal,3)-1.194*pow(RmsVal,2)+1.18*RmsVal-0.01193;  
    return RmsMCP_Real;   
}
