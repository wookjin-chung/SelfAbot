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
#define INVALID_PIN 255 
const byte servoLeftPin = INVALID_PIN;
const byte servoRightPin = INVALID_PIN;
int currentLeftSpeed = 0;
int currentRightSpeed = 0;

SelfAbot abot(servoLeftPin, servoRightPin);

void setup() {
    abot.setup();
    abot.servoAttachPins(11, 10);
}

void loop() {
    gradualServoSpeed(100, -100);
    delay(2000);
    gradualServoSpeed(20, -20);
    delay(2000);
    gradualServoSpeed(-100, 100);
    delay(2000);
    gradualServoSpeed(0, 0);
    delay(2000);
}

void gradualServoSpeed(int targetLeftSpeed, int targetRightSpeed) {
    int step = 5; // Determine the step size for speed change
    while (currentLeftSpeed != targetLeftSpeed || currentRightSpeed != targetRightSpeed) {
        unsigned long currentMillis = millis();
        // Accelerate or decelerate the left servo
        if (currentLeftSpeed < targetLeftSpeed) {
            currentLeftSpeed += step;
        } else if (currentLeftSpeed > targetLeftSpeed) {
            currentLeftSpeed -= step;
        }
        // Accelerate or decelerate the right servo
        if (currentRightSpeed < targetRightSpeed) {
            currentRightSpeed += step;
        } else if (currentRightSpeed > targetRightSpeed) {
            currentRightSpeed -= step;
        }
        // Update servo speeds
        abot(11, 10).servoSpeed(currentLeftSpeed, currentRightSpeed);

        // Wait for 10ms before the next change
        while (millis() - currentMillis < 10) {
            // Small delay to wait until 10ms has passed
        }
    }
}
