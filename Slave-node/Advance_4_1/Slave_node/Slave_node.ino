#include <SoftwareSerial.h>

// ======================================================
// Advanced Task 4-1
// Student B - HC-05 SLAVE
//
// Function:
// 1. Receive button state from MASTER -> control LED
// 2. Read potentiometer -> send motor speed to MASTER
// ======================================================


// ---------------- Pin Configuration ----------------

// HC-05
// HC-05 TXD -> Arduino D10
// HC-05 RXD -> Arduino D11
SoftwareSerial BT(10, 11);   // Arduino RX, TX

// LED
const int LED_PIN = 9;

// Potentiometer
const int POT_PIN = A0;


// ---------------- Variables ----------------

int potValue = 0;
int motorSpeed = 0;

unsigned long lastSendTime = 0;
const unsigned long SEND_INTERVAL = 50;   // send every 50 ms


void setup() {

  // Debug Serial Monitor
  Serial.begin(9600);

  // HC-05 communication
  BT.begin(9600);

  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);

  Serial.println("=================================");
  Serial.println("HC-05 SLAVE NODE STARTED");
  Serial.println("Waiting for MASTER...");
  Serial.println("=================================");
}


void loop() {

  // ====================================================
  // Part 1:
  // Receive button state from Student A
  // ====================================================

  if (BT.available()) {

    char command = BT.read();

    // MASTER button pressed
    if (command == '1') {

      digitalWrite(LED_PIN, HIGH);

      Serial.println("Received: 1 -> LED ON");
    }

    // MASTER button released
    else if (command == '0') {

      digitalWrite(LED_PIN, LOW);

      Serial.println("Received: 0 -> LED OFF");
    }
  }


  // ====================================================
  // Part 2:
  // Read potentiometer and send motor speed to MASTER
  // ====================================================

  if (millis() - lastSendTime >= SEND_INTERVAL) {

    lastSendTime = millis();

    // ADC value: 0 ~ 1023
    potValue = analogRead(POT_PIN);

    // Convert to PWM value: 0 ~ 255
    motorSpeed = map(potValue, 0, 1023, 0, 255);

    // Send speed to MASTER
    BT.println(motorSpeed);

    // Debug information
    Serial.print("Potentiometer: ");
    Serial.print(potValue);

    Serial.print("   Motor Speed: ");
    Serial.println(motorSpeed);
  }
}