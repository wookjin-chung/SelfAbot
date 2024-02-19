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
#include "SelfAbot.h"
#define INVALID_PIN 255 

SelfAbot::SelfAbot() {
    _selectedPin = INVALID_PIN;
}

SelfAbot::SelfAbot(byte servoLeftPin, byte servoRightPin)
    : _servoLeftPin(servoLeftPin), _servoRightPin(servoRightPin) {
    _selectedPin = INVALID_PIN;
}

SelfAbot& SelfAbot::operator()(byte pin) {
    _selectedPin = pin;
    return *this;
}

SelfAbot& SelfAbot::operator()(byte leftPin, byte rightPin) {
    _servoLeftPin = leftPin;
    _servoRightPin = rightPin;
    return *this;
}

void SelfAbot::setup() {
    if (_servoLeftPin != INVALID_PIN && _servoRightPin != INVALID_PIN) { 
        _servoLeft.attach(_servoLeftPin);
        _servoRight.attach(_servoRightPin);
    }
}

// Original method
void SelfAbot::digitalWrite(byte pin, byte value) {	
    pinMode(pin, OUTPUT);
    ::digitalWrite(pin, value); 
}
// Overloaded method
void SelfAbot::digitalWrite(byte value) {	
    if (_selectedPin != INVALID_PIN) {
        pinMode(_selectedPin, OUTPUT);
        ::digitalWrite(_selectedPin, value);
    }
}

// Original method
void SelfAbot::analogWrite(byte pin, int value) {
    ::analogWrite(pin, value);  
}
// Overloaded method
void SelfAbot::analogWrite(int value) {
    if (_selectedPin != INVALID_PIN) {
        ::analogWrite(_selectedPin, value); 
    }
}

// Original method
int SelfAbot::digitalRead(byte pin) {
    pinMode(pin, INPUT);
    return ::digitalRead(pin);
}
// Overloaded method
int SelfAbot::digitalRead() {
    if (_selectedPin != INVALID_PIN) {
        pinMode(_selectedPin, INPUT);
    	return ::digitalRead(_selectedPin);
    }
}

// Original method
void SelfAbot::tone(byte pin, unsigned int frequency, unsigned long duration) {
    ::tone(pin, frequency, duration);  
}
// Overloaded method
void SelfAbot::tone(unsigned int frequency, unsigned long duration) {
    if (_selectedPin != INVALID_PIN) {
        ::tone(_selectedPin, frequency, duration);  
    }
}

// Original method
void SelfAbot::servoAttachPins(byte servoLeftPin, byte servoRightPin) {
    if (servoLeftPin != INVALID_PIN) {
        _servoLeftPin = servoLeftPin;
        _servoLeft.attach(_servoLeftPin);
    }
    if (servoRightPin != INVALID_PIN) {
        _servoRightPin = servoRightPin;
        _servoRight.attach(_servoRightPin);
    }
}

// Original method
void SelfAbot::servoAttachAngle(byte servoAnglePin) {
	if (servoAnglePin != INVALID_PIN) {
		_servoAnglePin = servoAnglePin;
        _servoAngle.attach(_servoAnglePin);
	}
}
// Overloaded method
void SelfAbot::servoAngle(int angle) {
	if (angle >= 0 && angle <= 180) {
        _servoAngle.write(angle);
    } else {
    	Serial.println("Error: Invalid input value");
	}
}
// Overloaded method
void SelfAbot::servoSpeed(int speed) {
    if (_selectedPin == _servoLeftPin) {
        _servoLeft.writeMicroseconds(1500 + speed);
    } else if (_selectedPin == _servoRightPin) {
        _servoRight.writeMicroseconds(1500 + speed);
    }
}
// Overloaded method
void SelfAbot::servoSpeed(int leftSpeed, int rightSpeed) {
    _servoLeft.writeMicroseconds(1500 + leftSpeed);
    _servoRight.writeMicroseconds(1500 + rightSpeed);
}
// Non-Overloaded method
void SelfAbot::servoSpeedNonoverload(int leftSpeed, int rightSpeed) {
	_servoLeft.writeMicroseconds(1500 + leftSpeed);
	_servoRight.writeMicroseconds(1500 + rightSpeed);
}
// Overloaded method
void SelfAbot::detachServos() {
    _servoLeft.detach();
    _servoRight.detach();
}

// Original method
int SelfAbot::irDetect(byte irLedPin, byte irReceiverPin, int frequency) {
	_irLedPin = irLedPin;
	_irReceiverPin = irReceiverPin;
	pinMode(_irLedPin, OUTPUT);
    pinMode(_irReceiverPin, INPUT);
    tone(_irLedPin, frequency, 8);  
    delay(1);
    int _lastReadValue_ir = ::digitalRead(_irReceiverPin);
    delay(1);
    return _lastReadValue_ir;
}

// Original method
int SelfAbot::irDistance(byte irLedPin, byte irReceivePin) {
	int distance = 0;
    for(long f = 38000; f <= 42000; f += 500) {
        distance += irDetect(irLedPin, irReceivePin, f); 
    }
    return distance;
}

// Original method
void SelfAbot::pulseOut(byte pin, unsigned long duration) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delayMicroseconds(2);
    digitalWrite(pin, HIGH);
    delayMicroseconds(duration);
    digitalWrite(pin, LOW);
}

// Original method
unsigned long SelfAbot::pulseIn(byte pin, int state) {
    pinMode(pin, INPUT);
    return ::pulseIn(pin, HIGH);
}

// Original method
unsigned long SelfAbot::pulseCount(byte pin, unsigned long duration) {
    pinMode(pin, INPUT);
    unsigned long startTime = micros();
    unsigned long endTime = startTime + duration;
    unsigned long count = 0;

    while (micros() < endTime) {
        if (::digitalRead(pin) == HIGH) {
            count++;
            while (::digitalRead(pin) == HIGH);
        }
    }

    return count;
}

// Original method
unsigned long SelfAbot::rcTime(byte pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    delay(1); 
    pinMode(pin, INPUT);
    digitalWrite(pin, LOW);
    unsigned long startTime = micros();
    unsigned long elapsedTime = 0;
    while (digitalRead(pin) == HIGH) {
        elapsedTime = micros() - startTime;
    }
    return elapsedTime;
}
