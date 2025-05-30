# Ultrasonic-Sensor-2

# main.cpp

#include <Arduino.h>

// 핀 정의
const int trigPin = 5;
const int echoPin = 18;

// 문 닫힘 상태에서의 기준 거리(cm)
const float DOOR_CLOSED_DISTANCE = 7.0;
const float THRESHOLD = 3.0;  // 문 열림 감지 오차 허용값

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

float measureDistance() {
  // 초음파 신호 발생
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 반사파 수신 시간 측정
  long duration = pulseIn(echoPin, HIGH, 30000);  // 30ms 제한

  // 측정 실패시 0 반환
  if (duration == 0) return 0;

  // 거리 계산: cm 단위
  float distance = duration * 0.0343 / 2;
  return distance;
}

void loop() {
  float distance = measureDistance();
  Serial.print("측정 거리: ");
  Serial.print(distance);
  Serial.println(" cm");

  // 거리 판별 로직
  if (distance == 0 || distance > (DOOR_CLOSED_DISTANCE + THRESHOLD)) {
    Serial.println("🚪 문이 열렸습니다!");
  } else {
    Serial.println("✅ 문이 닫혀 있습니다.");
  }

  delay(1000);  // 1초 간격 측정
}

# platformio.ini

[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200 
