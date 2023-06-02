#include "HX711.h"

// HX711 circuit wiring
#define DOUT  A0
#define CLK   A1

HX711 scale;

void setup() {
  Serial.begin(57600);
  scale.begin(DOUT, CLK);
}

void loop() {
  if (scale.is_ready()) {
    scale.set_scale();    
    Serial.println("Tare... remove any weights from the scale.");
    delay(5000);
    scale.tare();
    Serial.println("Tare done...");
    Serial.print("Place a known weight on the scale...");
    delay(5000);
    long reading = scale.get_units(10);
    Serial.print("Result: ");
    Serial.println(reading);
  } 
  else {
    Serial.println("HX711 not found.");
  }
  delay(1000);
}