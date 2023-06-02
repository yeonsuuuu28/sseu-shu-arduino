#include "HX711.h"

// HX711 circuit wiring
#define DOUT  A0
#define CLK   A1

HX711 scale;

void setup() {
  Serial.begin(57600);
  scale.begin(DOUT, CLK);
  scale.set_scale(-100);
  scale.tare();
}

void loop() {
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 1); //scale.get_units() returns a float
  Serial.print(" g"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
}