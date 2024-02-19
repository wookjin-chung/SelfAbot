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

void setup() {
    //Serial.begin(9600);
    abot.setup();
    abot.servoAttachPins(13, 12);
}

void loop() {
    int irLeft = abot.irDetect(9, 10, 38000); // left IR sensor
    int irRight = abot.irDetect(2, 3, 38000); // right IR sensor
    int combinedState = (irLeft << 1) | irRight; 

    switch (combinedState) {
        case 0: // Both sensors detect no obstacle
            abot(13, 12).servoSpeed(100, -100);
            break;
        case 1: // irLeft = 0, irRight = 1  left obstacle
            abot(13, 12).servoSpeed(-100, 100);
            delay(1000);
            abot(13, 12).servoSpeed(100, 0);
            delay(400);
            break;
        case 2: // irLeft = 1, irRight = 0  right obstacle
            abot(13, 12).servoSpeed(-100, 100);
            delay(1000);
            abot(13, 12).servoSpeed(0, -100);
            delay(400);
            break;
        case 3: // Both sensors detect an obstacle
            abot(13, 12).servoSpeed(-100, 100);
            delay(1000);
            abot(13, 12).servoSpeed(100, 0);
            delay(800);
            break;
    }
    delay(20);
}
