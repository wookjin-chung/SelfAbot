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

int duration = 3950;

void setup() {
    Serial.begin(9600); // Start serial communication for debugging
    abot.setup();
    abot.servoAttachPins(13, 12); // Replace with actual servo pins

    bool isClockwise = true; // Set this to true for clockwise, false for counterclockwise
    abot.calibrateRotation(duration, isClockwise); 
    
    // Get and display the appropriate _setanglefactor value based on the direction
    if (isClockwise) {
        float setanglefactorCW = abot.getAngleFactorCW();
        Serial.print("_setanglefactorCW clockwise value : ");
        Serial.println(setanglefactorCW);
    } else {
        float setanglefactorCCW = abot.getAngleFactorCCW();
        Serial.print("_setanglefactorCCW counterclockwise value : ");
        Serial.println(setanglefactorCCW);
    }
}

void loop() {

}
