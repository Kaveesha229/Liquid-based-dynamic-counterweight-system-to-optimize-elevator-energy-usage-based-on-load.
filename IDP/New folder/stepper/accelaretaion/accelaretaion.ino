#define DIR_PIN 53
#define STEP_PIN 52
const int stepsPerRevolution = 1500;  // Microstepping steps per revolution

// Motion profile parameters
const float acceleration = 1000.0;  // steps/s² (adjust for desired acceleration)
const float maxSpeed = 750.0;       // steps/s (adjust for your motor's capability)

void setup() {
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  digitalWrite(DIR_PIN, LOW);
  digitalWrite(STEP_PIN, LOW);
  delay(100);  // Driver stabilization
}

void loop() {
  // Forward (1 revolution in 2 seconds)
  digitalWrite(DIR_PIN, LOW);
  moveStepperSmooth(stepsPerRevolution, 2000);
  delay(1000);

  // Forward again
  digitalWrite(DIR_PIN, LOW);
  moveStepperSmooth(stepsPerRevolution, 2000);
  delay(1000);
  
  // Backward (1 revolution in 2 seconds)
  digitalWrite(DIR_PIN, HIGH);
  moveStepperSmooth(stepsPerRevolution, 2000);
  delay(1000);

  // Backward again
  digitalWrite(DIR_PIN, HIGH);
  moveStepperSmooth(stepsPerRevolution, 2000);
  delay(1000);
}

void moveStepperSmooth(int totalSteps, int totalTimeMs) {
  float totalTime = totalTimeMs / 1000.0;  // Convert to seconds
  
  // Calculate motion profile parameters
  float accelTime = maxSpeed / acceleration;
  float accelDist = 0.5 * acceleration * accelTime * accelTime;
  
  // Determine if we can reach max speed
  if (2 * accelDist > totalSteps) {
    // Triangular profile (never reach max speed)
    accelTime = sqrt(totalSteps / acceleration);
    accelDist = 0.5 * acceleration * accelTime * accelTime;
    float cruiseTime = 0;
    float cruiseSpeed = acceleration * accelTime;
  } else {
    // Trapezoidal profile
    float cruiseDist = totalSteps - 2 * accelDist;
    float cruiseTime = cruiseDist / maxSpeed;
    float cruiseSpeed = maxSpeed;
  }
  
  // Convert to step delays
  float currentSpeed = 0;
  unsigned long lastStepTime = micros();
  
  for (int stepCount = 0; stepCount < totalSteps; stepCount++) {
    // Calculate desired speed at this point
    if (stepCount < accelDist) {
      // Acceleration phase
      currentSpeed = acceleration * sqrt(2 * stepCount / acceleration);
    } else if (stepCount < (totalSteps - accelDist)) {
      // Cruise phase
      currentSpeed = maxSpeed;
    } else {
      // Deceleration phase
      float decelPoint = totalSteps - stepCount;
      currentSpeed = acceleration * sqrt(2 * decelPoint / acceleration);
    }
    
    // Calculate required delay
    unsigned long stepDelay = 1000000.0 / currentSpeed;  // microseconds
    
    // Wait until it's time for the next step
    while (micros() - lastStepTime < stepDelay) {
      // Busy wait (you could add yield() here if using ESP)
    }
    
    // Pulse the step pin
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(5);  // Minimum pulse width for DRV8825
    digitalWrite(STEP_PIN, LOW);
    
    lastStepTime = micros();
  }
}
