#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 7
#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

int INA = 9;  
int INB = 8;

void setup() { 
  Serial.begin(9600);
  dht.begin();
  pinMode(INA,OUTPUT); 
  pinMode(INB,OUTPUT); 
} 

void loop() { 
  sensors_event_t event;
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    if (event.relative_humidity < 50) {
      analogWrite(9, 0);
      analogWrite(10, 0);
      Serial.print(F("Humidity: "));
      Serial.print(event.relative_humidity);
      Serial.println(F("%"));
    }
    else if (event.relative_humidity >= 50 && event.relative_humidity < 65) {
      analogWrite(9, 85);
      analogWrite(10, 0);
      Serial.print(F("Humidity: "));
      Serial.print(event.relative_humidity);
      Serial.println(F("%"));
    }
    else if (event.relative_humidity >= 65 && event.relative_humidity < 80) {
      analogWrite(9, 170);
      analogWrite(10, 0);
      Serial.print(F("Humidity: "));
      Serial.print(event.relative_humidity);
      Serial.println(F("%"));
    }
    else {
      analogWrite(9, 255);
      analogWrite(10, 0);
      Serial.print(F("Humidity: "));
      Serial.print(event.relative_humidity);
      Serial.println(F("%"));
    }
  }
} 