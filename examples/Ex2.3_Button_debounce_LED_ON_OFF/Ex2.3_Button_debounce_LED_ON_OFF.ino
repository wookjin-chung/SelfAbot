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
int ledState = HIGH;
int buttonState; 
int lastButtonState = LOW; 

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; 

void setup() {
  abot.setup();
  abot.digitalWrite(ledPin, ledState);
}
void loop() {
  int reading = abot.digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }
  abot.digitalWrite(ledPin, ledState);
  lastButtonState = reading;
}
