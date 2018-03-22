#include <SoftwareSerial.h>

const byte rxPin = 3;
const byte txPin = 2;

SoftwareSerial ESP8266 (rxPin, txPin);

unsigned long lastTimeMillis = 0;

void setup() {
  Serial.begin(9600);   
  ESP8266.begin(115200);
  delay(1000);
  Serial.println("Changing baud rate");
  ESP8266.println("AT+IPR=9600");
  delay(1000);
  ESP8266.begin(9600);
  delay(2000);
}

void printResponse() {
  while (ESP8266.available()) {
    Serial.println(ESP8266.readStringUntil('\n')); 
  }
}

void loop() {

  if (millis() - lastTimeMillis > 30000) {
    lastTimeMillis = millis();

    ESP8266.println("AT+CIPMUX=1");
    delay(1000);
    printResponse();

    ESP8266.println("AT+CIPSTART=4,\"TCP\",\"api.openweathermap.org\",80");
    delay(1000);
    printResponse();

    String cmd = "GET /data/2.5/weather?id=2643390&appid=5d7171bef3c4d2055fcff9885bb2cf66 HTTP/1.1\r\nHost:api.openweathermap.org\r\n\r\n";
//    String cmd = "GET /data/2.5/weather?id=2643390&appid=5d7171bef3c4d2055fcff9885bb2cf66 HTTP/1.1\r\nHost: api.openweathermap.org\r\nConnection: close\r\n\r\n";
    ESP8266.println("AT+CIPSEND=4," + String(cmd.length() + 4));
    delay(1000);

    ESP8266.println(cmd);
    delay(1000);
    ESP8266.println(""); 
  }

  if (ESP8266.available()) {
//    Serial.println(ESP8266.readStringUntil('\r'));
    Serial.write(ESP8266.read());
  }
}