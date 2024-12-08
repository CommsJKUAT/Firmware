#include <Arduino.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>

#define comms_rx 5
#define comms_tx 21

SoftwareSerial downlink(12, 13);  // RX, TX for downlink
HardwareSerial OBCComms(1);       // RX, TX for OBCComms

const int commandready = 19;  // Input from OBC
const int transmitready = 18; // Input from OBC
const int downlinkready = 2;
const int commandstatus = 4;  // Output to interrupt

bool normal = false;
bool initialisation = false;
bool critical = false;

void setup() {
  Serial.begin(115200);            // Debugging port
  downlink.begin(115200);            // Downlink communication
  OBCComms.begin(115200, SERIAL_8N1, 5, 21);  // UART setup for OBCComms

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

  int sat1 = digitalRead(commandready);
  int sat2 = digitalRead(transmitready);

 
  if (millis() - lastTransmissionCheck >= 1000) {
    
    Serial.println(sat1);
    Serial.println(sat2);
    lastTransmissionCheck = millis();  
  }
  if (sat1==1 and sat2==1)
  {
    downlink.println("NM~");
  }
  if (sat1==1 and sat2==0)
  {
    while (sat2==0)
    {
      String dataOBC=OBCComms.readStringUntil('}');
      sat2=digitalRead(transmitready);
    }
    
  }
  if (sat1==0 and sat2==1)
  {
    downlink.println("CM~");
  }
  if (sat1==0 and sat2==0)
  {
    while (sat2==0)
    {
      String dataOBC=OBCComms.readStringUntil('}');
      sat2=digitalRead(transmitready);
    }
  }

  
}
