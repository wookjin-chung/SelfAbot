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
#include "EnhancedSelfAbot.h"

EnhancedSelfAbot::EnhancedSelfAbot() : SelfAbot(), _currentLeftSpeed(0), _currentRightSpeed(0), _deviationFactor(0.0), _detectionCount(0) {}

EnhancedSelfAbot::EnhancedSelfAbot(byte servoLeftPin, byte servoRightPin) 
        : SelfAbot(servoLeftPin, servoRightPin), _currentLeftSpeed(0), _currentRightSpeed(0), _deviationFactor(0.0) {
			servoAttachPins(servoLeftPin, servoRightPin);
		}

EnhancedSelfAbot::EnhancedSelfAbot(unsigned int maxDistance, unsigned int safeDistance, int angularRange)
: SelfAbot(), _maxDistance(maxDistance), _safeDistance(safeDistance), _notDetectedAngularRange(angularRange) {
		}

void EnhancedSelfAbot::driveStraight(int leftSpeed, int rightSpeed) {
        // Apply normalization to calculate correction coefficients
        float leftCoefficient = 1.0 + _deviationFactor;  // Increase for left servo
        float rightCoefficient = 1.0 - _deviationFactor; // Decrease for right servo

        int adjustedLeftSpeed = leftSpeed * leftCoefficient;
        int adjustedRightSpeed = rightSpeed * rightCoefficient;
        this->servoSpeed(adjustedLeftSpeed, adjustedRightSpeed);
}

void EnhancedSelfAbot::calibratedeviationFactor(float deviatedistance) {
	if (deviatedistance != 0) {
		float K = 0.005;
		_deviationFactor += K * (float)deviatedistance;
	} else {
		// blank
	}
}

void EnhancedSelfAbot::resetDeviationFactor() {
        _deviationFactor = 0;
    }

float EnhancedSelfAbot::getDeviationFactor() const {
        return _deviationFactor;
    }
    
void EnhancedSelfAbot::setDeviationFactor(float deviationFactor) {
        _deviationFactor = deviationFactor;
    }

// non-blocking code type
void EnhancedSelfAbot::gradualServoSpeed(int targetLeftSpeed, int targetRightSpeed) {
    int step = 20;
    unsigned long lastUpdateMillis = 0; // No longer static, as we'll manage timing in this function
    unsigned long currentMillis;
    bool targetReached = false; // Flag to track if target speed is reached

    while (!targetReached) {
        currentMillis = millis();

        // Check if 2ms have passed since the last update
        if (currentMillis - lastUpdateMillis >= 2) {
            lastUpdateMillis = currentMillis; // Update the last update time

            // Adjust left speed
            if (abs(_currentLeftSpeed - targetLeftSpeed) < step) {
                _currentLeftSpeed = targetLeftSpeed; // Directly set to target if difference is smaller than step
            } else {
                if (_currentLeftSpeed < targetLeftSpeed) {
                    _currentLeftSpeed += step;
                } else if (_currentLeftSpeed > targetLeftSpeed) {
                    _currentLeftSpeed -= step;
                }
            }

            // Adjust right speed
            if (abs(_currentRightSpeed - targetRightSpeed) < step) {
                _currentRightSpeed = targetRightSpeed; // Directly set to target if difference is smaller than step
            } else {
                if (_currentRightSpeed < targetRightSpeed) {
                    _currentRightSpeed += step;
                } else if (_currentRightSpeed > targetRightSpeed) {
                    _currentRightSpeed -= step;
                }
            }

            // Ensure the speeds don't overshoot the target speeds
            _currentLeftSpeed = constrain(_currentLeftSpeed, min(_currentLeftSpeed, targetLeftSpeed), max(_currentLeftSpeed, targetLeftSpeed));
            _currentRightSpeed = constrain(_currentRightSpeed, min(_currentRightSpeed, targetRightSpeed), max(_currentRightSpeed, targetRightSpeed));

            // Update servo speeds
            this->driveStraight(_currentLeftSpeed, _currentRightSpeed);

            // Check if target speeds are reached
            if (_currentLeftSpeed == targetLeftSpeed && _currentRightSpeed == targetRightSpeed) {
                targetReached = true; // Set flag to exit loop
            }
        }
        
        delay(2); // Small delay to prevent overloading the CPU
    }
}

