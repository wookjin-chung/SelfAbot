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

const byte servoLeftPin = 255;
const byte servoRightPin = 255;

SelfAbot abot(servoLeftPin, servoRightPin);

void setup() {
    abot.setup();
    abot.servoAttachPins(13, 12);
}

void loop() {
    abot(13).servoSpeed(0);
    abot(12).servoSpeed(0);
    delay(1000);
    abot(13).servoSpeed(150);
    abot(12).servoSpeed(-150);
    delay(1000);
    abot(13, 12).servoSpeed(-150, 150);
    delay(1000);
}
