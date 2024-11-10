#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

// Define LoRa SoftwareSerial pins
#define RX_PIN 14  // Receive pin for LoRa
#define TX_PIN 12  // Transmit pin for LoRa
#define ledgreen 6
#define ledred 7
#define buzzer 8

int indicator1=0;
int indicator2=0;
// Create SoftwareSerial object for LoRa communication
SoftwareSerial mySerial(RX_PIN, TX_PIN);


// Wi-Fi credentials
const char* ssid = "Abdullahi";
const char* password = "@Ahmed1234";
const char* serverName1 = "https://agroxsat.onrender.com/backendapi/images/";
const char* serverName2 = "https://agroxsat.onrender.com/backendapi/location/"; 
const char* serverName4 = "https://agroxsat.onrender.com/backendapi/baseStation/";
const char* serverName5 = "https://agroxsat.onrender.com/backendapi/temperature/";
const char* serverName6 = "https://agroxsat.onrender.com/backendapi/humidity/";
const char* serverName7 = "https://agroxsat.onrender.com/backendapi/soilph/";
const char* serverName8 = "https://agroxsat.onrender.com/backendapi/soilprec/";
const char* serverName9 = "https://agroxsat.onrender.com/backendapi/batt/";
const char* serverName10 = "https://agroxsat.onrender.com/backendapi/mapgs/";
const char* serverName11 = "https://agroxsat.onrender.com/backendapi/smoke/";
char jsonPayload[10000];  // Buffer for received payload

void setup() {
  Serial.begin(9600); 
  mySerial.begin(9600); 
  digitalWrite(ledgreen,LOW);
  digitalWrite(ledred,LOW);
  digitalWrite(buzzer,LOW);
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");



  Serial.println("Receiver is ready. Waiting for data...");
}
// Function to extract values from the incoming payload
String getValue(String data, String key) {
  int startIndex = data.indexOf(key) + key.length();
  int endIndex = data.indexOf("&", startIndex);
  if (endIndex == -1) {
    endIndex = data.length();
  }
  return data.substring(startIndex, endIndex); // Return substring as String
}
bool sendDatasoilphToAPI(String jsonData) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
    return false;
  }

  HTTPClient http;
  http.begin(serverName7);  // Specify the API endpoint
  http.addHeader("Content-Type", "application/json");  // Set content-type header

  // Send HTTP POST request
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
    http.end();  // Close connection
    return false;
  }
}
bool sendDatahumidityToAPI(String jsonData) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
    return false;
  }

  HTTPClient http;
  http.begin(serverName6);  // Specify the API endpoint
  http.addHeader("Content-Type", "application/json");  // Set content-type header

  // Send HTTP POST request
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
    http.end();  // Close connection
    return false;
  }
}
bool sendDataimagesToAPI(String jsonData) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
    return false;
  }

  HTTPClient http;
  http.begin(serverName1);  // Specify the API endpoint
  http.addHeader("Content-Type", "application/json");  // Set content-type header

  // Send HTTP POST request
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
    http.end();  // Close connection
    return false;
  }
}
bool sendDatalocationToAPI(String jsonData) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
    return false;
  }

  HTTPClient http;
  http.begin(serverName2);  // Specify the API endpoint
  http.addHeader("Content-Type", "application/json");  // Set content-type header

  // Send HTTP POST request
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
    http.end();  // Close connection
    return false;
  }
}
bool sendDatasmokeToAPI(String jsonData) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
    return false;
  }

  HTTPClient http;
  http.begin(serverName11);  // Specify the API endpoint
  http.addHeader("Content-Type", "application/json");  // Set content-type header

  // Send HTTP POST request
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
    http.end();  // Close connection
    return false;
  }
}

bool sendDatamapgsToAPI(String jsonData) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
    return false;
  }

  HTTPClient http;
  http.begin(serverName4);  // Specify the API endpoint
  http.addHeader("Content-Type", "application/json");  // Set content-type header

  // Send HTTP POST request
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
    http.end();  // Close connection
    return false;
  }
}
bool sendDatabattToAPI(String jsonData) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
    return false;
  }

  HTTPClient http;
  http.begin(serverName9);  // Specify the API endpoint
  http.addHeader("Content-Type", "application/json");  // Set content-type header

  // Send HTTP POST request
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
    http.end();  // Close connection
    return false;
  }
}
bool sendDatasoilprecToAPI(String jsonData) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
    return false;
  }

  HTTPClient http;
  http.begin(serverName8);  // Specify the API endpoint
  http.addHeader("Content-Type", "application/json");  // Set content-type header

  // Send HTTP POST request
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
    http.end();  // Close connection
    return false;
  }
}

