#include "HX711.h"

#define DIR_PIN 53
#define STEP_PIN 52
#define red 40    // red light
#define green 41  // green light

#define ENABLE_PIN 34

#define TRIG_PIN 36
#define ECHO_PIN 35

#define RELAY_BTM 37

#define RELAY_TOP 38  // 39 middle, 38 top, 37 bottom.

#define RELAY_MDL 39


long duration;
int distance;

#define DT_PIN1 45
#define SCK_PIN1 44
#define DT_PIN2 43
#define SCK_PIN2 42

const int ir1 = 51;  // bottom ir
const int ir2 = 50;  // middle ir
const int ir3 = 49;  // top ir

const int sw1 = 48;  // bottom switch
const int sw2 = 47;  // middle switch
const int sw3 = 46;  // top switch
//const int sw4 = 37;  // start switch

const int stat = 32;  // for static counter weights

void up();
void down();
void stop_s();
void balance();
void top();
void bottom();
void tank();
void statc();
void dynamicc();
void staticc();

int roundedWeight1;  // lift
int roundedWeight2;  // counterweight
float weight1;
float weight2;
HX711 scale1;
HX711 scale2;

int b = 9;
int k;

void setup() {
  Serial.begin(9600);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  digitalWrite(DIR_PIN, LOW);  //(LOW = forward, HIGH = reverse)

  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);

  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(sw3, INPUT_PULLUP);
  //pinMode(sw4, INPUT_PULLUP);
  pinMode(stat, INPUT_PULLUP);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_BTM, OUTPUT);
  digitalWrite(RELAY_BTM, LOW);  // motor OFF initially

  pinMode(ENABLE_PIN, OUTPUT);
  digitalWrite(ENABLE_PIN, LOW);

  pinMode(RELAY_TOP, OUTPUT);
  digitalWrite(RELAY_TOP, LOW);

  pinMode(RELAY_MDL, OUTPUT);
  digitalWrite(RELAY_MDL, LOW);

  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  digitalWrite(green, HIGH);
  digitalWrite(red, HIGH);

  scale1.begin(DT_PIN1, SCK_PIN1);
  scale2.begin(DT_PIN2, SCK_PIN2);

  delay(1000);

  scale1.tare();
  scale2.tare();
  Serial.println("Tare done. Ready to read weight.");

  scale1.set_scale(420);  // Adjust based on calibration
  scale2.set_scale(420);  // Adjust based on calibration
}

void loop() {

  // if (b == 8) {
  //   digitalWrite(green, LOW);
  //   digitalWrite(red, HIGH);
  //   if (digitalRead(sw4) == LOW) {
  //     digitalWrite(green, HIGH);
  //     digitalWrite(red, LOW);
  //     b = 9;
  //   }
  // }

  statc();
}

void dynamicc() {

  // tank();

  if (b == 9) {
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
    // tank();
    b = 10;
  }

  if (b == 10) {
    if (digitalRead(sw1) == LOW) {
      b = 11;
    } else {
      b = 13;
    }
  }

  if (b == 11) {
    if (digitalRead(ir1) == LOW) {
      b = 9;
    } else {
      b = 12;
    }
  }

  if (b == 12) {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    balance();
    while (digitalRead(ir1) != LOW) {
      down();
    }
    unsigned long startTime = millis();
    while (millis() - startTime < 100) {
      down();
    }
    b = 9;
    tank();
  }

  if (b == 13) {
    if (digitalRead(sw2) == LOW) {
      b = 14;
    } else {
      b = 18;
    }
  }

  if (b == 14) {
    if (digitalRead(ir2) == LOW) {
      b = 9;
    } else {
      b = 15;
    }
  }

  if (b == 15) {
    if (digitalRead(ir1) == LOW) {
      b = 16;
    } else {
      b = 17;
    }
  }

  if (b == 16) {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    balance();
    while (digitalRead(ir2) != LOW) {
      up();
    }
    unsigned long startTime = millis();
    while (millis() - startTime < 150) {
      up();
      b = 9;
      //tank();
    }
  }

  if (b == 17) {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    balance();
    while (digitalRead(ir2) != LOW) {
      down();
    }
    unsigned long startTime = millis();
    while (millis() - startTime < 150) {
      down();
      b = 9;
      //tank();
    }
  }

  if (b == 18) {
    if (digitalRead(sw3) == LOW) {
      b = 19;
    } else {
      b = 9;
    }
  }

  if (b == 19) {
    if (digitalRead(ir3) == LOW) {
      b = 9;
    } else {
      b = 20;
    }
  }

  if (b == 20) {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    balance();
    while (digitalRead(ir3) != LOW) {
      up();
    }
    b = 9;
    //tank();
  }
}

