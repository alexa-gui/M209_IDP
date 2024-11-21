#include <Adafruit_MotorShield.h>
#include "line_follower.h"
#include "motor_control.h"
#include "tof_sensor.h"
#include "led_flash.h"

extern int photo;

void findBox() {
	adjSpeed(255);

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

  uint32_t startTime = millis();
  while(millis() - startTime < 1200) {
	  ledFlash();
    followLine();
  }

  stop();
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
  stop();
}
