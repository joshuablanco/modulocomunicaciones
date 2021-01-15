#include <MCP3202.h>
MCP3202 adc = MCP3202(10);

int channel1 = 0;
int channel2 = 0;
const int Sensor = A2;
int buttonPin = 3;
int buttonState = 0;       
int a[400];
double chan;
double chan2 = 0;
double VTC = 0;
double V_acc = 0;
/// anadimos un comentario 
void setup() {
  // put your setup code here, to run once:
  adc.begin();
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  //analogReference(EXTERNAL);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("**************************************************************");
  V_acc = 0;
  VTC = 0;
  chan2 = 0;
  //channel1 = adc.readChannel(0);
  channel2 = analogRead(Sensor);

  for (int i=0; i<400; i++){
    //channel1 = adc.readChannel(0);
    channel2 = analogRead(Sensor);
    a[i]=channel2;
    //buttonState = digitalRead(buttonPin);
    //Serial.print(channel1+25);Serial.print(",");Serial.print(channel2*4+15);Serial.print(",");Serial.println(buttonState*2400);
    //Serial.println(channel2);
    //chan = float (channel1) * 5.06 / 4095;
    //chan2 = chan / 0.180;
    //Serial.println(chan);
    //V_acc = V_acc + (sq(chan2));   
    delay(50);
    } 
  for (int i=0; i<400; i++){
    Serial.println(a[i]);
    delay(1);
  }
  //Serial.print("channel1: ");Serial.println(channel1*5/4095);//Serial.println(channel2*4);
  //Serial.print("channel2: ");Serial.println(channel2*4.8/1023);
  //Serial.println("***********************************************************************");
  //VTC = (sqrt(V_acc/ 500));
  //Serial.println(VTC);
  
  delay(50);
  Serial.println("**************************************************************");
  //Serial.print("\t");
  //Serial.println(channel1-(-channel2*4));
  //Serial.print(channel1);Serial.print(",");Serial.println(channel2*4);
}
