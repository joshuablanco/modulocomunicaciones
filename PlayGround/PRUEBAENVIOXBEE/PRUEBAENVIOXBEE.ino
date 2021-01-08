#include <XBee.h>
#include <SoftwareSerial.h>


uint8_t rx = 2;
uint8_t tx = 3;


XBee xbee = XBee();

SoftwareSerial soft = SoftwareSerial(rx,tx);


const char HEADER = 'H';
const char TAIL = 'T';
uint8_t Tint = 26;
uint8_t Tdecimal = 32;
uint8_t Hint = 50;  
uint8_t Hdecimal = 45;
uint8_t ShuntInt = 4;
uint8_t ShuntDecimal = 8;
uint8_t Water = 1;
uint8_t SignalValues = 3;
uint8_t VTCint = 34;
uint8_t VTCDecimalMSB = 45;
uint8_t VTCDecimalLSB = 32;
uint8_t MaxCurrent = 43;
uint8_t Num_Samples = 54;
uint8_t Zero = 0; 

uint8_t payload[] = {HEADER,Tint,Tdecimal,Hint,Hdecimal,ShuntInt,ShuntDecimal,
                      Water,SignalValues,VTCint,VTCDecimalMSB,VTCDecimalLSB,
                      MaxCurrent,Num_Samples,TAIL,Zero,Zero,Zero};

XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x41553D44);
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  
  soft.begin(9600);
  xbee.setSerial(soft);
}

void loop() {
  // put your main code here, to run repeatedly:
  xbee.send(zbTx);
  delay(6000);
}
