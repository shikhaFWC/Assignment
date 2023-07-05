//----------------------Skeleton Code--------------------//
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

//    Can be client or even host   //
#ifndef STASSID
#define STASSID "shikha"  // Replace with your network credentials
#define STAPSK  "1234512345"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

int Q0,Q1,Q2;
int D0,D1,D2,d1;

void OTAsetup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(5000);
    ESP.restart();
  }
  ArduinoOTA.begin();
}

void OTAloop() {
  ArduinoOTA.handle();
}

//-------------------------------------------------------//

void setup(){
  OTAsetup();

pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
pinMode(10,OUTPUT);
pinMode(9,OUTPUT);

Q0 = LOW;
Q1 = LOW;
Q2 = LOW;
}

void updateInputs(){
D0 = Q0;
D1 = Q2^Q1;
D2 = Q1^Q0;
d1 = Q2^Q0;
}
void nextState(){
D2 = (Q2 && Q0)||(Q1 && Q0);
D1 = (!Q2 && Q0)||(Q1 && !Q0);
D0 = (!Q2 && !Q1)||(Q2 && Q0);
d1 = (!Q2 && Q0)||(Q1 && !Q0);
}

void loop() {
  OTAloop();
  delay(10);

digitalWrite(9,HIGH);
delay(1000);
Q0 = digitalRead(34);
Q1 = digitalRead(36);
Q2 = digitalRead(38);
D0 = (!Q2 && !Q1)||(Q2 && Q1);
D1 = (!Q2 && Q0)||(Q1 && !Q0);
D2 = (Q2 && Q0)||(Q1 && !Q0);
d1 = (!Q2 && Q0)||(Q1 && !Q0);

digitalWrite(9,LOW);
delay(1000);
digitalWrite(6,D0);
digitalWrite(7,D1);
digitalWrite(8,D2);
digitalWrite(10,d1);


nextState();
updateInputs();

}

