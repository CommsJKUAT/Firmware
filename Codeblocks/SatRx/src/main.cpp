#include <Arduino.h>

#include <HTTPClient.h>
#include <WiFi.h>
#include <SoftwareSerial.h>

// Define LoRa SoftwareSerial pins
#define RX_PIN 14  // Receive pin for LoRa
#define TX_PIN 12  // Transmit pin for LoRa

// Create SoftwareSerial object for LoRa communication
SoftwareSerial mySerial(RX_PIN, TX_PIN);

// Wi-Fi credentials
const char* ssid = "Abdullahi";
const char* password = "!Ahmed1234";
const char* serverName = "https://agroxsat.onrender.com/backendapi/images/";

char jsonPayload[100];  // Buffer for received payload

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);  // Initialize SoftwareSerial for LoRa

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  Serial.println("Receiver is ready. Waiting for data...");
}

void loop() {
  // Check for incoming data on LoRa via SoftwareSerial
  if (mySerial.available()) {
    String loRaPayload = mySerial.readString();
    Serial.print("Received via LoRa: ");
    Serial.println(loRaPayload);

    // Parse and format the data
    handleData(loRaPayload);
  }

  delay(1000);  // Add a delay to avoid flooding the loop
}

// Function to parse and format the received data
void handleData(String payload) {
  // Extract temperature from the payload
  String temperature = getValue(payload, "temperature=");

  // Format data as JSON string
  String jsonToSend = String("{\"temperature\":\"") + temperature.trim() + "\"}";

  // Print the formatted JSON
  Serial.print("Formatted JSON: ");
  Serial.println(jsonToSend);

  // Send the formatted data to the API endpoint
  if (sendDataToAPI(jsonToSend)) {
    Serial.println("Data sent to API successfully.");
  } else {
    Serial.println("Failed to send data to API.");
  }
}

// Function to extract values from the incoming payload
String getValue(String data, String key) {
  int startIndex = data.indexOf(key) + key.length();
  int endIndex = data.indexOf("&", startIndex);
  if (endIndex == -1) {
    endIndex = data.length();
  }
  return data.substring(startIndex, endIndex);  // Return as String
}

// Function to send the formatted JSON to the API endpoint
bool sendDataToAPI(String jsonData) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi not connected");
        return false;
    }

    HTTPClient http;
    http.begin(serverName);  // Specify the API endpoint
    http.addHeader("Content-Type", "application/json");  // Set content-type header
    http.addHeader("Content-Length", String(jsonData.length()));  // Optional: set content length

    // Send HTTP POST request
    Serial.print("Sending JSON Data: ");
    Serial.println(jsonData);  // Log the JSON being sent

    int httpResponseCode = http.POST(jsonData);

    // Check the response code
    if (httpResponseCode > 0) {
        String response = http.getString();  // Get server response
        Serial.print("Response from server: ");
        Serial.println(response);
        http.end();  // Close connection
        return true;
    } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
        Serial.println(http.errorToString(httpResponseCode));  // Log the error string
        http.end();  // Close connection
        return false;
    }
}