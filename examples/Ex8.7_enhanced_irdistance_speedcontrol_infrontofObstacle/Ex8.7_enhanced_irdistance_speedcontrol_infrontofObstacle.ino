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
    Serial.begin(9600);
    abot.setup();
    abot.servoAttachPins(13, 12); // Replace with actual servo pins

    abot.setDeviationFactor(-0.05);
}

void loop() {
    byte irLeftled = 9;
    byte irLeftreceiver = 10;
    byte irRightled = 2;
    byte irRightreceiver = 3;
    
    int irDistLeft = abot.irDistance(irLeftled, irLeftreceiver); 
    int irDistRight = abot.irDistance(irRightled, irRightreceiver); 

    int totalIRValue = irDistLeft + irDistRight;

    Serial.print("Left IR: ");
    Serial.print(irDistLeft);
    Serial.print(" || Right IR: ");
    Serial.println(irDistRight);
    delay(50);

    if (totalIRValue > 9) {
        // If the total IR value is more than 9, run the robot forward normally
        abot.gradualServoSpeed(100, -100);
    } else if (totalIRValue >= 1 && totalIRValue <= 9) {
        // If the total IR value is between 5 and 9, reduce the speed gradually
        // Adjust the speed reduction factor as per your requirement
        int speed = map(totalIRValue, 1, 9, 0, 100);
        abot.gradualServoSpeed(speed, -speed);
    } else {
        // If the total IR value is less than 5, stop the robot
        abot.servoSpeed(0, 0);
    }

    delay(20);
}
