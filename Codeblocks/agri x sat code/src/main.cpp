#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial downlink(12, 13);  // RX, TX for downlink
SoftwareSerial OBCComms(10, 11);  // RX, TX for OBCComms

const int commandready = 5;
const int transmitready = 21;
const int downlinkready = 2;
const int commandstatus = 4;

void setup() {
  
  Serial.begin(9600);
  downlink.begin(9600);
  

  pinMode(commandready, INPUT_PULLUP);
  pinMode(transmitready, INPUT_PULLUP);
  pinMode(downlinkready, OUTPUT);
  pinMode(commandstatus, OUTPUT);

  Serial.println("Setup complete");
}

void loop() {
  static unsigned long lastTransmissionCheck = 0;
  if (millis() - lastTransmissionCheck >= 5000) {
    lastTransmissionCheck = millis();
    if (downlink.available()) {
      delay(50);
      String command = downlink.readStringUntil('~');
      command.remove(0,8);
      Serial.println(command);
      downlink.println("received~");
    }
      }
  //deliverables
  //rx tx with obc
  // receiving data from obc
  static unsigned long lastCommandCheck = 0;

  //
  //  
//
  //  if (digitalRead(transmitready) == HIGH) {
  //    digitalWrite(downlinkready, HIGH);
  //    delay(3000);
//
  //    OBCComms.begin(9600);
  //    if (OBCComms.available()) {
  //      String message = OBCComms.readStringUntil('~');
  //      Serial.print("Message from OBCComms: ");
  //      Serial.println(message);
  //      OBCComms.end();
//
  //      downlink.begin(9600);
  //      downlink.println(message);
  //      downlink.end();
  //      Serial.println("Message sent to downlink");
  //    }
  //    digitalWrite(downlinkready, LOW);
  //  }
  //}

 // if (millis() - lastCommandCheck >= 1000) {
 //   lastCommandCheck = millis();
 //   Serial.println("running");
 //   downlink.begin(9600);
 //   if (downlink.available()) {
 //     delay(50);
 //     String command = downlink.readStringUntil('~');
 //     downlink.end();
//
 //     if (command == "command") {
 //       digitalWrite(commandstatus, HIGH);
 //       Serial.println("Command received: " + command);
//
 //       //OBCComms.begin(9600);
 //       //OBCComms.println("command~");
 //       //delay(2000);
 //       //OBCComms.end();
//
 //       if (digitalRead(commandready) == HIGH) {
 //         downlink.begin(9600);
 //         if (downlink.available()) {
 //           String newCommand = downlink.readStringUntil('~');
 //           downlink.end();
//
 //           //OBCComms.begin(9600);
 //           //OBCComms.println(newCommand);
 //           //OBCComms.end();
 //           Serial.println("New command sent to OBCComms");
 //         }
 //       }
 //     } else {
 //       digitalWrite(commandstatus, LOW);
 //     }
 //   }
 // }
}
