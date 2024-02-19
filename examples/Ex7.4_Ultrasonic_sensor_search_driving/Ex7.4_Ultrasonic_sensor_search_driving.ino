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

#define TRIGGER_PIN  7 
#define ECHO_PIN     7 
#define MAX_DISTANCE 200 // max distance (cm)
#define SAFE_DISTANCE 20 // safe distance (cm)
#define MAX_DETECTIONS 40 

#define INVALID_PIN 255
const byte servoLeftPin = INVALID_PIN;
const byte servoRightPin = INVALID_PIN;

SelfAbot abot(servoLeftPin, servoRightPin);
float factor = 10.5;

struct Detection {
  int angle;
  unsigned int distance;
};

Detection detections[MAX_DETECTIONS];
int detectionCount = 0;
int notdetectedAngularrange = 40; // 장애물이 존재하지 않는 최소한의 각도범위

void setup() {
  Serial.begin(9600);
  abot.setup();
  abot.servoAttachPins(13, 12);
  abot.servoAttachAngle(10);
}

void loop() {
  int distance = calculateDistance();

  if(distance > 0 && distance <= SAFE_DISTANCE) {
    abot.servoSpeed(0, 0);

    detectionCount = 0;
    for(int angle = 0; angle <= 180; angle += 5) { 
      abot.servoAngle(angle);
      delay(500);
      distance = calculateDistance();

      if (detectionCount < MAX_DETECTIONS) {
        detections[detectionCount].angle = angle;
        detections[detectionCount].distance = distance;
        detectionCount++;

        Serial.print("Object detected at angle: ");
        Serial.print(angle);
        Serial.print(" with distance: ");
        Serial.println(distance);
      }
    }
    if (isSafeAreaDetected()) {
      // Get safe area center angle
      int safeAreaCenterAngle = getSafeAreaCenterAngle();
      Serial.print("safeangle : ");
      Serial.println(safeAreaCenterAngle);

      if(safeAreaCenterAngle != -1) {
        setTravelDirection(safeAreaCenterAngle);

        Serial.print("Safe area center angle: ");
        Serial.println(safeAreaCenterAngle);
      } else {
        Serial.println("No safe area detected.");
      }
      alignSensorToFront();
    }
  } else {
    abot.servoSpeed(100, -100);
  }
}

int calculateDistance() {
    abot.pulseOut(TRIGGER_PIN, 5);
    unsigned long duration = abot.pulseIn(ECHO_PIN, HIGH);
 
    int distanceCm = (int)duration * 0.034 / 2;
    return distanceCm;
}

bool isSafeAreaDetected() {
  // getSafeAreaCenterAngle() 함수를 호출하여 결과를 확인합니다.
  int centerAngle = getSafeAreaCenterAngle();
  // centerAngle 값이 -1이 아니면, 안전한 영역이 감지된 것입니다.
  return centerAngle != -1;
}

int getSafeAreaCenterAngle() {
  int maxAngleWidth = 0; // 가장 넓은 각도 구간의 폭
  int safeAreaStartAngle = -1; // 장애물이 없는 영역의 시작 각도
  int safeAreaEndAngle = -1; // 장애물이 없는 영역의 끝 각도
  int bestSafeAreaCenter = -1; // 최적의 안전한 영역의 중심 각도

  // Find the widest safe area that is at least 40 degrees wide
  for(int i = 0; i < detectionCount; i++) {
    if(detections[i].distance > SAFE_DISTANCE) {
      int safeAreaStart = detections[i].angle; // 현재 장애물이 없는 영역의 시작 각도
      int safeAreaEnd = detections[i].angle; // 현재 장애물이 없는 영역의 끝 각도

      // 장애물이 없는 영역의 끝 각도를 찾기 위해 연속적으로 장애물이 없는 영역을 확인합니다.
      while(i < detectionCount - 1 && detections[i+1].distance > SAFE_DISTANCE) {
        safeAreaEnd = detections[i+1].angle;
        i++;
      }

      // 현재 장애물이 없는 영역의 폭을 계산합니다.
      int currentWidth = safeAreaEnd - safeAreaStart;

      // 현재까지 찾은 영역 중 조건이상의 가장 넓은 장애물이 없는 영역을 찾습니다.
      if(currentWidth >= notdetectedAngularrange && currentWidth > maxAngleWidth) {
        maxAngleWidth = currentWidth;
        safeAreaStartAngle = safeAreaStart;
        safeAreaEndAngle = safeAreaEnd;
        bestSafeAreaCenter = (safeAreaStartAngle + safeAreaEndAngle) / 2; // 영역의 중심 각도 업데이트
      }
    }
  }

  // 최적의 안전한 영역의 중심 각도를 반환합니다. 장애물이 없는 영역을 찾지 못한 경우 -1을 반환합니다.
  return bestSafeAreaCenter;
}

void rotateRobot(int angle) {
  int duration = abs(angle);

  if (angle >= 0) {  // forward rotate
    abot.servoSpeed(40, 40);
  } else {   // reverse rotate
    abot.servoSpeed(-40, -40);
  }
  delay(duration * factor);
  abot.servoSpeed(0, 0);
}

void setTravelDirection(int angle) {
  //int currentAngle = abot.getCurrentAngle(); 
  int currentAngle = 90;
  int requiredRotation = currentAngle - angle; // standard servo angle 0 degree is right side

  if (requiredRotation > 180) {
    requiredRotation -= 360;
  } else if (requiredRotation < -180) {
    requiredRotation += 360;
  }

  rotateRobot(requiredRotation);
}

void alignSensorToFront() {
  abot.servoAngle(90); 
  delay(1000); 
  Serial.println("Sensor aligned to front.");
}
