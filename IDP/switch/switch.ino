const int switchPin = 32;

void setup() {
  pinMode(switchPin, INPUT_PULLUP);  // Enable pull-up
  Serial.begin(9600);
}

void loop() {
  int switchState = digitalRead(switchPin);

  // Debug raw readings
  Serial.print("Raw pin state: ");
  Serial.println(switchState);  // Should be 0 when pressed

  if (switchState == LOW) {  // Pressed = LOW (GND)
    Serial.println("PRESSED (confirmed)");
    delay(500);  // Debounce
  } else {
    Serial.println("RELEASED");
    delay(500);
  }
}
