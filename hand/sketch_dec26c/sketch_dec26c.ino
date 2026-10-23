#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN pins
const uint64_t pipeAddress = 0xE8E8F0F0E1LL;

const int thumbPin = A0;
const int indexPin = A1;
const int middlePin = A2;
const int ringPin = A3;
const int pinkyPin = A4;

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(pipeAddress);
}

void loop() {
  // Read sensor values
  int thumbValue = analogRead(thumbPin);
  int indexValue = analogRead(indexPin);
  int middleValue = analogRead(middlePin);
  int ringValue = analogRead(ringPin);
  int pinkyValue = analogRead(pinkyPin);

  // Create a formatted string for sensor data
  String sensorData = String(thumbValue) + "," + String(indexValue) + "," + String(middleValue) + "," + String(ringValue) + "," + String(pinkyValue);

  // Convert string to char array
  char dataToSend[50];
  sensorData.toCharArray(dataToSend, sizeof(dataToSend));

  // Send data through radio
  radio.write(&dataToSend, sizeof(dataToSend));

  delay(100); // Adjust delay based on your requirements
}