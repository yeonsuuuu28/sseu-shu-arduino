#include <Firebase.h>
#include <WiFi.h>

const char* ssid = "AndroidHotspot6466";
const char* password = "BTM453APLUS";

#define FIREBASE_HOST "https://sseu-shu-db-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "YWK8fpkeAQXorRA9naX3ev8uW6fcGhSN9IerYaSk"

FirebaseData firebaseData;
FirebaseAuth mAuth;
FirebaseJson json;
FirebaseConfig mConfig;

int i = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WIFI");

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
  // put your main code here, to run repeatedly:
  if (WiFi.status() == WL_CONNECTED) {
    Firebase.getString(firebaseData, "/controls");
    Serial.println(firebaseData.to<String>());
    // json.set("/esp", i);
    // i++;
    // Firebase.updateNode(firebaseData, "/wow", json);
    // delay(500);
  }
  else {
    Serial.println("WIFI Not Connected");
  }
  delay(1000);
}