bool sendDatatemperatureToAPI(String jsonData) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
    return false;
  }

  HTTPClient http;
  http.begin(serverName5);  // Specify the API endpoint
  http.addHeader("Content-Type", "application/json");  // Set content-type header

  // Send HTTP POST request
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
    http.end();  // Close connection
    return false;
  }
}
// Function to parse and format the received data
void handleimageData(String payload) {
  String image = getValue(payload, "image=");
  
  // Clean up the base64 string by removing newlines and carriage returns
  image.replace("\n", "");  // Remove newline characters
  image.replace("\r", "");  // Remove carriage return characters
  
  // Format data as JSON string
  String jsonToSend = String("{\"image\":\"") + image + "\"}";

  // Print the formatted JSON
  Serial.print("Formatted JSON: ");
  Serial.println(jsonToSend);

  // Send the formatted data to the API endpoint
  if (sendDataimagesToAPI(jsonToSend)) {
    Serial.println("Data sent to API successfully.");
  } else {
    Serial.println("Failed to send data to API.");
  }
}

void handletemperatureData(String payload) {
  String temperature = getValue(payload, "temperature=");
  
  // Clean up the base64 string by removing newlines and carriage returns
  temperature.replace("\n", "");  // Remove newline characters
  temperature.replace("\r", "");  // Remove carriage return characters
  
  // Format data as JSON string
  String jsonToSend = String("{\"temperature\":\"") + temperature + "\"}";

  // Print the formatted JSON
  Serial.print("Formatted JSON: ");
  Serial.println(jsonToSend);

  // Send the formatted data to the API endpoint
  if (sendDatatemperatureToAPI(jsonToSend)) {
    Serial.println("Temperature sent to API successfully.");
  } else {
    Serial.println("Failed to send data to API.");
  }
}
void handlelocationData(String payload) {
  String location = getValue(payload, "location=");
  
  // Clean up the base64 string by removing newlines and carriage returns
  location.replace("\n", "");  // Remove newline characters
  location.replace("\r", "");  // Remove carriage return characters
  
  // Format data as JSON string
  String jsonToSend = String("{\"location\":\"") + location + "\"}";

  // Print the formatted JSON
  Serial.print("Formatted JSON: ");
  Serial.println(jsonToSend);

  // Send the formatted data to the API endpoint
  if (sendDatalocationToAPI(jsonToSend)) {
    Serial.println("Data sent to API successfully.");
  } else {
    Serial.println("Failed to send data to API.");
  }
}
void handlesmokeData(String payload) {
  String smoke = getValue(payload, "smoke=");
  
  // Clean up the base64 string by removing newlines and carriage returns
  smoke.replace("\n", "");  // Remove newline characters
  smoke.replace("\r", "");  // Remove carriage return characters
  
  // Format data as JSON string
  String jsonToSend = String("{\"smoke\":\"") + smoke + "\"}";

  // Print the formatted JSON
  Serial.print("Formatted JSON: ");
  Serial.println(jsonToSend);

  // Send the formatted data to the API endpoint
  if (sendDatasmokeToAPI(jsonToSend)) {
    Serial.println("Data sent to API successfully.");
  } else {
    Serial.println("Failed to send data to API.");
  }
}
void handlebattData(String payload) {
  String batt = getValue(payload, "batt=");
  
  // Clean up the base64 string by removing newlines and carriage returns
  batt.replace("\n", "");  // Remove newline characters
  batt.replace("\r", "");  // Remove carriage return characters
  
  // Format data as JSON string
  String jsonToSend = String("{\"batt\":\"") + batt + "\"}";

  // Print the formatted JSON
  Serial.print("Formatted JSON: ");
  Serial.println(jsonToSend);

  // Send the formatted data to the API endpoint
  if (sendDatabattToAPI(jsonToSend)) {
    Serial.println("Data sent to API successfully.");
  } else {
    Serial.println("Failed to send data to API.");
  }
}
void handlemapgsData(String payload) {
  String mapgs = getValue(payload, "mapgs=");
  
  // Clean up the base64 string by removing newlines and carriage returns
  mapgs.replace("\n", "");  // Remove newline characters
  mapgs.replace("\r", "");  // Remove carriage return characters
  
  // Format data as JSON string
  String jsonToSend = String("{\"mapgs\":\"") + mapgs + "\"}";

  // Print the formatted JSON
  Serial.print("Formatted JSON: ");
  Serial.println(jsonToSend);

  // Send the formatted data to the API endpoint
  if (sendDatamapgsToAPI(jsonToSend)) {
    Serial.println("Data sent to API successfully.");
  } else {
    Serial.println("Failed to send data to API.");
  }
}
void handlesoilprecData(String payload) {
  String soilprec = getValue(payload, "soilprec=");
  
  // Clean up the base64 string by removing newlines and carriage returns
  soilprec.replace("\n", "");  // Remove newline characters
  soilprec.replace("\r", "");  // Remove carriage return characters
  
  // Format data as JSON string
  String jsonToSend = String("{\"soilprec\":\"") + soilprec + "\"}";

  // Print the formatted JSON
  Serial.print("Formatted JSON: ");
  Serial.println(jsonToSend);

  // Send the formatted data to the API endpoint
  if (sendDatasoilprecToAPI(jsonToSend)) {
    Serial.println("Data sent to API successfully.");
  } else {
    Serial.println("Failed to send data to API.");
  }
}
void handlesoilphData(String payload) {
  String soilph = getValue(payload, "soilph=");
  
  // Clean up the base64 string by removing newlines and carriage returns
  soilph.replace("\n", "");  // Remove newline characters
  soilph.replace("\r", "");  // Remove carriage return characters
  
  // Format data as JSON string
  String jsonToSend = String("{\"soilph\":\"") + soilph + "\"}";

  // Print the formatted JSON
  Serial.print("Formatted JSON: ");
  Serial.println(jsonToSend);

  // Send the formatted data to the API endpoint
  if (sendDatasoilphToAPI(jsonToSend)) {
    Serial.println("Data sent to API successfully.");
  } else {
    Serial.println("Failed to send data to API.");
  }
}
void handlehumidityData(String payload) {
  String humidity = getValue(payload, "humidity=");
  
  // Clean up the base64 string by removing newlines and carriage returns
  humidity.replace("\n", "");  // Remove newline characters
  humidity.replace("\r", "");  // Remove carriage return characters
  
  // Format data as JSON string
  String jsonToSend = String("{\"humidity\":\"") + humidity + "\"}";

  // Print the formatted JSON
  Serial.print("Formatted JSON: ");
  Serial.println(jsonToSend);

  // Send the formatted data to the API endpoint
  if (sendDatahumidityToAPI(jsonToSend)) {
    Serial.println("Data sent to API successfully.");
  } else {
    Serial.println("Failed to send data to API.");
  }
}
// Function to send the formatted JSON to the API endpoint


