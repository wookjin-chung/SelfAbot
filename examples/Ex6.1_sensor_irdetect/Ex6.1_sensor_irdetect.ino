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
    int irLeft = abot.irDetect(9, 10, 38000); // 왼쪽 IR 센서 데이터 읽기
    int irRight = abot.irDetect(2, 3, 38000); // 오른쪽 IR 센서 데이터 읽기
    Serial.print("Left IR: ");
    Serial.print(irLeft);
    Serial.print(" || Right IR: ");
    Serial.println(irRight);
    delay(10);
}
