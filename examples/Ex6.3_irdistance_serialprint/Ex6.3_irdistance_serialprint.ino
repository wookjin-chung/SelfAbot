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
    abot.setup();
}

void loop() {
    byte irLeftled = 9;
    byte irLeftreceiver = 10;
    byte irRightled = 2;
    byte irRightreceiver = 3;
    
    int irDistLeft = abot.irDistance(irLeftled, irLeftreceiver); 
    int irDistRight = abot.irDistance(irRightled, irRightreceiver); 

    Serial.print("Left IR: ");
    Serial.print(irDistLeft);
    Serial.print(" || Right IR: ");
    Serial.println(irDistRight);
    delay(50);
}
