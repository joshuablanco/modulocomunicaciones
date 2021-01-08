#include <ListLib.h>

int Reading = 0;
List<int> list;
void setup() {
  
  Serial.begin(9600);

}

void loop() {
//  Reading = analogRead(A0);
//  Serial.println(Reading);
  for (int i = 0; i <= 100; i++)
  {
    Reading = analogRead(A0);
    delay(10);
    list.Add(Reading);
    
  }
  for (int i = 0; i <= 100; i++)
  {
    Serial.println(list[i]);
    delay(10);
  }
  
  
  
}
