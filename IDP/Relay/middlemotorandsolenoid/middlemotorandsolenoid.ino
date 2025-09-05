// Relay pins
#define RELAY1 39


void setup() {
  pinMode(RELAY1, OUTPUT);


  // Start with both off
  digitalWrite(RELAY1, LOW);

}

void loop() {
  // Turn ON relay 1 for 1 second
  digitalWrite(RELAY1, HIGH);
  delay(8000);
  digitalWrite(RELAY1, LOW);
  delay(3000);


}
