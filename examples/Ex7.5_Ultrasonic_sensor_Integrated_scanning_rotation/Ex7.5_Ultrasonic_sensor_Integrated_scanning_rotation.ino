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
int notdetectedAngularrange = 40; // 장애물이 존재하지 않는 최소한의 각도범위 40도

void setup() {
  Serial.begin(9600);
  abot.setup();
  abot.servoAttachPins(13, 12);
  abot.servoAttachAngle(10);
}

void loop() {
  abot.servoSpeed(100, -100); // 로봇 전진 시작

  // 스캔 방향을 변경하지 않고, 단일 반복문으로 처리
  scanInDirection(-30, 30); // -30도에서 30도까지 스캔
  delay(100); // 스캔 방향 변경 전 대기
  scanInDirection(30, -30); // 30도에서 -30도까지 스캔

  delay(100); // 루프의 반복 속도 조절을 위한 딜레이
}

void scanInDirection(int startOffset, int endOffset) {
  int step = startOffset < endOffset ? 15 : -15; // 스캔 방향 결정

  for(int offset = startOffset; step > 0 ? offset <= endOffset : offset >= endOffset; offset += step) {
    abot.servoAngle(90 + offset); // 서보 모터를 해당 각도로 조정
    delay(30); // 서보 모터가 이동하고 안정화되는데 필요한 시간

    int distance = calculateDistance(); // 현재 각도에서의 거리 측정

    if(distance <= SAFE_DISTANCE) {
      abot.servoSpeed(0, 0); // 장애물이 감지되면 로봇 정지
      detectAndProcessSafeArea(); // 상세 탐색 및 회피 동작 수행
      abot.servoSpeed(100, -100); // 회피 동작 후 다시 전진
      break; // 하나라도 조건을 만족하면 더 이상의 감지는 필요 없으므로 반복문 탈출
    }
  }
}

int calculateDistance() {
  abot.pulseOut(TRIGGER_PIN, 5);
  unsigned long duration = abot.pulseIn(ECHO_PIN, HIGH);

  return (int)(duration * 0.034 / 2);
}

void detectAndProcessSafeArea() {
  bool isDescending = false; // true for 10 to 170, false for 170 to 10

  while(true) {
    detectionCount = 0; // Reset detection count at the start of each detection cycle
    if (!isDescending) {
      // Scan from 10 to 180 degrees
      for(int angle = 0; angle <= 180; angle += 5) {
        if (scanAndProcessAngle(angle, isDescending)) return; // If a safe area is found, exit
      }
    } else {
      // Scan from 180 to 10 degrees
      for(int angle = 180; angle >= 0; angle -= 5) {
        if (scanAndProcessAngle(angle, isDescending)) return; // If a safe area is found, exit
      }
    }

    // If no safe area was found in the current scan direction, switch direction for the next scan
    isDescending = !isDescending;
    Serial.println("Switching scan direction.");
  }
}

bool scanAndProcessAngle(int angle, bool isDescending) {
  abot.servoAngle(angle);
  delay(25); // Allow time for the servo to move and stabilize
  int distance = calculateDistance();

  if (detectionCount < MAX_DETECTIONS) {
    detections[detectionCount++] = {angle, (unsigned int)distance};
  }

  // Now pass the isDescending flag to findSafeAreaCenterAngle to consider the scan direction
  int safeAreaCenterAngle = findSafeAreaCenterAngle(isDescending);
  if(safeAreaCenterAngle != -1) {
    setTravelDirection(safeAreaCenterAngle);

    Serial.print("Safe area found at angle: ");
    Serial.println(safeAreaCenterAngle);
    return true;
  }

  return false;
}

int findSafeAreaCenterAngle(bool isDescending) {
  int maxAngleWidth = 0;
  int bestSafeAreaCenter = -1;
  
  // DB의 높은 위치에서 낮은 위치로 검사하는 로직 추가
  if (isDescending) {
    for (int i = detectionCount - 1; i >= 0; i--) {
      if (detections[i].distance > SAFE_DISTANCE) {
        int safeAreaStart = detections[i].angle;
        int safeAreaEnd = detections[i].angle;
        
        while (i > 0 && detections[i-1].distance > SAFE_DISTANCE) {
          safeAreaStart = detections[i-1].angle;
          --i;
        }

        int currentWidth = abs(safeAreaEnd - safeAreaStart);
        if (currentWidth >= notdetectedAngularrange && currentWidth > maxAngleWidth) {
          maxAngleWidth = currentWidth;
          bestSafeAreaCenter = (safeAreaStart + safeAreaEnd) / 2;
        }
        // 한 영역을 처리했으므로 루프를 계속 진행하지 않고 다음 영역으로 넘어감
      }
    }
  } else {
    // 원래 로직: DB의 낮은 위치에서 높은 위치로 검사
    for(int i = 0; i < detectionCount; i++) {
      if(detections[i].distance > SAFE_DISTANCE) {
        int safeAreaStart = detections[i].angle;
        int safeAreaEnd = detections[i].angle;

        while(i < detectionCount - 1 && detections[i+1].distance > SAFE_DISTANCE) {
          safeAreaEnd = detections[i+1].angle;
          ++i;
        }

        int currentWidth = abs(safeAreaEnd - safeAreaStart);
        if(currentWidth >= notdetectedAngularrange && currentWidth > maxAngleWidth) {
          maxAngleWidth = currentWidth;
          bestSafeAreaCenter = (safeAreaStart + safeAreaEnd) / 2;
        }
      }
    }
  }

  return bestSafeAreaCenter;
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