void fetchData() {
  if (WiFi.status() == WL_CONNECTED) { 
    HTTPClient http;
    String url = "https://agroxsat.onrender.com/backendapi/command/";
    http.begin(url);  
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String response = http.getString(); 
      Serial.println(httpResponseCode); // Print HTTP response code for debugging  
      Serial.println(response);          // Print the raw JSON response

      DynamicJsonDocument doc(1024); 
      DeserializationError error = deserializeJson(doc, response);

      if (!error) {
        if (!doc["command"].isNull()) {
          String command = doc["command"]; 
          Serial.print("Command: ");
          Serial.println(command);

          command += '~';   // Add delimiter for mySerial communication
          mySerial.println(command); // Send command to mySerial
          
          delay(50); // Allow a moment for mySerial to respond
          
          if (mySerial.available()) {
            String status = mySerial.readStringUntil('~');
            if (status == "received") {
              mySerial.println(command); // Send command again if "received"
            }
          }

        } else {
          Serial.println("Command is null or not available.");
        }
      } else {
        Serial.print("JSON Deserialization Error: ");
        Serial.println(error.f_str());
      }
    } else {
      Serial.print("Error on HTTP request: ");
      Serial.println(httpResponseCode);
    }

    http.end(); 
  } else {
    Serial.println("WiFi not connected");
  }
}

void loop() {
  if(millis() >= 10000){
      indicator1 = millis();
      fetchData();
     
  }

  //if (mySerial.available()) {
  //  // Read the entire payload from LoRa
  //  String loRaPayload = mySerial.readString();
//
  //  // Clean up the payload by removing any newline or carriage return characters
  //  loRaPayload.replace("\n", "");  // Remove newline characters
  //  loRaPayload.replace("\r", "");  // Remove carriage return characters
//
  //  Serial.print("Received via LoRa: ");
  //  Serial.println(loRaPayload);
  //  int index = loRaPayload.indexOf('=');
  //  String parameter = loRaPayload.substring(0, index);
  //  Serial.println(loRaPayload);
  //  
  //  if(parameter == "temperature"){
  //      handletemperatureData(loRaPayload);
  //  }
  //  else if(parameter == "images"){
  //      handleimageData(loRaPayload);
  //  }
  //  else if(parameter == "location"){
  //      handlelocationData(loRaPayload);
  //  }
  //  else if(parameter == "smoke"){
  //      handlesmokeData(loRaPayload);
  //  }
  //  else if(parameter == "batt"){
  //      handlebattData(loRaPayload);
  //  }
  //  else if(parameter == "mapgs"){
  //      handlemapgsData(loRaPayload);
  //  }
  //  else if(parameter == "soilprec"){
  //      handlesoilprecData(loRaPayload);
  //  }
  //  else if(parameter == "humidity"){
  //      handlehumidityData(loRaPayload);
  //  }
  //  else if(parameter == "soilph"){
  //      handlesoilphData(loRaPayload);
  //  }
    
    
  //}

  //delay(1000);  
}