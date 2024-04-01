#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace these variables with your Wi-Fi credentials
const char* ssid = "wifi_ssid";
const char* password = "wifi_password";

ESP8266WebServer server(80);

// Pin connected to Relay
const int relayPin = D3;  // Change this to the pin you want to control

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
}

void loop() {
  server.handleClient();
}
