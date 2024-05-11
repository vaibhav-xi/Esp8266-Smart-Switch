#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

// Replace these variables with your Wi-Fi credentials
const char* ssid = "wifi_ssid";
const char* password = "wifi_password";

ESP8266WebServer server(80);

// Pin connected to Relay
const int relayPin = D3;  // Change this to the pin you want to control

// Pins connected to RGB LED (common cathode)
const int redPin = D4;
const int greenPin = D5;
const int bluePin = D6;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected to Wi-Fi");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize Relay pin
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  // Initialize RGB LED pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  // Turn off RGB LED
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);

  // Route for root / web page
  server.on("/", HTTP_GET, []() {
    // HTML for the web page with on/off button
    String html = "<!DOCTYPE html><html><head><title>ESP8266 Web Server</title></head><body><h1>Switch Control</h1><p>Click to toggle Switch:</p>";
    html += "<form action='/toggle' method='post'><button type='submit'>Toggle Switch</button></form>";
    html += "</body></html>";

    server.send(200, "text/html", html);
  });

  // Route to handle toggle button
  server.on("/toggle", HTTP_POST, []() {
    static bool relayState = false;
    relayState = !relayState;
    digitalWrite(relayPin, relayState ? HIGH : LOW);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.begin();
  Serial.println("HTTP server started");

  // Initialize OTA
  ArduinoOTA.onStart([]() {
    Serial.println("OTA Update Start");
    // Blink red LED to indicate OTA update start
    setColor(255, 0, 0); // Red
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("OTA Update End");
    // Turn off all LEDs at OTA update end
    setColor(0, 0, 0); // Turn off
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("OTA Progress: %u%%\r", (progress / (total / 100)));
    // Blink blue LED to indicate OTA update progress
    setColor(0, 0, 255); // Blue
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("OTA Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
      setColor(255, 0, 255); // Magenta
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
      setColor(255, 255, 0); // Yellow
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
      setColor(255, 165, 0); // Orange
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
      setColor(255, 140, 0); // Dark Orange
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
      setColor(255, 69, 0); // Red-Orange
    }
  });

  ArduinoOTA.begin();
}

void loop() {
  server.handleClient();
  ArduinoOTA.handle();
}

// Function to set RGB LED color
void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
