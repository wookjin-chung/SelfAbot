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
#include "Arduino.h"

class SelfArduino {
public:
    SelfArduino() {}
    void setup() {}

    void digitalWrite(byte pin, byte value) {
        pinMode(pin, OUTPUT);
        ::digitalWrite(pin, value);
    }

private:
};

SelfArduino adu;
int pin = 9;
void setup() {
    //adu.setup();
}

void loop() {
    adu.digitalWrite(pin, HIGH);
    delay(1000);
    adu.digitalWrite(pin, LOW);
    delay(1000);
}
