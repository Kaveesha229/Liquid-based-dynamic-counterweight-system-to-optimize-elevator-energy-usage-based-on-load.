    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(500);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(500);#define DIR_PIN 53
#define STEP_PIN 52
const int stepsPerRevolution = 1500;

void setup() {
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  digitalWrite(DIR_PIN, LOW);
  digitalWrite(STEP_PIN, LOW);
  delay(100);
}

void loop() {
  digitalWrite(DIR_PIN, LOW);
  rotateStepper(stepsPerRevolution, 2000);
  delay(2000);

  digitalWrite(DIR_PIN, LOW);
  rotateStepper(stepsPerRevolution, 2000);
  delay(2000);
  
  digitalWrite(DIR_PIN, HIGH);
  rotateStepper(stepsPerRevolution, 2000);
  delay(2000);

  digitalWrite(DIR_PIN, HIGH);
  rotateStepper(stepsPerRevolution, 2000);
  delay(2000);
}

void rotateStepper(int steps, int duration) {
  long stepDelay = (duration * 1000L) / steps;
  
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(stepDelay / 2);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(stepDelay / 2);
  }
}