void staticc() {
  weight2 = scale2.get_units(5);
  roundedWeight2 = round(weight2 / 200.0) * 200;
  if (roundedWeight2 < 0) roundedWeight2 = 0;

  if (roundedWeight2 < 500) {
    load();
  }
  if (b == 9) {
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
    // tank();
    b = 10;
  }

  if (b == 10) {
    if (digitalRead(sw1) == LOW) {
      b = 11;
    } else {
      b = 13;
    }
  }

  if (b == 11) {
    if (digitalRead(ir1) == LOW) {
      b = 9;
    } else {
      b = 12;
    }
  }

  if (b == 12) {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    while (digitalRead(ir1) != LOW) {
      down();
    }
    unsigned long startTime = millis();
    while (millis() - startTime < 100) {
      down();
      b = 9;
    }
  }

  if (b == 13) {
    if (digitalRead(sw2) == LOW) {
      b = 14;
    } else {
      b = 18;
    }
  }

  if (b == 14) {
    if (digitalRead(ir2) == LOW) {
      b = 9;
    } else {
      b = 15;
    }
  }

  if (b == 15) {
    if (digitalRead(ir1) == LOW) {
      b = 16;
    } else {
      b = 17;
    }
  }

  if (b == 16) {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    while (digitalRead(ir2) != LOW) {
      up();
    }
    unsigned long startTime = millis();
    while (millis() - startTime < 150) {
      up();
      b = 9;
    }
  }

  if (b == 17) {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    while (digitalRead(ir2) != LOW) {
      down();
    }
    unsigned long startTime = millis();
    while (millis() - startTime < 150) {
      down();
      b = 9;
    }
  }

  if (b == 18) {
    if (digitalRead(sw3) == LOW) {
      b = 19;
    } else {
      b = 9;
    }
  }

  if (b == 19) {
    if (digitalRead(ir3) == LOW) {
      b = 9;
    } else {
      b = 20;
    }
  }

  if (b == 20) {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    while (digitalRead(ir3) != LOW) {
      up();
    }
    b = 9;
  }
}

void load() {
  int k = 1;
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  // digitalWrite(ENABLE_PIN, HIGH);
  while (k == 1) {
    // stop_s();
    Serial.println("Sending water from top to counter tank");
    digitalWrite(RELAY_TOP, HIGH);  // Turn on the relay

    // Allow time for water transfer before reading weights
    delay(4000);  // Increased delay for better stability 2000 for 50 g

    digitalWrite(RELAY_TOP, LOW);

    delay(700);

    // Update readings with proper scaling
    weight2 = scale2.get_units(5);
    roundedWeight2 = round(weight2 / 50.0) * 50;

    if (roundedWeight2 < 0) roundedWeight2 = 0;

    Serial.print("Updated Weight2: ");
    Serial.print(roundedWeight2);
    Serial.println(" g");

    if (roundedWeight2 >= 800) {
      k = 0;
      digitalWrite(RELAY_TOP, LOW);
      digitalWrite(ENABLE_PIN, LOW);
      digitalWrite(red, HIGH);
      digitalWrite(green, LOW);
    }
  }
}

void balance() {
  //digitalWrite(ENABLE_PIN, HIGH);
  stop_s();
  float weight1 = scale1.get_units(3);
  float weight2 = scale2.get_units(3);

  // Round to nearest 50g
  roundedWeight1 = round(weight1 / 250.0) * 250;
  roundedWeight2 = round(weight2 / 250.0) * 250;

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

  if (roundedWeight1 > roundedWeight2) {
    top();
  } else if (roundedWeight1 < roundedWeight2) {
    bottom();
  }
}

