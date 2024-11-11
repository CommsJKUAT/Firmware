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
  
  //if (millis() - lastTransmissionCheck >= 5000) {
  //  lastTransmissionCheck = millis();
  //  if (downlink.available()) {
  //    delay(50);
  //    String command = downlink.readStringUntil('~');
  //    command.remove(0,8);
  //    Serial.println(command);
  //    downlink.println("received~");
  //  }
  //   }
    if (millis() - lastcommandsignal >= 1000)
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
