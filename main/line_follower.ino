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
  uint32_t currentTime = millis();
  while (millis() - currentTime <= time_ms)
    followLine();
  stop();
}

void runTillIntersection() {
  while (!isIntersection()) {
	  ledFlash();
    followLine();
  }
  stop();
  // delayWithFlash(250);
  // hysteris_time = millis();
  Serial.println("Detected Intersection");
  // digitalWrite(LED_YEL, 1);
  // delayWithFlash(500);
  // digitalWrite(LED_YEL, 0);
}
bool zigzagRunTillIntersectionOrBox() {
  while(getDistanceReading()==GROUND){
    if(isIntersection()){
		stop();
		return false;
	  }
    zigzagFollowLine();
  }
  stop();
  return true;
}
bool runTillIntersectionOrBox() {
  while(getDistanceReading()==GROUND){
    if(isIntersection()){
		stop();
		return false;
	  }
    followLine();
  }
  stop();
  return true;
}

void runTillEvent() {
  while (!isIntersection() && (getDistanceReading() == GROUND)) {
    followLine();
  }
  stop();
  Serial.println("Detected Intersection or Box");
}

void backOutTillIntersection() {
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
  // hysteris_time = millis();
  // Unsure if this should be commented out or not
}

void turn180() {
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

void turnRight() {  //turnRight

  adjRight();
  delayWithFlash(TURN_DLY);
  while (1) {
    // if (adcRead(R1) == 1) {
		ledFlash();
    if (risingEdgeRead(R1) == 1) {
      break;
    }
  }
}

void turnLeft() {  //turnLeft

  adjLeft();

  delayWithFlash(TURN_DLY);
  while (1) {
    // if (adcRead(L1) == 1) {
	  ledFlash();
    if (risingEdgeRead(L1) == 1) {
      break;
    }
  }
}
void turnSlightRight() {  //turnRight

  adjSlightRight();
  delayWithFlash(TURN_DLY);
  while (1) {
    // if (adcRead(R1) == 1) {
	  ledFlash();
    if (risingEdgeRead(R1) == 1) {
      break;
    }
  }
}

void turnSlightLeft() {  //turnLeft

  adjSlightLeft();

  delayWithFlash(TURN_DLY);
  while (1) {
    // if (adcRead(L1) == 1) {
	  ledFlash();
    if (risingEdgeRead(L1) == 1) {
      break;
    }
  }
}

void turnDiffRight(int speed) {
  adjDiffRight(speed);                    //as adjRight but with right motor at speed 'speed'

  delayWithFlash(TURN_DLY);
  while (1) {
    // if (adcRead(R1) == 1) {
	  ledFlash();
    if (risingEdgeRead(R1) == 1) {
      break;
    }
  }
  adjSpeed(255);
}

void turnDiffLeft(int speed) {
  adjDiffLeft(speed);                     //as adjLeft but with right motor at speed 'speed'

  delayWithFlash(TURN_DLY);
  while (1) {
    // if (adcRead(L1) == 1) {
	  ledFlash();
    if (risingEdgeRead(L1) == 1) {
      break;
    }
  }
  adjSpeed(255);
}

void sweep() {
  uint32_t startTime;

  adjSpeed(150);

  while (1) {
    adjLeft();
	ledFlash();
    startTime = millis();
    while ((millis() - startTime) < 1000) {
		ledFlash();
      if ((adcRead(L1) == 1) || (adcRead(R1) == 1)) {
        goto end_sweep;
      }
    }
    adjRight();
    startTime = millis();
    while ((millis() - startTime) < 2000) {
		ledFlash();
      if ((adcRead(L1) == 1) || (adcRead(R1) == 1)) {
        goto end_sweep;
      }
    }
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
  bool exitLeft = 0;
  bool exitRight = 0;
  uint32_t startTime;

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
  delayWithFlash(250);
  startTime = millis();
  while ((millis() - startTime) < 250) {
		ledFlash();
    if ((adcRead(L2) == 1) || (adcRead(R2) == 1)) {
      break;
    }
  }
  stop();
  sweep();
}
void zigzagFollowLine(){
    if (digitalRead(button))
    while (1) { stop(); }

		ledFlash();
  if ((adcRead(R1) == 0) && (adcRead(L1) == 0)) { forward(); delay(10);} 
  if ((adcRead(R1) == 1) && (adcRead(L1) == 0)) { adjSlightRight(); delay(10);} 
  if ((adcRead(R1) == 0) && (adcRead(L1) == 1)) { adjSlightLeft(); delay(10);}
  if ((adcRead(R1) == 1) && (adcRead(L1) == 1)) { forward(); delay(10);} 
}
void followLine() {
  if (digitalRead(button))
    while (1) { stop(); }

		ledFlash();
  if ((adcRead(R1) == 0) && (adcRead(L1) == 0)) { forward(); }  //if Right Sensor and Left Sensor are at black color then it will call forword function

  // if ((digitalRead(R1) == 1) && (digitalRead(L1) == 0)) { adjRight(); }  //if Right Sensor is white and Left Sensor is black then it will call turn Right function
  if ((adcRead(R1) == 1) && (adcRead(L1) == 0)) { adjSlightRight(); }  //if Right Sensor is white and Left Sensor is black then it will call turn Right function

  // if ((digitalRead(R1) == 0) && (digitalRead(L1) == 1)) { adjLeft(); }  //if Right Sensor is black and Left Sensor is white then it will call turn Left function
  if ((adcRead(R1) == 0) && (adcRead(L1) == 1)) { adjSlightLeft(); }  //if Right Sensor is black and Left Sensor is white then it will call turn Left function

  if ((adcRead(R1) == 1) && (adcRead(L1) == 1)) { forward(); }  //if Right Sensor and Left Sensor are at white color then it will call stop function
}
