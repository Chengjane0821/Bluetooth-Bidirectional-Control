#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11);   // RX, TX

void setup() {
  Serial.begin(9600);
  BT.begin(38400);

  Serial.println("HC-05 AT Mode");
}

void loop() {
  // Computer -> HC-05
  if (Serial.available()) {
    BT.write(Serial.read());
  }

  // HC-05 -> Computer
  if (BT.available()) {
    Serial.write(BT.read());
  }
}