/// <summary>
/// Lectura de sensores de agua, se debe especificar que puertos se deben leer
/// Si se indica un puerto que no esta conectado puede arrojar alarma
/// </summary>
/// <param name="ADC_INPUT1"></param>
/// <param name="ADC_INPUT2"></param>
/// <param name="ADC_INPUT3"></param>
/// <returns></returns>
Water WaterReads(int ADC_INPUT1, int ADC_INPUT2, int ADC_INPUT3){
    Water wateread = Water();

    uint8_t sensorValue = analogRead(ADC_INPUT1);
    delay(10);
    uint8_t sensorValue = analogRead(ADC_INPUT2);
    delay(10);
    uint8_t sensorValue = analogRead(ADC_INPUT3);
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
struct Water {
    int WaterState;
};
class WaterRead {
public:
    WaterRead(uint8_t ADC_IPUT1, uint8_t ADC_INPUT2, uint8_t ADCINPUT3);
    Water WaterReading();

};