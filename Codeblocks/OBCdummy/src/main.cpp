#include <Arduino.h>

int status1 = 5;
int status2 =18;
int commandpin=4;
volatile bool commandAvailable = false;

void IRAM_ATTR handleCommandpin() {
  Serial.println("Ready to process command");
  commandAvailable = true;  
  
}
void setup() {
  Serial.begin(9600);
  pinMode(status1,OUTPUT);
  pinMode(status2,OUTPUT);
  pinMode(commandpin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(commandpin), handleCommandpin, RISING);
}


void modeNormal(){
  int data=digitalRead(commandpin);
  Serial.println(data);
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