void top() {
  int k = 1;
  stop_s();
  // digitalWrite(ENABLE_PIN, HIGH);
  while (k == 1) {
    // stop_s();
    Serial.println("Sending water from top to counter tank");
    digitalWrite(RELAY_TOP, HIGH);  // Turn on the relay

    // Allow time for water transfer before reading weights
    delay(4000);  // Increased delay for better stability 2000 for 50 g

    digitalWrite(RELAY_TOP, LOW);

    delay(700);

    // Update readings with proper scaling
    weight1 = scale1.get_units(5);  // Take 5 readings for averaging
    weight2 = scale2.get_units(5);

    roundedWeight1 = round(weight1 / 50.0) * 50;
    roundedWeight2 = round(weight2 / 50.0) * 50;

    // Ensure non-negative values
    if (roundedWeight1 < 0) roundedWeight1 = 0;
    if (roundedWeight2 < 0) roundedWeight2 = 0;

    Serial.print("Updated Weight1: ");
    Serial.print(roundedWeight1);
    Serial.println(" g");

    Serial.print("Updated Weight2: ");
    Serial.print(roundedWeight2);
    Serial.println(" g");

    if (roundedWeight1 <= roundedWeight2) {
      k = 0;
    }
  }

  // Always turn off the relay when exiting the loop
  digitalWrite(RELAY_TOP, LOW);
  Serial.println("Top transfer completed - Relay OFF");
  //digitalWrite(ENABLE_PIN, LOW);
}

void bottom() {
  stop_s();
  // digitalWrite(ENABLE_PIN, HIGH);
  int k = 1;
  while (k == 1) {
    // stop_s();
    Serial.println("Sending water from counter tank to bottom");
    digitalWrite(RELAY_MDL, HIGH);  // Turn on the relay

    // Allow time for water transfer before reading weights
    delay(4000);  // Increased delay for better stability

    digitalWrite(RELAY_MDL, LOW);

    delay(700);

    // Update readings with proper scaling
    weight1 = scale1.get_units(5);  // Take 5 readings for averaging
    weight2 = scale2.get_units(5);

    roundedWeight1 = round(weight1 / 50.0) * 50;
    roundedWeight2 = round(weight2 / 50.0) * 50;

    // Ensure non-negative values
    if (roundedWeight1 < 0) roundedWeight1 = 0;
    if (roundedWeight2 < 0) roundedWeight2 = 0;

    Serial.print("Updated Weight1: ");
    Serial.print(roundedWeight1);
    Serial.println(" g");

    Serial.print("Updated Weight2: ");
    Serial.print(roundedWeight2);
    Serial.println(" g");

    if (roundedWeight1 >= roundedWeight2) {
      k = 0;
    }
  }

  // Always turn off the relay when exiting the loop
  digitalWrite(RELAY_MDL, LOW);
  Serial.println("Bottom transfer completed - Relay OFF");
}

void statc() {  // pressed nm low
  if (digitalRead(stat) == HIGH) {
    dynamicc();
  } else if (digitalRead(stat) == LOW) {  // static counters
    staticc();
  }
}

void dis() {
  //
  // digitalWrite(ENABLE_PIN, HIGH);
  float sum = 0;  // to accumulate distances

  for (int i = 0; i < 10; i++) {
    // Trigger pulse
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Read echo
    duration = pulseIn(ECHO_PIN, HIGH, 30000);  // timeout 30ms
    float d = duration * 0.034 / 2;             // convert to cm
    sum += d;                                   // add to total
    delay(10);                                  // small delay between readings
  }

  // Average of 10 readings
  distance = sum / 10.0;
  Serial.print("distance ");

  Serial.print(distance);
}

void tank() {
  dis();
  // Control relay based on distance
  if (distance >= 11) {
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    Serial.print("water tank filling");
    digitalWrite(RELAY_BTM, HIGH);  // motor ON
    delay(20000);
    digitalWrite(RELAY_BTM, LOW);  // motor ON
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
  }
}

void up() {
  digitalWrite(ENABLE_PIN, LOW);
  digitalWrite(DIR_PIN, LOW);
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(1500);  // Controls speed (smaller = faster)
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(500);
}

void down() {
  digitalWrite(ENABLE_PIN, LOW);
  digitalWrite(DIR_PIN, HIGH);
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(1500);  // Controls speed (smaller = faster)
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(1);
}

void stop_s() {
  //digitalWrite(ENABLE_PIN, HIGH);
  // digitalWrite(DIR_PIN, HIGH);
  digitalWrite(STEP_PIN, LOW);
}
