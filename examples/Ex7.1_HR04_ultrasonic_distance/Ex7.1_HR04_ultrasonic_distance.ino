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
const byte triggerPin = 7; // Ultrasonic sensor trigger pin
const byte echoPin = 8;    // Ultrasonic sensor echo pin

void setup() {
    abot.setup();
    pinMode(triggerPin, OUTPUT); // Set the trigger pin as an output
    pinMode(echoPin, INPUT);     // Set the echo pin as an input
    Serial.begin(9600);
}

void loop() {
    abot.pulseOut(triggerPin, 10); // 10 microseconds pulse
    unsigned long duration = abot.pulseIn(echoPin, HIGH);

    // Calculate distance (in centimeters or inches)
    // Speed of sound = 34300 cm/s (in air), so time for there and back is duration
    // Distance = (speed of sound * time) / 2
    float distanceCm = duration * 0.0343 / 2;
    float distanceInch = duration * 0.0135 / 2;

    // Print the distance
    Serial.print("Distance: ");
    Serial.print(distanceCm);
    Serial.print(" cm, ");
    Serial.print(distanceInch);
    Serial.println(" inches");

    delay(1000); // Wait for a second before the next measurement
}
