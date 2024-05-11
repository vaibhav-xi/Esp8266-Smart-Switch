#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000); // Delay to allow time for serial monitor to open

  Serial.println("\nMemory Configuration:");
  Serial.println("---------------------");

  // Get flash chip size
  uint32_t flashChipSize = ESP.getFlashChipSize();
  Serial.printf("Flash Chip Size: %u bytes\n", flashChipSize);

  // Get flash chip real size
  uint32_t flashChipRealSize = ESP.getFlashChipRealSize();
  Serial.printf("Flash Chip Real Size: %u bytes\n", flashChipRealSize);

  // Get sketch size
  uint32_t sketchSize = ESP.getSketchSize();
  Serial.printf("Sketch Size: %u bytes\n", sketchSize);

  // Get free sketch space
  uint32_t freeSketchSpace = ESP.getFreeSketchSpace();
  Serial.printf("Free Sketch Space: %u bytes\n", freeSketchSpace);

  // Get flash chip speed
  uint32_t flashChipSpeed = ESP.getFlashChipSpeed();
  Serial.printf("Flash Chip Speed: %u Hz\n", flashChipSpeed);

  // Get flash chip mode
  FlashMode_t flashChipMode = ESP.getFlashChipMode();
  Serial.printf("Flash Chip Mode: %u\n", flashChipMode);

  Serial.println("---------------------");
}

void loop() {
  // Nothing to do here
}
