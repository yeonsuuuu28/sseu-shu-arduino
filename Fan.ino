#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT_U.h>
#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int INA = 9;  
int INB = 8;

void setup() { 
  //serial
  Serial.begin(9600);

  //humidty sensor
  dht.begin();

  //lcd screen
  lcd.init();
  lcd.backlight();

  //motor
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

      lcd.setCursor(0,0);
      lcd.print("Humidity: ");
      lcd.print(event.relative_humidity);
      lcd.print("%");
      lcd.setCursor(0,1);
      lcd.print("Level: 0");
      
      Serial.print(F("Humidity: "));
      Serial.print(event.relative_humidity);
      Serial.println(F("%"));
    }
    else if (event.relative_humidity >= 50 && event.relative_humidity < 65) {
      analogWrite(9, 85);
      analogWrite(10, 0);

      lcd.setCursor(0,0);
      lcd.print("Humidity: ");
      lcd.print(event.relative_humidity);
      lcd.print("%");
      lcd.setCursor(0,1);
      lcd.print("Level: 1");

      Serial.print(F("Humidity: "));
      Serial.print(event.relative_humidity);
      Serial.println(F("%"));
    }
    else if (event.relative_humidity >= 65 && event.relative_humidity < 80) {
      analogWrite(9, 170);
      analogWrite(10, 0);

      lcd.setCursor(0,0);
      lcd.print("Humidity: ");
      lcd.print(event.relative_humidity);
      lcd.print("%");
      lcd.setCursor(0,1);
      lcd.print("Level: 2");

      Serial.print(F("Humidity: "));
      Serial.print(event.relative_humidity);
      Serial.println(F("%"));
    }
    else {
      analogWrite(9, 255);
      analogWrite(10, 0);

      lcd.setCursor(0,0);
      lcd.print("Humidity: ");
      lcd.print(event.relative_humidity);
      lcd.print("%");
      lcd.setCursor(0,1);
      lcd.print("Level: 3");

      Serial.print(F("Humidity: "));
      Serial.print(event.relative_humidity);
      Serial.println(F("%"));
    }
  }
}