# Bluetooth Bidirectional Control

## Overview

This project implements bidirectional wireless communication between two Arduino boards using HC-05 Bluetooth modules in a Master/Slave configuration.

The system is divided into two nodes:

- **Student A — Master Node**
- **Student B — Slave Node**

The two Arduino boards exchange control data through Bluetooth.

### Communication Functions

- When Student A presses or releases the push button, Student B's LED turns ON or OFF.
- When Student B rotates the potentiometer, Student A's DC motor changes speed according to the potentiometer value.

---

## Hardware Description

### Master Node — Student A

The Master Node contains:

- Arduino Uno
- HC-05 Bluetooth module configured as **MASTER**
- Push button
- DC motor
- Motor driver / transistor circuit
- Resistors and jumper wires
- Breadboard

The push button is used as the input device. Its state is transmitted through the HC-05 module to the Slave Node.

The Master Node also receives the potentiometer value from the Slave Node and uses it to control the speed of the DC motor using PWM.

---

### Slave Node — Student B

The Slave Node contains:

- Arduino Uno
- HC-05 Bluetooth module configured as **SLAVE**
- Potentiometer
- LED
- Current-limiting resistor for the LED
- Jumper wires
- Breadboard

The potentiometer provides an analog input value from `0` to `1023`. The Arduino converts this value into a PWM range from `0` to `255` and sends it to the Master Node through Bluetooth.

The Slave Node also receives the push-button state from the Master Node and controls the LED accordingly.

---

## System Architecture

```text
        Student A — MASTER                     Student B — SLAVE

        Push Button                            Potentiometer
             |                                      |
             v                                      v
        +-----------+                          +-----------+
        | Arduino A |                          | Arduino B |
        +-----------+                          +-----------+
             |                                      |
             |          HC-05 Bluetooth             |
             |<------------------------------------>|
             |                                      |
             v                                      v
         DC Motor                                  LEDtitle + hardware description
