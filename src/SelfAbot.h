/**
 * SelfAbot Library Code
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
#ifndef SELFABOT_H
#define SELFABOT_H

#include "Arduino.h"
#include <Servo.h>

class SelfAbot {
public:
	SelfAbot();
	SelfAbot(byte servoLeftPin, byte servoRightPin);
	SelfAbot& operator()(byte pin);
	SelfAbot& operator()(byte leftPin, byte rightPin);

	void setup();

	void digitalWrite(byte pin, byte value);
	void digitalWrite(byte value);
	void analogWrite(byte pin, int value);
	void analogWrite(int value);
	int digitalRead(byte pin);
	int digitalRead();
	void tone(byte pin, unsigned int frequency, unsigned long duration);
	void tone(unsigned int frequency, unsigned long duration);

	void servoAttachAngle(byte servoAnglePin); 
	void servoAttachPins(byte servoLeftPin, byte servoRightPin); 

	void servoAngle(int angle);
	void servoSpeed(int speed);
	void servoSpeed(int leftSpeed, int rightSpeed);
	void servoSpeedNonoverload(int leftSpeed, int rightSpeed);
	void detachServos();

	int irDetect(byte irLedPin, byte irReceiverPin, int frequency);
	int irDistance(byte irLedPin, byte irReceivePin);

	void pulseOut(byte pin, unsigned long duration);
	unsigned long pulseIn(byte pin, int state);
	unsigned long pulseCount(byte pin, unsigned long duration);

    unsigned long rcTime(byte pin);

private:
	Servo _servoAngle, _servoLeft, _servoRight; 
	byte _servoAnglePin, _servoLeftPin, _servoRightPin;
	byte _selectedPin;

	byte _irLedPin;
    byte _irReceiverPin;
    byte _lastReadValue_ir;
};

#endif  // SELFABOT_H
