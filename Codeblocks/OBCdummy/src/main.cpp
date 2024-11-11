#include <Arduino.h>

int status1 = 5;
int status2 =18;
void setup() {
  pinMode(status1,OUTPUT);
  pinMode(status2,OUTPUT);
}


void modeNormal(){
  digitalWrite(status1,LOW);
  digitalWrite(status2,LOW);
}
void modeidle(){
  digitalWrite(status1,LOW);
  digitalWrite(status2,LOW);
}
void modeSafe(){
  digitalWrite(status1,LOW);
  digitalWrite(status2,LOW);
}
void modeEmergency(){
  digitalWrite(status1,HIGH);
  digitalWrite(status2,HIGH);
}
void loop() {
  modeNormal();
}