void EnhancedSelfAbot::lightFollowing(unsigned long leftrcTime, unsigned long rightrcTime) {
    if (leftrcTime + rightrcTime == 0) {
        this->servoSpeed(0, 0); 
        return;
    }
	
	float ndShade = (float)leftrcTime / (leftrcTime + rightrcTime) - 0.5;
    int leftSpeed, rightSpeed;

    if (ndShade < 0.0) {
        leftSpeed = int(200.0 + (ndShade * 1000.0));
        leftSpeed = constrain(leftSpeed, -200, 200);
        rightSpeed = 200;
    } else {
        rightSpeed = int(200.0 - (ndShade * 1000.0));
        rightSpeed = constrain(rightSpeed, -200, 200);
        leftSpeed = 200;
    }

    this->driveStraight(leftSpeed, -rightSpeed);   
    delay(20);
}

void EnhancedSelfAbot::irNavigationdriving(int irLeft, int irRight) {
	int combinedState = (irLeft << 1) | irRight; 

    switch (combinedState) {
        case 0: // Both sensors detect no obstacle
        	this->driveStraight(-100, 100);
            delay(1000);
            this->driveStraight(100, 0);
            delay(800);
            break;
        case 1: // irLeft = 0, irRight = 1
        	this->driveStraight(-100, 100);
        	delay(800);
            this->driveStraight(100, 0);
            delay(400);
            break;
        case 2: // irLeft = 1, irRight = 0
        	this->driveStraight(-100, 100);
        	delay(800);
            this->driveStraight(0, -100);
            delay(400);
            break;
        case 3: // Both sensors detect an obstacle
            this->driveStraight(100, -100);
            break;
    }
    delay(20);
}

void EnhancedSelfAbot::rotateAbot(int angle) {
	int duration;
    
    if (angle >= 0) { // Clockwise rotation
        duration = (int)(angle * _setanglefactorCW);
        this->driveStraight(40, 40);
    } else { // Counter-clockwise rotation
        duration = (int)(abs(angle) * _setanglefactorCCW);
        this->driveStraight(-40, -40);
    }
    
    delay(duration);
    this->servoSpeed(0, 0);
}

void EnhancedSelfAbot::calibrateRotation(int duration, bool clockwise) {
	// Initialize calibration factors to 0 at the beginning of each calibration
    _setanglefactorCW = 0;
    _setanglefactorCCW = 0;

    unsigned long startTime = millis();
    
    if (clockwise) {
        this->driveStraight(40, 40); // Clockwise rotation
    } else {
        this->driveStraight(-40, -40); // Counter-clockwise rotation
    }

    delay(duration);
    this->servoSpeed(0, 0);
    unsigned long endTime = millis();
    unsigned long timeTaken = endTime - startTime;
    
    if (clockwise) {
        _setanglefactorCW = timeTaken / 360.0; // Calibrate for clockwise rotation
    } else {
        _setanglefactorCCW = timeTaken / 360.0; // Calibrate for counter-clockwise rotation
    }
}

// Setters
void EnhancedSelfAbot::setAngleFactorCW(float angleFactorCW) {
    _setanglefactorCW = angleFactorCW;
}

void EnhancedSelfAbot::setAngleFactorCCW(float angleFactorCCW) {
    _setanglefactorCCW = angleFactorCCW;
}

// Getters
float EnhancedSelfAbot::getAngleFactorCW() const {
    return _setanglefactorCW;
}

float EnhancedSelfAbot::getAngleFactorCCW() const {
    return _setanglefactorCCW;
}

void EnhancedSelfAbot::setUltrasonicSensorPin(byte triggerPin, byte echoPin) {
    _triggerPin = triggerPin;
    _echoPin = echoPin;
}

int EnhancedSelfAbot::calculateDistance() {
	this->pulseOut(_triggerPin, 5);
    unsigned long duration = this->pulseIn(_echoPin, HIGH);
 
    float distanceCm = (float)duration * 0.034/2;
    return (int)distanceCm;
}

void EnhancedSelfAbot::ultrasonicRadarData() {
	int distance;
	
	for (int i = 0; i <= 180 ; i++) {
        this->servoAngle(i);
        delay(30);
        distance = this->calculateDistance();

        Serial.print(i);
        Serial.print(",");
        Serial.print(distance);
        Serial.print(".");
    }

    for (int i = 180; i > 0 ; i--) {
        this->servoAngle(i);
        delay(30);
        distance = this->calculateDistance();

        Serial.print(i);
        Serial.print(",");
        Serial.print(distance);
        Serial.print(".");
    }
}

