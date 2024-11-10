#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial downlink(12,13);
int uplinkready =5;
int downlinkready =2;



void setup() {
  Serial.begin(9600);
  downlink.begin(9600);
  downlink.println();
  pinMode();
  pinMode();
}


void loop() {
  

}

