//Get the location of the ground station and update the map accordingly
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Replace with your Google Geolocation API key
const char* apiKey = "your_API_KEY";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Get location
  getGeoLocation();
}

void getGeoLocation() {
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://www.googleapis.com/geolocation/v1/geolocate?key=";
    url += apiKey;

    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    String jsonPayload = "{\"considerIp\": \"true\"}";  // Send IP-based geolocation request
    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("HTTP Response code: " + String(httpResponseCode));
      Serial.println("Location Data: " + response);
    }
    else {
      Serial.println("Error on sending POST: " + String(httpResponseCode));
    }

    http.end();
  }
  else {
    Serial.println("WiFi not connected");
  }
}

void loop() {
  // Nothing to do in the loop
}
