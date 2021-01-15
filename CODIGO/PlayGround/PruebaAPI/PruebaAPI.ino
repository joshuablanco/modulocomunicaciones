#include <XBee.h>
//#include <SoftwareSerial.h>

/* 
 * En este programa se busca recibir una trama e intentar 
 * separar de la forma mas sencilla los campos del router
 * 
 */

//entero fijo 2 bytes son los pines del softserial
uint8_t recv = 2;
uint8_t trans = 3;
//se inicializa el puerto 
//SoftwareSerial soft_serial(recv,trans);

//inicializa libreria xbee
XBee xbee = XBee();
ZBRxResponse rx = ZBRxResponse();
XBeeResponse response = XBeeResponse();

int statusLed = 13;
int errorLed = 13;
int dataLed = 13;

void setup() {
  Serial.begin(9600);  
  Serial2.begin(9600);
  Serial.println("Init...");
  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  pinMode(dataLed,  OUTPUT);
  xbee.setSerial(Serial2);
  
}

void loop() {
  xbee.readPacket();
  if(xbee.getResponse().isAvailable()){

    if(xbee.getResponse().getApiId() == ZB_RX_RESPONSE){
      
      xbee.getResponse().getZBRxResponse(rx);
      
      if(rx.getOption()== ZB_PACKET_ACKNOWLEDGED){
        Serial.println("Recibio un Acknowledge.");  
        
        }
      else{
        Serial.println("Recibio algo raro NO ACKNOWLEDGE");
        } 

        Serial.print("CheckSum: ");
        Serial.println(rx.getChecksum(),HEX);
        Serial.print("Packet length: ");
        Serial.println(rx.getPacketLength(),HEX);   
        
        for(int i=0; i < rx.getDataLength(); i++){
          
          Serial.print("payload [");
          Serial.print(i,DEC);
          Serial.print("] is ");
          Serial.println(rx.getData()[i],DEC);
          }    
        for(int i=0; i < xbee.getResponse().getFrameDataLength();i++){
          Serial.print("frame data [");
          Serial.print(i, HEX);
          Serial.print("] is ");
          Serial.println(xbee.getResponse().getFrameData()[i], HEX);
          }    
      }
      else if(xbee.getResponse().isError()){
        Serial.print("Error reading Packet, Error code: ");
        Serial.println(xbee.getResponse().getErrorCode());
        }
    
    }
  
  
}

void get_address(ZBRxIoSampleResponse *ioSample){
  Serial.print("Received data from adress : ");
  Serial.println(ioSample-> getRemoteAddress64().getMsb(),HEX);
  Serial.print(ioSample -> getRemoteAddress64().getLsb(),HEX);
  Serial.println(" ");  
  }
  
void get_temperature(ZBRxIoSampleResponse *ioSample){
  float adc_data = ioSample->getAnalog(3);
  Serial.print("Temperature is : ");
  float temperatureC = ((adc_data * 1200.0 / 1024.0) - 500.0) / 10.0;
  Serial.print(temperatureC);
  Serial.println(" C ");
  }

void get_supply_voltage(){
  Serial.print("Supply voltage is: ");
  int ref = xbee.getResponse().getFrameData()[17] << 8;
  ref += xbee.getResponse().getFrameData()[18];
  float volts = (float(ref)* float(1200.0/1024))/1000.0;
  Serial.print(" = ");  
  Serial.print(volts);
  Serial.println(" V ");
  }
  
