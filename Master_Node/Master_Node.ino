#include <SoftwareSerial.h>

// HC-05
SoftwareSerial BT(10, 11);   // RX, TX
// Arduino D10 <- HC-05 TXD
// Arduino D11 -> HC-05 RXD（建議分壓）

// Button
const int buttonPin = 2;

// Motor driver
const int motorEnable = 5;   // PWM
const int motorIN1 = 7;
const int motorIN2 = 8;

int lastButtonState = HIGH;

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(motorEnable, OUTPUT);
  pinMode(motorIN1, OUTPUT);
  pinMode(motorIN2, OUTPUT);

  // 馬達固定一個方向
  digitalWrite(motorIN1, HIGH);
  digitalWrite(motorIN2, LOW);

  Serial.println("MASTER ready");
}

void loop() {

  // ========================================
  // 1. A 的按鈕 -> 傳給 B 控制 LED
  // ========================================

  int buttonState = digitalRead(buttonPin);

  // 只在按鈕狀態改變時傳送
  if (buttonState != lastButtonState) {

    if (buttonState == LOW) {
      // 按下
      BT.println("B:1");
      Serial.println("Send: B:1");
    }
    else {
      // 放開
      BT.println("B:0");
      Serial.println("Send: B:0");
    }

    lastButtonState = buttonState;
  }


  // ========================================
  // 2. 接收 B 的 potentiometer 數值
  // ========================================

if (BT.available()) {

  String message = BT.readStringUntil('\n');
  message.trim();

  Serial.print("Received from B: ");
  Serial.println(message);

  int potValue = message.toInt();

  potValue = constrain(potValue, 0, 1023);

  int motorSpeed = map(potValue, 0, 1023, 0, 255);
  motorSpeed = constrain(motorSpeed, 0, 255);

  analogWrite(motorEnable, motorSpeed);

  Serial.print("Motor PWM = ");
  Serial.println(motorSpeed);
}
}
