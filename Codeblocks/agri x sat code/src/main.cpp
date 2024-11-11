#include <Arduino.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
#define comms_rx 5
#define comms_tx  21

SoftwareSerial downlink(12, 13);  // RX, TX for downlink
HardwareSerial OBCComms(1);  // RX, TX for OBCComms

const int commandready = 19;  // Input from OBC
const int transmitready = 18; // Input from OBC
const int downlinkready = 2;
const int commandstatus = 4;  // Output to interrupt

int sat1 = 1;
int sat2 = 1;

bool normal = false;
bool initialisation = false;
bool critical = false;

void setup() {
  Serial.begin(9600);
  downlink.begin(9600);

  pinMode(commandready, INPUT_PULLUP);
  pinMode(transmitready, INPUT_PULLUP);
  pinMode(downlinkready, OUTPUT);
  pinMode(commandstatus, OUTPUT);

  Serial.println("Setup complete");
  digitalWrite(commandstatus, LOW);
}

void loop() {
  static unsigned long lastTransmissionCheck = 0;
  static unsigned long lastCommandSignal = 0;

  // Check every 1000 ms if we should update `sat1` and `sat2`
  if (millis() - lastTransmissionCheck >= 1000) {
    sat1 = digitalRead(commandready);
    sat2 = digitalRead(transmitready);
    Serial.println(sat1);
    Serial.println(sat2);
    lastTransmissionCheck = millis();  // Update the timestamp
  }

  // Initialization mode
  if (sat1 == 0 && sat2 == 0) {
    downlink.println("INM~");
    initialisation = true;
    while (initialisation) {
      String message = Serial.readStringUntil('~');
      downlink.println("INM~");  // Repeat mode indicator

      // Read the updated state directly from `commandready` and `transmitready`
      int in1 = digitalRead(commandready);
      int in2 = digitalRead(transmitready);
      if (in1 != 0 || in2 != 0) {
        initialisation = false;  // Exit initialization mode
      }
    }
  }

  // Normal mode
  if (sat1 == 0 && sat2 == 1) {
    downlink.println("NM~");
    normal = true;
    while (normal) {
      String message = Serial.readStringUntil('~');
      downlink.println(message);  // Send received message
      delay(3000);  // Delay for 3 seconds between transmissions

      // Check if we should exit the normal mode
      int nm1 = digitalRead(commandready);
      int nm2 = digitalRead(transmitready);
      Serial.println(nm1);
      Serial.println(nm2);
      String meso=OBCComms.readStringUntil('}');
      Serial.println(meso);
      if (nm1 != 0 || nm2 != 1) {
        normal = false;  // Exit normal mode
      }
    }
  }

  // Critical mode
  if (sat1 == 1 && sat2 == 0) {
    downlink.println("CTM~");
    critical = true;
    while (critical) {
      String message = Serial.readStringUntil('~');

      // Check if we should exit the critical mode
      int ct1 = digitalRead(commandready);
      int ct2 = digitalRead(transmitready);
      if (ct1 != 1 || ct2 != 0) {
        critical = false;  // Exit critical mode
      }
    }
  }

  // Command signal check every 5000 ms
  if (millis() - lastCommandSignal >= 5000) {
    lastCommandSignal = millis();  // Update the timestamp

    while (downlink.available()) {
      String message = downlink.readStringUntil('~');

      if (message.startsWith("Cm")) {
        digitalWrite(commandstatus, HIGH);  // Trigger command status
        message.remove(0, 3);               // Remove "Cm" prefix
        Serial.println(message);            // Print the command
      }
    }
  }
}
