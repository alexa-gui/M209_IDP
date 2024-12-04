#include <Adafruit_MotorShield.h>
#include "line_follower.h"
#include "motor_control.h"
#include "tof_sensor.h"
#include "led_flash.h"

extern int photo;
extern uint32_t hysteris_time;
#define TIME_THRESHOLD 5000

bool findBox() {
	adjSpeed(165);
  uint32_t tm = millis();
  Serial.println("wall section start");
  while(!digitalRead(photo)) {
	  ledFlash();
    followLine();
    if(millis()-tm > TIME_THRESHOLD)
      goto over_threshold;
  }
  Serial.println("wall section end");

  adjSpeed(165);

  while(digitalRead(photo)) {
	  ledFlash();
    followLine();
    if(millis()-tm > TIME_THRESHOLD)
      goto over_threshold;
  }
  Serial.println("box found");
  
  Serial.println(millis() - tm);
  if(millis() - tm > TIME_THRESHOLD){
    over_threshold:
    Serial.println("exceeded box finding threshold time");
    adjSpeed(255);
    return false;
  }
  uint32_t startTime = millis();
  while(millis() - startTime < 1200) {
	  ledFlash();
    followLine();
  }

  stop();
  return true;
}

bool collectBox() {
	adjSpeed(255);

  while(!digitalRead(R2)) {
	  ledFlash();
    adjRight();
  }
  stop();
  while(!digitalRead(L2)) {
	  ledFlash();
    adjSlightLeftReverse();
  }
  while(!digitalRead(R2)) {
	  ledFlash();
    adjSlightRightReverse();
  }
  hysteris_time = millis();
  stop();
  bool gotBox = false;
  uint32_t t = millis();
  forward();
  while(millis() - t < 2100) {
    if(getDistanceReading() == FLAT) {
      stop();
      pickUpBox();
      gotBox = true;
      break;
    }
  }
  stop();
  backOutTillIntersection();
  return gotBox;
}
