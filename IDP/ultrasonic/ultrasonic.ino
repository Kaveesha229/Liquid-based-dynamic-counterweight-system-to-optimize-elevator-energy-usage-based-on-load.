#define TRIG_PIN 36
#define ECHO_PIN 35
#define RELAY_PIN 37

long duration;
int distance;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // motor OFF initially
  Serial.begin(9600);
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo
  duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30ms
  distance = duration * 0.034 / 2; // convert to cm

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);

  // Control relay based on distance
  if (distance >= 12) {
    digitalWrite(RELAY_PIN, HIGH);  // motor ON
  } else if (distance <= 7) {
    digitalWrite(RELAY_PIN, LOW);   // motor OFF
  }
}