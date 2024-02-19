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
#ifndef ENHANCEDSELFABOT_H
#define ENHANCEDSELFABOT_H

#include "SelfAbot.h" // Include the base class header
#include "Arduino.h"
#include <Servo.h> 

struct Detection {
  int angle;
  unsigned int distance;
};

class EnhancedSelfAbot : public SelfAbot {
public:
    EnhancedSelfAbot();
    EnhancedSelfAbot(byte servoLeftPin, byte servoRightPin);
    EnhancedSelfAbot(unsigned int maxDistance, unsigned int safeDistance, int angularRange);

	static const int MAX_DETECTIONS = 40;

	void resetDeviationFactor();
	float getDeviationFactor() const;
	void setDeviationFactor(float deviationFactor);
	void calibratedeviationFactor(float deviatedistance);
	
	void driveStraight(int leftSpeed, int rightSpeed);
    void gradualServoSpeed(int targetLeftSpeed, int targetRightSpeed);
    void lightFollowing(unsigned long leftrcTime, unsigned long rightrcTime);
    void irNavigationdriving(int irLeft, int irRight);

    void rotateAbot(int angle);
    void calibrateRotation(int duration, bool clockwise);
    
    // Setters
    void setAngleFactorCW(float angleFactorCW);
    void setAngleFactorCCW(float angleFactorCCW);

    // Getters
    float getAngleFactorCW() const;
    float getAngleFactorCCW() const;
    
    void setUltrasonicSensorPin(byte triggerPin, byte echoPin);
    int calculateDistance();
    void ultrasonicRadarData();
    
    void detectAndProcessSafeArea();
    bool scanAndProcessAngle(int angle, bool isDescending);
    int findSafeAreaCenterAngle(bool isDescending);
    void setTravelDirection(int angle);
    
private:
	float _deviationFactor;
	float _setanglefactorCW, _setanglefactorCCW;
	int _currentLeftSpeed;   // Current speed for left servo as a class member
    int _currentRightSpeed;  // Current speed for right servo as a class member
    
    Detection _detections[MAX_DETECTIONS];
    int _detectionCount;
    int _notDetectedAngularRange;
    
    byte _triggerPin, _echoPin;
    unsigned int _maxDistance;  
    unsigned int _safeDistance;  
};

#endif // ENHANCEDSELFABOT_H
