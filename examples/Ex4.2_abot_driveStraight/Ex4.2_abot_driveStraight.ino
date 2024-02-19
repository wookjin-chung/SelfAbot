/**
 * SelfAbot Library Example Code
 * This example code is part of the SelfAbot library, designed for educational purposes 
 * to teach C++ programming with Arduino Uno-based robots. It incorporates modified coding examples
 * based on Parallax educational materials.
 * Copyright (c) 2024 by wookjin chung 
 *
 * Free for personal and educational use.
 *
 * Download: https://github.com/wookjin-chung/SelfAbot
 * Report bugs to: mail@fribot.com
 *
 * Created on: February 20, 2024
 * Author: wookjin chung 
 * Version: 0.1.0
 */
#include "SelfAbot.h"
#define INVALID_PIN 255;
const byte servoLeftPin = INVALID_PIN;
const byte servoRightPin = INVALID_PIN;
float deviationFactor = 0.0; // min. val -0.15 max. val 0.15

SelfAbot abot(servoLeftPin, servoRightPin);

void setup() {
    abot.setup();
    abot.servoAttachPins(11, 10);

    driveStraight(40, -40);
    delay(8000);

    abot.servoSpeed(0, 0);
    delay(1000);
}

void loop() {

}

void driveStraight(int leftSpeed, int rightSpeed) {
    // Apply normalization to calculate correction coefficients
    float leftCoefficient = 1.0 + deviationFactor;  // Increase for left servo
    float rightCoefficient = 1.0 - deviationFactor; // Decrease for right servo

    int adjustedLeftSpeed = leftSpeed * leftCoefficient;
    int adjustedRightSpeed = rightSpeed * rightCoefficient;

    abot.servoSpeed(adjustedLeftSpeed, adjustedRightSpeed);
}
