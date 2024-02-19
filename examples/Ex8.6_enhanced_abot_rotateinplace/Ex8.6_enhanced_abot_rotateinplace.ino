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
#include "EnhancedSelfAbot.h"

const byte servoLeftPin = 255;
const byte servoRightPin = 255;
EnhancedSelfAbot abot(servoLeftPin, servoRightPin);

void setup() {
    Serial.begin(9600); // Start serial communication for debugging
    abot.setup();
    abot.servoAttachPins(13, 12); // Replace with actual servo pins

    abot.setAngleFactorCW(10.97);
    abot.setAngleFactorCCW(12.22);
}

void loop() {
    abot.rotateAbot(360); // Rotate robot by 90 degrees
    delay(2000); // Wait for 2 seconds

    abot.rotateAbot(-360); // Rotate robot by -90 degrees (opposite direction)
    delay(2000); // Wait for 2 seconds
}
