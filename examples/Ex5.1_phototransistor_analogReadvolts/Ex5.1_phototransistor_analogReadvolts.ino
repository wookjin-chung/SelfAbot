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

//#include "SelfAbot.h"
//SelfAbot abot;
int sensorPin = A2;

void setup() {
  //  abot.setup();
    Serial.begin(9600);
}
void loop() {
    Serial.print("A2 = ");  
    Serial.print(volts(A2)); 
    Serial.println(" volts"); 
    delay(1000);
}
float volts(int adpin)         // Measures volts at adPin
{                            // Returns floating point voltage
  return float(analogRead(adpin)) * 5.0 / 1024.0;
} 