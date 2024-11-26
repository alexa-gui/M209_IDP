#include <Adafruit_MotorShield.h>
#include "line_follower.h"
#include "motor_control.h"
#include "tof_sensor.h"
#include "led_flash.h"

extern int photo;
extern uint32_t hysteris_time;
#define TIME_THRESHOLD 4800
bool findBox() {
	adjSpeed(150);
  uint32_t tm = millis();
  Serial.println("wall section start");
  while(!digitalRead(photo)) {
	ledFlash();
    followLine();
  }
  Serial.println("wall section end");

  adjSpeed(150);

  while(digitalRead(photo)) {
	  ledFlash();
    followLine();
  }
  Serial.println("box found");

  Serial.println(millis() - tm);
  if(millis() - tm > TIME_THRESHOLD){
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

void faceBox() {
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
  hysteris_time = millis();
  stop();
}
