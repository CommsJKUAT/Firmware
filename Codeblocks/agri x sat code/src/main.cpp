#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial downlink(12, 13);
SoftwareSerial OBCComms(18, 19);
int commandready = 5;
int transmitready = 21;
int downlinkready = 2;
int commandstatus = 4;
int indicator1 = 0;
int indicator2 = 0;

void setup()
{
  Serial.begin(9600);
  // downlink.begin(9600);
  // downlink.println();
  pinMode(commandready, INPUT_PULLUP);
  pinMode(transmitready, INPUT_PULLUP);
  pinMode(downlinkready, OUTPUT);
  pinMode(commandstatus, OUTPUT);
}

void loop()
{
  if (millis() >= 5000)
  {
    indicator1 = millis();
    int transmitstatus = digitalRead(transmitready);
    if (transmitstatus == 1)
    {
      digitalWrite(downlinkready, HIGH);
      delay(3000);
      OBCComms.begin(9600);
      String message = OBCComms.readStringUntil('~');
      OBCComms.end();
      delay(50);
      downlink.begin(9600);
      delay(50);
      downlink.println(message);
      downlink.end();
    }
  }
  if (millis() >= 1000)
  {
    indicator2 = millis();
    downlink.begin(9600);
    delay(50);
    String command = downlink.readStringUntil('~');
    if (command == "command")
    {
      digitalWrite(commandstatus, HIGH);

      downlink.end();
      OBCComms.begin(9600);
      delay(2000);
      OBCComms.println("command~");
      OBCComms.end();
      int status = digitalRead(commandready);
      if (status == 1)
      {
        downlink.begin(9600);
        delay(50);
        String command = downlink.readStringUntil('~');
        downlink.end();
        OBCComms.begin(9600);
        delay(20);
        OBCComms.println(command);
        OBCComms.end();
      }
    }
  }
}
