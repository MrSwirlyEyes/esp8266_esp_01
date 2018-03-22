#include "SoftwareSerial.h"

SoftwareSerial ESP8266(3, 2);// RX, TX

String server = "api.openweathermap.org"; // np. www.examble.pl albo adres ip 129.75.1.32

void setup() 
{
  ESP8266.begin(115200); //odpowiednia prędkość dla twojego modułu
  Serial.begin(115200);
  Serial.print("Start");
  delay(2000);
//  reset();
  ESP8266.println("AT+CWMODE=1");
  delay("1000");
  ESP8266.println("AT+CIPMUX=1");
  delay("1000");
  
  connectWifi();
}

void loop()
{
  String cmd;
  cmd = "AT+CIPSTART=1,\"TCP\",\"";
  delay(500);
  cmd += server;
  delay(500);
  cmd += "\",80";
  delay(500);
  ESP8266.println(cmd); 
  delay(500);
  
  if(ESP8266.find("OK")) 
  {
    Serial.println("Connected to the web!");
  }
  
  float weight = 257;
  bool state = 1;
  cmd =  "GET /data/2.5/weather?id=2643390&appid=5d7171bef3c4d2055fcff9885bb2cf66 HTTP/1.1\r\n";  
  delay(500);
  cmd += "Host:api.openweathermap.org\r\n\r\n"; 
  delay(500);  
  ESP8266.print("AT+CIPSEND=1,");
  delay(500);
  ESP8266.println(cmd.length());  
  delay(500);
  
  if(ESP8266.find(">")) 
  {
    Serial.println(">");
  }
  
  ESP8266.println(cmd);
  delay(500);
  
  if(ESP8266.find("OK")) 
  {
    Serial.println("send!");
    
    delay(2000);
    while (ESP8266.available()) {
      Serial.write(ESP8266.read());
    }
  }
  delay(30000);
}

void connectWifi() 
{

  String cmd = "AT+CWJAP=\"Swirly24\",\"\"";
  ESP8266.println(cmd);
  delay(4000);
  
  if(ESP8266.find("OK")) 
  {
    Serial.println("Connected!");
  }else{
    Serial.println("Cannot connect to wifi"); 
    connectWifi();
  }
}

void reset()
{
  ESP8266.println("AT+RST");
  delay(1000);
  if(ESP8266.find("OK")) Serial.println("Module Reset");
}


void printResponse() {
  while (ESP8266.available()) {
    Serial.println(ESP8266.readStringUntil('\n')); 
//    byte var[773];
//    Serial.println(ESP8266.readBytes(var,773)); 
//    
//    Serial.println();
//    for(int i = 0 ; i < 773 ; i++) {
//      Serial.print((char) var[i]);
//    }
  }
}