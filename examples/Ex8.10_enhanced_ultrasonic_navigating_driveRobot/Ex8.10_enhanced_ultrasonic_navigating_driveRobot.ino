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

#define SAFE_DISTANCE 20 // safe distance (cm)
#define INVALID_PIN 255
const byte servoLeftPin = INVALID_PIN;
const byte servoRightPin = INVALID_PIN;

EnhancedSelfAbot abot(200, 20, 40);

void setup() {
    Serial.begin(9600);
    abot.setup();
    abot.servoAttachPins(13, 12); // Replace with actual servo pins
    abot.servoAttachAngle(10);

    abot.setUltrasonicSensorPin(7, 7);

    abot.setDeviationFactor(-0.05);
    abot.setAngleFactorCW(10.97);
    abot.setAngleFactorCCW(12.22);
}

void loop() {
  abot.gradualServoSpeed(80, -80); // 로봇 전진 시작

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

    int distance = abot.calculateDistance(); // 현재 각도에서의 거리 측정

    if(distance <= SAFE_DISTANCE) {
      abot.gradualServoSpeed(20, -20); // 장애물이 감지되면 로봇 정지
      abot.detectAndProcessSafeArea(); // 상세 탐색 및 회피 동작 수행
      abot.gradualServoSpeed(80, -80); // 회피 동작 후 다시 전진
      break; // 하나라도 조건을 만족하면 더 이상의 감지는 필요 없으므로 반복문 탈출
    }
  }
}
