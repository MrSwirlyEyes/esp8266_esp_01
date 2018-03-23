#include <SoftwareSerial.h>

#define rxPin 3
#define txPin 2

SoftwareSerial ESP8266 (rxPin, txPin);

const String server = "api.openweathermap.org";
    const String request_method = "GET";
    const String route = "/data/2.5/weather?id=2643390&appid=5d7171bef3c4d2055fcff9885bb2cf66";

unsigned long lastTimeMillis = 0;

void setup() {
  Serial.begin(9600);
  delay(500);
  ESP8266.begin(115200);
  delay(1000);
  Serial.println("Changing baud rate");
  ESP8266.println("AT+IPR=9600");
  delay(1000);
  ESP8266.begin(9600);
  delay(2000);
//  Serial.println("");
  Serial.println("\nRemember to set Both NL & CR in the serial monitor.");
  Serial.println("Ready\n\nStarting application");
//  Serial.println("");
//  Serial.println("Starting application");
}

void loop() {

  if (millis() - lastTimeMillis > 30000) {
    lastTimeMillis = millis();

    ESP8266.println("AT+CIPMUX=1");
    delay(1000);
    printResponse();    

    ESP8266.println("AT+CIPSTART=4,\"TCP\",\"" + server + "\",80");
    delay(1000);
    printResponse();    
    
    String cmd = request_method + " " + route + " HTTP/1.1\r\nHost:" + server + "\r\n\r\n";
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

void printResponse() {
  while (ESP8266.available()) {
    Serial.println(ESP8266.readStringUntil('\n')); 
  }
}
