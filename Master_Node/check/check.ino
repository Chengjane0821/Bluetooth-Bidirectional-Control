#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11);  // RX, TX

void setup() {
  Serial.begin(9600);
  BT.begin(38400);          // HC-05 AT mode 常見 baud rate
  Serial.println("AT mode ready");
}

void loop() {
  if (BT.available()) {
    Serial.write(BT.read());
  }

  if (Serial.available()) {
    BT.write(Serial.read());
  }
}
