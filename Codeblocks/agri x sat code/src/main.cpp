#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial downlink(12, 13);  // RX, TX for downlink
SoftwareSerial OBCComms(10, 11);  // RX, TX for OBCComms

const int commandready = 19;// input from obc
const int transmitready = 18;// input from obc
const int downlinkready = 2;
const int commandstatus = 4; // output to interrupt

void setup() {
  
  Serial.begin(9600);
  downlink.begin(9600);
  

  pinMode(commandready, INPUT_PULLUP);
  pinMode(transmitready, INPUT_PULLUP);
  pinMode(downlinkready, OUTPUT);
  pinMode(commandstatus, OUTPUT);

  Serial.println("Setup complete");
  digitalWrite(commandstatus,LOW);

}

void loop() {
  static unsigned long lastTransmissionCheck = 0;
  static unsigned long lastcommandsignal = 0;

 
    if (millis() - lastTransmissionCheck >= 1000){
      int sat=digitalRead(commandready);
      Serial.println(sat);

    }
    if (millis() - lastcommandsignal >= 5000)
    {
      while(downlink.available()){

        String message=downlink.readStringUntil('~');
        
        if (message.startsWith("Cm"))
        {
          digitalWrite(commandstatus,HIGH);
          message.remove(0,3);
          Serial.println(message);
        }
        
      }
    }
    
  
}
