#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11);   // RX, TX

const int ledPin = 9;
const int potPin = A0;

void setup() {
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  BT.begin(9600);
}

void loop() {

  // ==========================
  // Receive button state from A
  // ==========================

  if (BT.available()) {
    char command = BT.read();

    if (command == '1') {
      digitalWrite(ledPin, HIGH);
    }
    else if (command == '0') {
      digitalWrite(ledPin, LOW);
    }
  }


  // ==========================
  // Send potentiometer to A
  // ==========================

  int potValue = analogRead(potPin);

  // Arduino ADC: 0 ~ 1023
  // Convert to PWM range: 0 ~ 255
  int motorSpeed = map(potValue, 0, 1023, 0, 255);

  BT.println(motorSpeed);

  delay(50);
}