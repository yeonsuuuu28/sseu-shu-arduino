#include <Firebase.h>
#include <WiFi.h>
#include <SPI.h>
#include <MFRC522.h>
#include "HX711.h"

const char* ssid = "AndroidHotspot6466";
const char* password = "BTM453APLUS";

#define FIREBASE_HOST "https://sseu-shu-db-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "YWK8fpkeAQXorRA9naX3ev8uW6fcGhSN9IerYaSk"
#define LIGHT_SENSOR_PIN 36
const int LOADCELL_DOUT_PIN = 16;
const int LOADCELL_SCK_PIN = 4;
float weight = 0.0f;

HX711 scale;

FirebaseData firebaseData;
FirebaseAuth mAuth;
FirebaseJson json1;
FirebaseJson json2;
FirebaseConfig mConfig;

int i = 0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WIFI");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(-100);
  scale.tare();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected with WIFI");
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  Serial.print("Connected with Firebase");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    int analogValue = analogRead(LIGHT_SENSOR_PIN);

    Serial.print("Light Value = ");
    Serial.print(analogValue);
    Serial.println();

    if (scale.get_units() < 0) {
      weight = scale.get_units() * -1;
      json1.set("/weight", weight);
      Firebase.updateNode(firebaseData, "/controls", json1);
    }
    else {
      weight = scale.get_units();
      json1.set("/weight", weight);
      Firebase.updateNode(firebaseData, "/controls", json1);
    }

    Serial.print("Weight Value = ");
    Serial.print(weight, 1);
    Serial.print(" g");
    Serial.println();
    Serial.println();

    if (analogValue < 2500) {
      json2.set("/open", true);
      Firebase.updateNode(firebaseData, "/controls", json2);
      json2.set("/RFID_user", "A3 EC 21 13");
      Firebase.updateNode(firebaseData, "/controls", json2);
      delay(10000);
    }
  }

  else {
    Serial.println("WIFI Not Connected");
  }

  delay(1000);
}
