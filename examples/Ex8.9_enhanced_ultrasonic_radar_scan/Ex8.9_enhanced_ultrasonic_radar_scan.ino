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

EnhancedSelfAbot abot; 
void setup() {
    Serial.begin(9600);
    abot.setup();
    abot.servoAttachAngle(10);
    abot.setUltrasonicSensorPin(7, 7);
}

void loop() {
    abot.ultrasonicRadarData();
    delay(2000);
}
