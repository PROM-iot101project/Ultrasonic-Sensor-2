# sensor_utils.cpp (거리 측정 함수 구현하기)

#include <Arduino.h>
#include "sensor_utils.h"

float measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms 제한
  if (duration == 0) return 0;

  return duration * 0.0343 / 2.0; // cm 단위 거리 계산
} 
