#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN pins
const uint64_t pipeAddress = 0xE8E8F0F0E1LL;

Servo thumbServo;
Servo indexServo;
Servo middleServo;
Servo ringServo;
Servo pinkyServo;

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(1, pipeAddress);
  radio.startListening();

  thumbServo.attach(2);
  indexServo.attach(3);
  middleServo.attach(4);
  ringServo.attach(5);
  pinkyServo.attach(6);
}

void loop() {
  if (radio.available()) {
    char dataReceived[50];
    radio.read(&dataReceived, sizeof(dataReceived));

    String dataString = String(dataReceived);
    int thumbPos = dataString.substring(0, dataString.indexOf(',')).toInt();
    dataString.remove(0, dataString.indexOf(',') + 1);
    int indexPos = dataString.substring(0, dataString.indexOf(',')).toInt();
    dataString.remove(0, dataString.indexOf(',') + 1);
    int middlePos = dataString.substring(0, dataString.indexOf(',')).toInt();
    dataString.remove(0, dataString.indexOf(',') + 1);
    int ringPos = dataString.substring(0, dataString.indexOf(',')).toInt();
    dataString.remove(0, dataString.indexOf(',') + 1);
    int pinkyPos = dataString.toInt();

    thumbServo.write(thumbPos);
    indexServo.write(indexPos);
    middleServo.write(middlePos);
    ringServo.write(ringPos);
    pinkyServo.write(pinkyPos);
  }
}
