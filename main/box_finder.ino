#include <Adafruit_MotorShield.h>
#include "line_follower.h"
#include "motor_control.h"
#include "tof_sensor.h"
#include "led_flash.h"

extern int photo;
extern uint32_t hysteris_time;
#define TIME_THRESHOLD 5000

bool findBox() {
	/* Starting from an intersection, look for the offline box on the right hand side by using photoelectric sensor
	   Returns true if the box is found, false otherwise
	 */
	adjSpeed(165);

  uint32_t tm = millis();

  Serial.println("wall section start");
  // Keep running until it detects the concave wall or it runs out of time
  while(!digitalRead(photo)) {
	  ledFlash();
    followLine();
    if(millis()-tm > TIME_THRESHOLD)
      goto over_threshold; // give up after 5 secs
  }
  Serial.println("wall section end");

  adjSpeed(165);

  // Keep runnin until it detects something closer than the concave wall (ie the offline box)
  while(digitalRead(photo)) {
	  ledFlash();
    followLine();
    if(millis()-tm > TIME_THRESHOLD)
      goto over_threshold; // give up after 5 secs
  }
  Serial.println("box found");

  Serial.println(millis() - tm);
  if(millis() - tm > TIME_THRESHOLD){
    over_threshold:
    Serial.println("exceeded box finding threshold time");
    adjSpeed(255);
    return false;
  }

  // Go a bit further to align the center of the robot with the box
  uint32_t startTime = millis();
  while(millis() - startTime < 1200) {
	  ledFlash();
    followLine();
  }

  stop();
  return true;
}

bool collectBox() {
	/*
	   Turns perpendicular to the line and goes forward to try to pick up the offline box
	   Returns true if the box has been successfully picked up, false otherwise
	*/
	adjSpeed(255);

	// Turn right with both wheels until the right side sensor detects the line
  while(!digitalRead(R2)) {
	  ledFlash();
    adjRight();
  }
  stop();

  // Turn left motor backwards until the left side sensor detects the line
  while(!digitalRead(L2)) {
	  ledFlash();
    adjSlightLeftReverse();
  }

  // Turn right motor backwards until the right side sensor detects the line
  while(!digitalRead(R2)) {
	  ledFlash();
    adjSlightRightReverse();
  }

  // At this point, both line sensors are either completely or basically on the line with the
  // TOF sensor aligned with the box perpendicular to the line

  // Attempt to go blindly forwards for the box but stops in time as to not hit the wall
  hysteris_time = millis();
  stop();
  bool gotBox = false;
  uint32_t t = millis();
  forward();
  while(millis() - t < 2100) {
    if(getDistanceReading()) {
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
