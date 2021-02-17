/*void requestURL(const char * host, uint8_t port)
{
  printLine();
  Serial.println("Connecting to domain: " + String(host));
  WiFiClient client;
  if (!client.connect(host, port))
  {
    Serial.println("connection failed");
    return;
  }
  Serial.println("Connected!");
  printLine();
  //String url = "/input/zD78yJxmNNcMMr8vzj6g?private_key=YymkKRXP22UbbkjBEwdA&var=";
  String url = "/ecoenergy-webapp/savevalue";
  //url += Temperature;
  //String("POST ") + url + " HTTP/1.1\r\n" +  "Host: 192.168.0.33\r\n" + "Connection: close\r\n\r\n"
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "User-Agent: ESP32\r\n" + "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) 
  {
    if (millis() - timeout > 5000) 
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }  
  while (client.available()) 
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");
  client.stop();
}

void printLine()
{
  Serial.println();
  for (int i=0; i<30; i++)
    Serial.print("-");
  Serial.println();
}

void connectToWiFi(const char * ssid, const char * pwd)
{
  int ledState = 0;
  printLine();
  Serial.println("Connecting to WiFi network: " + String(ssid));
  WiFi.begin(ssid, pwd);

  while (WiFi.status() != WL_CONNECTED) 
  {
    digitalWrite(LED_PIN, ledState);
    ledState = (ledState + 1) % 2; 
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected!");
  
("IP address: ");
  Serial.println(WiFi.localIP());
}*/

/**** Ubidots ****/
//void callback(char* topic, byte* payload, unsigned int length) {
//  char p[length + 1];
//  memcpy(p, payload, length);
//  p[length] = NULL;
//  String message(p);
//  Serial.write(payload, length);
//  //Serial.println(topic);
//}
//
//void reconnect() {
//  // Loop until we're reconnected
//  Reconnect=0;
//  while (!client.connected() && Reconnect < 3 ) {
//    //
//    //Serial.println("Attempting MQTT connection...");
//    
//    // Attemp to connect
//    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
//      //Serial.println("Connected");
//    } else {
//      Serial.print("Failed, rc=");
//      Serial.print(client.state());
//      Serial.println(" try again in 2 seconds");
//      delay(2000);
//    }
//    Reconnect = Reconnect+1;
//  }
//}

//void Ubiupload(){
//  if (!client.connected()) {
//    reconnect();
//  }
//
//  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
//  sprintf(payload0, "%s", ""); // Cleans the payload
//  sprintf(payload0, "{\"%s\":", VARIABLE_LABEL0); // Adds the variable label
//  sprintf(payload1, "%s", ""); // Cleans the payload
//  sprintf(payload1, "{\"%s\":", VARIABLE_LABEL1); // Adds the variable label
//  sprintf(payload2, "%s", ""); // Cleans the payload
//  sprintf(payload2, "{\"%s\":", VARIABLE_LABEL2); // Adds the variable label
//  sprintf(payload3, "%s", ""); // Cleans the payload
//  sprintf(payload3, "{\"%s\":", VARIABLE_LABEL3); // Adds the variable label
//  sprintf(payload4, "%s", ""); // Cleans the payload
//  sprintf(payload4, "{\"%s\":", VARIABLE_LABEL4); // Adds the variable label
//  sprintf(payload5, "%s", ""); // Cleans the payload
//  sprintf(payload5, "{\"%s\":", VARIABLE_LABEL5); // Adds the variable label
//  //4 is mininum width, 2 is precision; float value is copied onto str_sensor
//  dtostrf(Temperature, 4, 2, Temperature2_Str);
//  dtostrf(Humidity, 4, 2, Humidity1_Str);
//  dtostrf(ShuntVoltage, 4, 2, Voltage1_Str );
//  dtostrf(CurrentmaInt, 4, 2, Current1_Str );
//  dtostrf(CTC, 4, 2, CTC1_Str );
//  dtostrf(Innun, 4, 2, Innun_Str );
//  
//  sprintf(payload0, "%s {\"value\": %s}}", payload0, Temperature2_Str); // Adds the value
//  sprintf(payload1, "%s {\"value\": %s}}", payload1, Humidity1_Str ); // Adds the   
//  sprintf(payload2, "%s {\"value\": %s}}", payload2, Voltage1_Str ); // Adds the  
//  sprintf(payload3, "%s {\"value\": %s}}", payload3, Current1_Str ); // Adds the 
//  sprintf(payload4, "%s {\"value\": %s}}", payload4, CTC1_Str ); // Adds the
//  sprintf(payload5, "%s {\"value\": %s}}", payload5, Innun_Str ); // Adds the
//  
//  client.publish(topic, payload0); 
//  client.publish(topic, payload1);
//  delay(1000);
//  client.publish(topic, payload2);  
//  client.publish(topic, payload3);
//  delay(1000);
//  client.publish(topic, payload4);
//  client.publish(topic, payload5);
//  Serial.println("Publishing data to Ubidots Cloud");
//  client.loop();
//  delay(1000);
//  }
  
