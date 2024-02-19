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

SelfAbot abot(servoLeftPin, servoRightPin);
float factor = 10.5; // Factor to convert angle to duration

void setup() {
    abot.setup();
    abot.servoAttachPins(13, 12);
    rotateRobot(360);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// The rotateRobot function
void rotateRobot(int angle) {
    int duration = (int)(angle * factor);

    abot.servoSpeed(40, 40); // Adjust speed as needed
    delay(duration);
    abot.servoSpeed(0, 0); // Stop the robot after rotating
}