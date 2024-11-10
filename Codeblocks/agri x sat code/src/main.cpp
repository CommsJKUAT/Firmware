#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial downlink(12,13);
SoftwareSerial OBCComms(18,19);
int uplinkready =5;
int downlinkready =2;
int commandstatus =4;
int indicator1=0;


void setup() {
  Serial.begin(9600);
  //downlink.begin(9600);
  //downlink.println();
  pinMode(uplinkready,INPUT_PULLUP);
  pinMode(downlinkready,OUTPUT);
  pinMode(commandstatus,OUTPUT);
}


void loop() {
  if(millis()>=2000){
    indicator1=millis();
    digitalWrite(downlinkready,HIGH);
    delay(3000);
    OBCComms.begin(9600);
    String message=OBCComms.readStringUntil('~');
    OBCComms.end();
    delay(50);
    downlink.begin(9600);
    downlink.println(message);
    downlink.end();

  }

}


