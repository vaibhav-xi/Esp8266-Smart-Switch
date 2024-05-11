// Pins connected to RGB LED (common cathode)
const int redPin = D5;
const int greenPin = D6;
const int bluePin = D7;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Initialize RGB LED pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Check if data is available to read from Serial Monitor
  if (Serial.available() > 0) {
    // Read the incoming bytes
    String input = Serial.readStringUntil('\n');
    
    // Split the input string by comma
    int commaIndex1 = input.indexOf(',');
    int commaIndex2 = input.lastIndexOf(',');
    
    // Extract R, G, and B values
    int redValue = input.substring(0, commaIndex1).toInt();
    int greenValue = input.substring(commaIndex1 + 1, commaIndex2).toInt();
    int blueValue = input.substring(commaIndex2 + 1).toInt();
    
    // Set RGB LED colors
    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);
    
    // Print received RGB values
    Serial.print("Received RGB values: R=");
    Serial.print(redValue);
    Serial.print(", G=");
    Serial.print(greenValue);
    Serial.print(", B=");
    Serial.println(blueValue);
  }
}
