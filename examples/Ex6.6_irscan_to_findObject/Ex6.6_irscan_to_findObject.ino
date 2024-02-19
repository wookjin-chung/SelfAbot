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
float factor = 10.5;

void setup() {
    abot.setup();
    abot.servoAttachPins(13, 12);

    byte irLeftled = 9;
    byte irLeftreceiver = 10;
    byte irRightled = 2;
    byte irRightreceiver = 3;

    int distance = 10;
    int directionOfdistance = 0;

    for (int angle = 0; angle <= 180; angle += 10) {
        rotateRobot(10);

        int irDistLeft = abot.irDistance(irLeftled, irLeftreceiver);
        int irDistRight = abot.irDistance(irRightled, irRightreceiver);
        int averageDistance = (irDistLeft + irDistRight) / 2;

        if (averageDistance < distance) {
            distance = averageDistance;
            directionOfdistance = angle;
        }
        delay(100);
    }
    // Set robot's direction to the direction of max distance
    setTravelDirection(directionOfdistance);
}

void loop() {
}

void rotateRobot(int angle) {
  int duration = 0;
  if (angle >= 0) {
    duration = (int)(angle * factor);
    abot.servoSpeed(40, 40);
    delay(duration);
    abot.servoSpeed(0, 0);
  } else {   // reverse rotate
    duration = (int)(abs(angle) * factor);
    abot.servoSpeed(-40, -40);
    delay(duration);
    abot.servoSpeed(0, 0);
  }
}

void setTravelDirection(int angle) {
    // Rotate the robot to the desired direction
    rotateRobot(angle-180);
}