#include "HX711.h"

// Define pins for HX711
#define DT_PIN1 45
#define SCK_PIN1 44
#define DT_PIN2 43
#define SCK_PIN2 42

int roundedWeight1;  // lift
int roundedWeight2;  // counterweight

HX711 scale1;
HX711 scale2;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing load cells...");

  scale1.begin(DT_PIN1, SCK_PIN1);
  scale2.begin(DT_PIN2, SCK_PIN2);

  delay(1000);  // Wait for stabilization

  scale1.tare();
  scale2.tare();
  Serial.println("Tare done. Ready to read weight.");

  scale1.set_scale(420);  // Adjust based on calibration
  scale2.set_scale(420);  // Adjust based on calibration
}

void loop() {
  // Read actual weights
  float weight1 = scale1.get_units();
  float weight2 = scale2.get_units();

  // Round to nearest 50g
  roundedWeight1 = round(weight1 / 50.0) * 50;
  roundedWeight2 = round(weight2 / 50.0) * 50;

  // Prevent negative values
  if (roundedWeight1 < 0) roundedWeight1 = 0;
  if (roundedWeight2 < 0) roundedWeight2 = 0;

  // Print current weights
  Serial.print("Weight1: ");
  Serial.print(roundedWeight1);
  Serial.println(" g");

  Serial.print("Weight2: ");
  Serial.print(roundedWeight2);
  Serial.println(" g");

  // Compare and take action
  if (roundedWeight1 > roundedWeight2) {
    while (roundedWeight1 > roundedWeight2) {
      Serial.println("send water from top to counter tank");

      Serial.print("Weight1: ");
      Serial.print(roundedWeight1);
      Serial.println(" g");

      Serial.print("Weight2: ");
      Serial.print(roundedWeight2);
      Serial.println(" g");

      delay(500);  // avoid flooding the serial monitor

      // Update readings
      weight1 = scale1.get_units();
      weight2 = scale2.get_units();
      roundedWeight1 = round(weight1 / 50.0) * 50;
      roundedWeight2 = round(weight2 / 50.0) * 50;

      if (roundedWeight1 < 0) roundedWeight1 = 0; // FIXED
      if (roundedWeight2 < 0) roundedWeight2 = 0;
    }
  }

  if (roundedWeight1 < roundedWeight2) {
    while (roundedWeight1 < roundedWeight2) {
      Serial.println("send water from counter tank to bottom");

      Serial.print("Weight1: ");
      Serial.print(roundedWeight1);
      Serial.println(" g");

      Serial.print("Weight2: ");
      Serial.print(roundedWeight2);
      Serial.println(" g");

      delay(500);  // avoid flooding the serial monitor

      // Update readings
      weight1 = scale1.get_units();
      weight2 = scale2.get_units();
      roundedWeight1 = round(weight1 / 50.0) * 50; // FIXED SIGN
      roundedWeight2 = round(weight2 / 50.0) * 50;

      if (roundedWeight1 < 0) roundedWeight1 = 0;
      if (roundedWeight2 < 0) roundedWeight2 = 0;
    }
  }
}
