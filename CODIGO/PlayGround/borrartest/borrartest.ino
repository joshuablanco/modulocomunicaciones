//#include <SoftwareSerial.h>
uint8_t ssRX = 2;
// Connect Arduino pin 9 to RX of usb-serial device
uint8_t ssTX = 3;
// Remember to connect all devices to a common Ground: XBee, Arduino and USB-Serial device
//SoftwareSerial nss(ssRX, ssTX);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //nss.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    Serial.println(Serial.read(),HEX);
    
    }
}
