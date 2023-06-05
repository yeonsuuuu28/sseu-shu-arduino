#include <SPI.h>
#include <MFRC522.h>

//need to change for ESP32 board; for now it's arduino uno
#define SS_PIN 10
#define RST_PIN 9
#define LED_G 5 //green LED pin
#define LED_R 4 //red LED pin
#define RELAY 3 //relay pin
#define BUZZER 2 //buzzer pin
#define ACCESS_DELAY 1000
#define ACCESS_DELAY2 2000
#define DENIED_DELAY 1000
#define OPEN_DELAY 4000
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

void (*resetFunc)(void) = 0;

void setup() {
  Serial.begin(9600);   
  SPI.begin();          
  mfrc522.PCD_Init();   
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  digitalWrite(RELAY, LOW);
  Serial.println("Please tag your card to the reader.");
  Serial.println();
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  //Show UID on serial monitor
  //Get UID as string
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  //print message
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();

  //If UID of my card is authorized
  if (content.substring(1) == "A3 EC 21 13") {
    //print message
    Serial.println("Access Authorized");
    Serial.println();
    delay(500);
    //unlock solenoid lock, turn on green led, play buzzer sound
    digitalWrite(RELAY, HIGH);
    digitalWrite(LED_G, HIGH);
    tone(BUZZER, 330);
    delay(ACCESS_DELAY); //1 sec
    noTone(BUZZER);
    delay(ACCESS_DELAY2); //2 sec
    digitalWrite(LED_G, LOW);
    delay(OPEN_DELAY); //4 sec
    digitalWrite(RELAY, LOW);
    delay(1000);
    resetFunc();
  }

 //If unauthorized
 else   {
   //print message
    Serial.println("Access denied");
    // digitalWrite(LED_R, HIGH);
    //just play buzzer and turn on red LED
    tone(BUZZER, 262);
    delay(DENIED_DELAY);
    // digitalWrite(LED_R, LOW);
    noTone(BUZZER);
  }
  
  mfrc522.PICC_HaltA(); // halt PICC
  mfrc522.PCD_StopCrypto1(); // stop encryption on PCD
}