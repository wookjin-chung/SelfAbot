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
SelfAbot abot;

void setup() {
    Serial.begin(9600);
    abot.servoAttachPins(11, 10);
}
void loop() {
    maneuver(100, -100, 200); 
    delay(2000);
}

void maneuver(int speedLeft, int speedRight, int msTime) {
    abot.servoSpeed(speedLeft, speedRight);
    if (msTime == -1) {
        // Indefinite operation, servos remain engaged
    } else {
        delay(msTime);
    }
}