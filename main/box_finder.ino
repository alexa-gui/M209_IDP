#include <Adafruit_MotorShield.h>
#include "line_follower.h"
#include "motor_control.h"
#include "tof_sensor.h"

extern int photo;

void findBox() {
	adjSpeed(255);

  Serial.println("wall section start");
  while(!digitalRead(photo)) {
    followLine();
  }
  Serial.println("wall section end");

  adjSpeed(150);

  while(digitalRead(photo)) {
    followLine();
  }
  Serial.println("box found");

  uint32_t startTime = millis();
  while(millis() - startTime < 1200) {
    followLine();
  }

  stop();
}

void faceBox() {
	adjSpeed(255);

  while(!digitalRead(R2)) {
    adjRight();
  }
  stop();
  while(!digitalRead(L2)) {
    adjSlightLeftReverse();
  }
  stop();
}
