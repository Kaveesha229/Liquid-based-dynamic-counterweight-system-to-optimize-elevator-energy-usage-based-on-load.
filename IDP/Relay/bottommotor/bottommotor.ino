// Relay pins
#define RELAY1 37 // 39 middle, 38 top, 37 bottom.


void setup() {
  pinMode(RELAY1, OUTPUT);


  // Start with both of
  digitalWrite(RELAY1, HIGH);

}

void loop() {
  // Turn ON relay 1 for 1 second
  digitalWrite(RELAY1, HIGH);
  delay(5000);
  // digitalWrite(RELAY1, LOW);
  // delay(1000);


}
