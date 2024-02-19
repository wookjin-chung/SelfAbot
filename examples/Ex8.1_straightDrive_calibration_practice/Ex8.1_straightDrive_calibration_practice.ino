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
    Serial.println("Calibration Practice for SelfAbot");
    Serial.println("Place the robot and press 's' to start moving.");
}

void loop() {
    if (Serial.available() > 0) {
        char command = Serial.read();
        if (command == 's') {
            performCalibration();
        }
    }
}

void performCalibration() {
    int servospeed = 40;
    int delaytime = 5000; // Time to make the robot go straight (5 seconds)
    int measuredDevidistance; // Save the measured deviation distance (unit : mm)
    unsigned long startTime = millis(); // Start time for timeout
    unsigned long timeout = 30000; // 30 second timeout

    abot.resetDeviationFactor();

    Serial.println("Going straight. Please wait...");
    abot.driveStraight(servospeed, -servospeed); // Straight
    delay(delaytime); // Go straight for the specified delay time
    abot.servoSpeed(0, 0); // Stop the robot

    Serial.println("Please measure the deviation distance and enter it (mm): ");
    delay(500); // Short delay to ensure the user sees the message

    // Clear the serial buffer to remove any unwanted or leftover data
    while (Serial.available() > 0) {
        Serial.read();
    }

    // Wait for new input
    while (Serial.available() == 0) {
        // Check if timeout has been reached
        if (millis() - startTime > timeout) {
            Serial.println("Input waiting time has expired. Please restart calibration.");
            return; // exit the function when timeout is reached
        }
        delay(100); // Small delay to prevent the loop from running too fast
    }

    measuredDevidistance = Serial.parseInt(); // Read the entered value...

    // Check for '0' input to exit without performing corrections
    if (measuredDevidistance == 0) {
        Serial.println("Exiting calibration without correction as the input is '0'.");
        return; // exit the function as '0' was entered
    }

    Serial.print("Measured deviation distance: ");
    Serial.print(measuredDevidistance);
    Serial.println("mm");

    // Convert mm to cm for calibratedeviationFactor if necessary
    float measuredDevidistanceCm = measuredDevidistance / 10.0;
    abot.calibratedeviationFactor(measuredDevidistanceCm);

    abot.driveStraight(servospeed, -servospeed); // Straight
    delay(delaytime); // Go straight for the specified delay time
    abot.servoSpeed(0, 0); // Stop the robot

    // Display the final corrected _deviationFactor value
    float finalDeviationFactor = abot.getDeviationFactor();
    Serial.print("Final corrected _deviationFactor: ");
    Serial.println(finalDeviationFactor);

    Serial.println("Calibration is complete. Test the robot's movements again.");
}