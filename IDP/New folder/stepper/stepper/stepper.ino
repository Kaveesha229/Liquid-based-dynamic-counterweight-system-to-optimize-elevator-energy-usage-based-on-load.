#define DIR_PIN 53
#define STEP_PIN 52
const int stepsPerRevolution = 1500;  // Standard NEMA17 motor

void setup() {
  // Stabilize pins immediately
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  digitalWrite(DIR_PIN, LOW);   // Set direction before stepping
  digitalWrite(STEP_PIN, LOW);  // Ensure no accidental steps
  
  delay(100);  // Let DRV8825 stabilize
}

void loop() {
  // Forward (1 rev in 2 sec)
  digitalWrite(DIR_PIN, LOW);
  rotateStepper(stepsPerRevolution, 2000);  // 200 steps, 2000ms
  
  delay(2000);

    // Forward (1 rev in 2 sec)
  digitalWrite(DIR_PIN, LOW);
  rotateStepper(stepsPerRevolution, 2000);  // 200 steps, 2000ms
  
  delay(2000);
  
  // Backward (1 rev in 1 sec)
  digitalWrite(DIR_PIN, HIGH);
  rotateStepper(stepsPerRevolution, 2000);  // 200 steps, 1000ms
  
  delay(2000);

    digitalWrite(DIR_PIN, HIGH);
  rotateStepper(stepsPerRevolution, 2000);  // 200 steps, 1000ms
  
  delay(2000);
}

void rotateStepper(int steps, int duration) {
  long stepDelay = (duration * 1000L) / steps;  // in microseconds
  
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(stepDelay / 2);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(stepDelay / 2);
  }
}
