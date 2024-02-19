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

const byte servoPin = 9;
SelfAbot abot;

void setup() {
    abot.setup();
    abot.servoAttachAngle(servoPin);
}

void loop() {
    for (int pos = 0; pos < 180; pos += 1) {
      abot(servoPin).servoAngle(pos);
      delay(15);
    }
    for (int pos = 180; pos >= 1; pos -= 1) {
      abot(servoPin).servoAngle(pos);
      delay(15);
    }
}
