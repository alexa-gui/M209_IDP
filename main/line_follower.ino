#include <Adafruit_MotorShield.h>
#include "line_follower.h"
#include "motor_control.h"
#include "tof_sensor.h"
#include "line_sensor_wrapper.h"
#include "led_flash.h"

extern Adafruit_DCMotor *leftMotor;
extern Adafruit_DCMotor *rightMotor;
extern int photo;
extern int LED_YEL;

uint32_t hysteris_time = 0;
#define INTERSECTION_DLY 1000

bool isIntersection() {
	// Returns if the robot detects an intersection
	// with a filter that only allows detection 1 sec after a previous detection
	ledFlash();
  if (millis() - hysteris_time <= INTERSECTION_DLY)
    return false;
  bool intersection_raw = (adcRead(L2) || adcRead(R2));
  if (intersection_raw) {
    hysteris_time = millis();
  }
  return intersection_raw;
}

void runTillTimed(uint32_t time_ms) {
	// Line follow for a set amount of time
  uint32_t currentTime = millis();
  while (millis() - currentTime <= time_ms)
    followLine();
  stop();
}

void runTillIntersection() {
	// Line follow until the robot detects an intersection
  while (!isIntersection()) {
	  ledFlash();
    followLine();
  }
  stop();
  Serial.println("Detected Intersection");
}

bool runTillIntersectionOrBox() {
	/*
	   Line follows until the robot either detects a box or hits an intersection
	   Returns true if it detects a box
	 */
  while(!getDistanceReading()){
    if(isIntersection()){
		stop();
		return false;
	  }
    followLine();
  }
  stop();
  return true;
}

void backOutTillIntersection() {
	// Back out till both line sensors detect an intersection
	// This is done to ensure the robot is perpendicular to the line
  while (!isIntersection()) {
    reverse();
  }
  stop();

  if(adcRead(L2)&&adcRead(R2))
    return;
  if(adcRead(L2)&&!adcRead(R2)){
    while(!adcRead(R2)) {
      adjSlightRightReverse();
	  ledFlash();
	}
  }
    if(!adcRead(L2)&&adcRead(R2)){
    while(!adcRead(L2)) {
      adjSlightLeftReverse();
	  ledFlash();
	}
  }
  stop();
}

void turn180() {
	// 3 point turn that turns the robot around, the turning radius is smaller than just a single turn
  while(digitalRead(R2) == 0) {
	  ledFlash();
    adjLeft();
  }
  while(digitalRead(L2) == 0) {
	  ledFlash();
    adjSlightLeftReverse();
  }
  turnLeft();
}

void turnRight() {
	// Turns right differentially until the right central sensor detects a rising edge
  adjRight();
  delayWithFlash(TURN_DLY); // added a delay to ensure the robot doesn't detect the current line its on
  while (1) {
		ledFlash();
    if (risingEdgeRead(R1) == 1) {
      break;
    }
  }
}

void turnLeft() {
	// Turns left differentially until the left central sensor detects a rising edge
  adjLeft();

  delayWithFlash(TURN_DLY); // added a delay to ensure the robot doesn't detect the current line its on
  while (1) {
	  ledFlash();
    if (risingEdgeRead(L1) == 1) {
      break;
    }
  }
}
void turnSlightRight() {
	// Turns right with only left motor going forwards until right central sensor detects a rising edge
  adjSlightRight();
  delayWithFlash(TURN_DLY); // added a delay to ensure the robot doesn't detect the current line its on
  while (1) {
	  ledFlash();
    if (risingEdgeRead(R1) == 1) {
      break;
    }
  }
}

void turnSlightLeft() {
	// Turns left with only right motor going forwards until left central sensor detects a rising edge
  adjSlightLeft();
  delayWithFlash(TURN_DLY); // added a delay to ensure the robot doesn't detect the current line its on
  while (1) {
	  ledFlash();
    if (risingEdgeRead(L1) == 1) {
      break;
    }
  }
}

void turnDiffRight(int speed) {
	// Turns right with left motor full speed and right motor at a different speed
  adjDiffRight(speed); //adjRight but with right motor at speed 'speed'

  delayWithFlash(TURN_DLY); // added a delay to ensure the robot doesn't detect the current line its on
  while (1) {
	  ledFlash();
    if (risingEdgeRead(R1) == 1) {
      break;
    }
  }
  adjSpeed(255);
}

void turnDiffLeft(int speed) {
	// Turns left with right motor full speed and left motor at a different speed
  adjDiffLeft(speed); //adjLeft but with right motor at speed 'speed'

  delayWithFlash(TURN_DLY); // added a delay to ensure the robot doesn't detect the current line its on
  while (1) {
	  ledFlash();
    if (risingEdgeRead(L1) == 1) {
      break;
    }
  }
  adjSpeed(255);
}

void sweep() {
	// Sweeps left and right until the robot finds a line
  uint32_t startTime;

  adjSpeed(150);

  while (1) {
	  // Sweep left for 1 sec or until either central sensor detects the line
    adjLeft();
	ledFlash();
    startTime = millis();
    while ((millis() - startTime) < 1000) {
		ledFlash();
      if ((adcRead(L1) == 1) || (adcRead(R1) == 1)) {
        goto end_sweep;
      }
    }

	  // Sweep right for 2 sec or until either central sensor detects the line
    adjRight();
    startTime = millis();
    while ((millis() - startTime) < 2000) {
		ledFlash();
      if ((adcRead(L1) == 1) || (adcRead(R1) == 1)) {
        goto end_sweep;
      }
    }

	  // Sweep left for 1 sec or until either central sensor detects the line
    adjLeft();
    startTime = millis();
    while ((millis() - startTime) < 1000) {
		ledFlash();
      if ((adcRead(L1) == 1) || (adcRead(R1) == 1)) {
        goto end_sweep;
      }
    }
  }

end_sweep:
  adjSpeed(255);
  hysteris_time = millis() - 500;
  return;
}

void exitBox() {
	// Exit the starting box by first exiting the box boundary is and then sweeping onto the line
  bool exitLeft = 0;
  bool exitRight = 0;
  uint32_t startTime;

  // Forward until both side sensors have passed the box boundary
  forward();

  while ((exitLeft == 0) || (exitRight == 0)) {
		ledFlash();
    if (adcRead(L2) == 1) {
      exitLeft = 1;
    }
    if (adcRead(R2) == 1) {
      exitRight = 1;
    }
  }
  Serial.println("Exited box boundary");

  // continue forwards for a bit, stopping if the side sensors hit the central line
  // signifying an overshoot
  delayWithFlash(250);
  startTime = millis();
  while ((millis() - startTime) < 250) {
		ledFlash();
    if ((adcRead(L2) == 1) || (adcRead(R2) == 1)) {
      break;
    }
  }
  stop();

  // Sweep onto the line
  sweep();
}

void followLine() {
	// One iteration of line following

	// Stop button
  if (digitalRead(button))
    while (1) { stop(); }

  ledFlash();
  if ((adcRead(R1) == 0) && (adcRead(L1) == 0)) { forward(); }  //if Right Sensor and Left Sensor are at black color then it will call forword function
  if ((adcRead(R1) == 1) && (adcRead(L1) == 0)) { adjSlightRight(); }  //if Right Sensor is white and Left Sensor is black then it will call turn Right function
  if ((adcRead(R1) == 0) && (adcRead(L1) == 1)) { adjSlightLeft(); }  //if Right Sensor is black and Left Sensor is white then it will call turn Left function
  if ((adcRead(R1) == 1) && (adcRead(L1) == 1)) { forward(); }  //if Right Sensor and Left Sensor are at white color then it will call stop function
}
