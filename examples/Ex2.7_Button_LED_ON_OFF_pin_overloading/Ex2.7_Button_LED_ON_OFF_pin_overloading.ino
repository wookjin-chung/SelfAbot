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
const int buttonPin = 8; 
const int ledPin =  9;
int buttonState = 0; 

void setup() {
  //  abot.setup();
}
void loop() {
  buttonState = abot(buttonPin).digitalRead();
  if (buttonState == HIGH) {  
    abot(ledPin).digitalWrite(HIGH);
  } else {  
    abot(ledPin).digitalWrite(LOW);
  }
}
