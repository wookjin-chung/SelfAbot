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
  //  abot.setup();
    Serial.begin(9600);
}
void loop() {
    float rctimeValLeft = float(abot.rcTime(8)); 
    float rctimeValRight = float(abot.rcTime(6)); 

    float ndShade;
    ndShade = rctimeValLeft / (rctimeValLeft + rctimeValRight) - 0.5;
    for(int i = 0;i < (ndShade * 40) + 20; i++) {
      Serial.print(' ');
    }
    Serial.println('*');
    delay(100);
}
