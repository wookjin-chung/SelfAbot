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
const byte servoPin = 10;
const byte pingPin = 7; // sensor trigger/echo pin
int distance;

void setup() {
    abot.setup();
    abot.servoAttachAngle(servoPin);
    Serial.begin(9600);
}

void loop() {
    for (int i = 0; i <= 180 ; i++) {
        abot.servoAngle(i);
        delay(30);
        distance = calculateDistance();

        Serial.print(i);
        Serial.print(",");
        Serial.print(distance);
        Serial.print(".");
    }
    
    for (int i = 180; i > 0 ; i--) {
        abot.servoAngle(i);
        delay(30);
        distance = calculateDistance();

        Serial.print(i);
        Serial.print(",");
        Serial.print(distance);
        Serial.print(".");
    }
}

int calculateDistance(){ 
    abot.pulseOut(pingPin, 5);
    unsigned long duration = abot.pulseIn(pingPin, HIGH);
 
    int distanceCm = (int)duration * 0.034/2;
    return distanceCm;
}