void EnhancedSelfAbot::detectAndProcessSafeArea() {
  bool isDescending = false; // true for 10 to 170, false for 170 to 10

  while(true) {
    _detectionCount = 0; // Reset detection count at the start of each detection cycle
    if (!isDescending) {
      // Scan from 10 to 180 degrees
      for(int angle = 0; angle <= 180; angle += 5) {
        if (this->scanAndProcessAngle(angle, isDescending)) return; // If a safe area is found, exit
      }
    } else {
      // Scan from 180 to 10 degrees
      for(int angle = 180; angle >= 0; angle -= 5) {
        if (this->scanAndProcessAngle(angle, isDescending)) return; // If a safe area is found, exit
      }
    }

    // If no safe area was found in the current scan direction, switch direction for the next scan
    isDescending = !isDescending;
    Serial.println("Switching scan direction.");
  }
}

bool EnhancedSelfAbot::scanAndProcessAngle(int angle, bool isDescending) {
  this->servoAngle(angle);
  delay(25); // Allow time for the servo to move and stabilize
  int distance = this->calculateDistance();

  if (_detectionCount < MAX_DETECTIONS) {
    _detections[_detectionCount++] = {angle, (unsigned int)distance};
  }

  // Now pass the isDescending flag to findSafeAreaCenterAngle to consider the scan direction
  int safeAreaCenterAngle = this->findSafeAreaCenterAngle(isDescending);
  if(safeAreaCenterAngle != -1) {
    this->setTravelDirection(safeAreaCenterAngle);

    Serial.print("Safe area found at angle: ");
    Serial.println(safeAreaCenterAngle);
    return true;
  }

  return false;
}

int EnhancedSelfAbot::findSafeAreaCenterAngle(bool isDescending) {
  int maxAngleWidth = 0;
  int bestSafeAreaCenter = -1;
  
  // DB의 높은 위치에서 낮은 위치로 검사하는 로직 추가
  if (isDescending) {
    for (int i = _detectionCount - 1; i >= 0; i--) {
      if (_detections[i].distance > _safeDistance) {
        int safeAreaStart = _detections[i].angle;
        int safeAreaEnd = _detections[i].angle;
        
        while (i > 0 && _detections[i-1].distance > _safeDistance) {
          safeAreaStart = _detections[i-1].angle;
          --i;
        }

        int currentWidth = abs(safeAreaEnd - safeAreaStart);
        if (currentWidth >= _notDetectedAngularRange && currentWidth > maxAngleWidth) {
          maxAngleWidth = currentWidth;
          bestSafeAreaCenter = (safeAreaStart + safeAreaEnd) / 2;
        }
        // 한 영역을 처리했으므로 루프를 계속 진행하지 않고 다음 영역으로 넘어감
      }
    }
  } else {
    // 원래 로직: DB의 낮은 위치에서 높은 위치로 검사
    for(int i = 0; i < _detectionCount; i++) {
      if(_detections[i].distance > _safeDistance) {
        int safeAreaStart = _detections[i].angle;
        int safeAreaEnd = _detections[i].angle;

        while(i < _detectionCount - 1 && _detections[i+1].distance > _safeDistance) {
          safeAreaEnd = _detections[i+1].angle;
          ++i;
        }

        int currentWidth = abs(safeAreaEnd - safeAreaStart);
        if(currentWidth >= _notDetectedAngularRange && currentWidth > maxAngleWidth) {
          maxAngleWidth = currentWidth;
          bestSafeAreaCenter = (safeAreaStart + safeAreaEnd) / 2;
        }
      }
    }
  }

  return bestSafeAreaCenter;
}

void EnhancedSelfAbot::setTravelDirection(int angle) {
  //int currentAngle = abot.getCurrentAngle(); 
  int currentAngle = 90;
  int requiredRotation = currentAngle - angle; // standard servo angle 0 degree is right side

  if (requiredRotation > 180) {
    requiredRotation -= 360;
  } else if (requiredRotation < -180) {
    requiredRotation += 360;
  }

  this->rotateAbot(requiredRotation);
}

