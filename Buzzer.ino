#include <IRremote.hpp>

#define FORCE_SENSOR_PIN A0 // the FSR and 10K pulldown are connected to A0
#define BUZZER 2
#define ERROR_DELAY 5000
#define IR 11

IRrecv irrecv(IR);
decode_results results;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  irrecv.enableIRIn();
}

void loop() {
  int analogReading = analogRead(FORCE_SENSOR_PIN);
  Serial.print("Force sensor reading = ");
  Serial.print(analogReading); // print the raw analog reading
  Serial.println();
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    Serial.println("Error Detected");
    tone(BUZZER, 262);
    delay(ERROR_DELAY);
    noTone(BUZZER);
    irrecv.resume();
  }
  if (analogReading > 800) {
    Serial.println("Error Detected");
    tone(BUZZER, 262);
    delay(ERROR_DELAY);
    noTone(BUZZER);
  }
}
