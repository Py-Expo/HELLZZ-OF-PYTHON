#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"

#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4

int waterSensorPin = A0; // Pin connected to the water level sensor
int threshold = 300; // Adjust this threshold according to your sensor and environment

char PHONE_NUMBER[] = "8220159993"; // Enter your phone number here
char message[] = "Flood Alert! Water detected. Take necessary actions."; // Message to be sent

SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

void setup() {
  Serial.begin(9600);
  fonaSS.begin(9600);
  if (!fona.begin(fonaSS)) {
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
  Serial.println(F("FONA is OK"));
}

void loop() {
  int waterLevel = analogRead(waterSensorPin);
  Serial.print("Water Level: ");
  Serial.println(waterLevel);
  
  if (waterLevel > threshold) {
    Serial.println("Flood Alert!");
    sendSMS(PHONE_NUMBER, message);
    delay(300000); // Delay for 5 minutes to avoid sending multiple messages
  }
}

void sendSMS(char* phoneNumber, char* message) {
  Serial.println("Sending SMS...");
  if (!fona.sendSMS(phoneNumber, message)) {
    Serial.println(F("SMS sent"));
  } else {
    Serial.println(F("SMS Sent!"));
  }
}