#include "HX711.h"

#define DT  45// 45 , 43
#define SCK 44 // 44, 42

HX711 scale;

// Replace this with your calibration factor
float calibration_factor = 420.0;  

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 Weight Measurement");

  scale.begin(DT, SCK);
  scale.set_scale(calibration_factor);  
  scale.tare();  // Reset to 0
}

void loop() {
  Serial.print("Weight: ");
  Serial.print(scale.get_units(), 1); // 1 decimal place
  Serial.println(" g");

  delay(500);
}
