#include <Adafruit_MotorShield.h>
#include "line_follower.h"
#include "motor_control.h"
#include "tof_sensor.h"
#include "line_sensor_wrapper.h"

extern Adafruit_DCMotor *leftMotor;
extern Adafruit_DCMotor *rightMotor;
extern int photo;
extern int LED_YEL;

uint32_t hysteris_time = 0;
#define INTERSECTION_DLY 2000
bool isIntersection() {
  if (millis() - hysteris_time <= INTERSECTION_DLY)
    return false;
  bool intersection_raw = (adcRead(L2) || adcRead(R2));
  //digitalWrite(LED_YEL, LOW);
  if (intersection_raw) {
    hysteris_time = millis();
    //digitalWrite(LED_YEL, HIGH);
  }
  return (adcRead(L2) || adcRead(R2));
}

void runTillTimed(uint32_t time_ms) {
  uint32_t currentTime = millis();
  while (millis() - currentTime <= time_ms)
    followLine();
  stop();
}

void runTillIntersection() {
  while (!isIntersection()) {
    followLine();
  }
  stop();
  Serial.println("Detected Intersection");
  // digitalWrite(LED_YEL, 1);
  // delay(500);
  // digitalWrite(LED_YEL, 0);
}

bool runTillIntersectionOrBox() {
  while(getDistanceReading()==GROUND){
    if(isIntersection())
      return false;
    followLine();
  }
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
    while(!adcRead(R2))
      adjSlightRightReverse();
  }
    if(!adcRead(L2)&&adcRead(R2)){
    while(!adcRead(L2))
      adjSlightLeftReverse();
  }
  stop();
  //hysteris_time = millis();
}

void turn180() {
  while(digitalRead(R2) == 0) {
    adjLeft();
  }
  while(digitalRead(L2) == 0) {
    adjSlightLeftReverse();
  }
  turnLeft();
}

void turnRight() {  //turnRight

  adjRight();
  delay(TURN_DLY);
  while (1) {
    // if (adcRead(R1) == 1) {
    if (risingEdgeRead(R1) == 1) {
      break;
    }
  }
}

void turnLeft() {  //turnLeft

  adjLeft();

  delay(TURN_DLY);
  while (1) {
    // if (adcRead(L1) == 1) {
    if (risingEdgeRead(L1) == 1) {
      break;
    }
  }
}
void turnSlightRight() {  //turnRight

  adjSlightRight();
  delay(TURN_DLY);
  while (1) {
    // if (adcRead(R1) == 1) {
    if (risingEdgeRead(R1) == 1) {
      break;
    }
  }
}

void turnSlightLeft() {  //turnLeft

  adjSlightLeft();

  delay(TURN_DLY);
  while (1) {
    // if (adcRead(L1) == 1) {
    if (risingEdgeRead(L1) == 1) {
      break;
    }
  }
}

void sweep() {
  uint32_t startTime;

  adjSpeed(150);

  while (1) {
    adjLeft();
    startTime = millis();
    while ((millis() - startTime) < 1000) {
      if ((adcRead(L1) == 1) || (adcRead(R1) == 1)) {
        goto end_sweep;
      }
    }
    adjRight();
    startTime = millis();
    while ((millis() - startTime) < 2000) {
      if ((adcRead(L1) == 1) || (adcRead(R1) == 1)) {
        goto end_sweep;
      }
    }
    adjLeft();
    startTime = millis();
    while ((millis() - startTime) < 1000) {
      if ((adcRead(L1) == 1) || (adcRead(R1) == 1)) {
        goto end_sweep;
      }
    }
  }
end_sweep:
  adjSpeed(255);
  return;
}

void exitBox() {
  bool exitLeft = 0;
  bool exitRight = 0;
  uint32_t startTime;

  forward();

  while ((exitLeft == 0) || (exitRight == 0)) {
    if (adcRead(L2) == 1) {
      exitLeft = 1;
    }
    if (adcRead(R2) == 1) {
      exitRight = 1;
    }
  }

  delay(500);
  startTime = millis();
  while ((millis() - startTime) < 500) {
    if ((adcRead(L2) == 1) || (adcRead(R2) == 1)) {
      break;
    }
  }
  stop();
  sweep();
}

void followLine() {
  if (digitalRead(button))
    while (1) { stop(); }

  if ((adcRead(R1) == 0) && (adcRead(L1) == 0)) { forward(); }  //if Right Sensor and Left Sensor are at black color then it will call forword function

  // if ((digitalRead(R1) == 1) && (digitalRead(L1) == 0)) { adjRight(); }  //if Right Sensor is white and Left Sensor is black then it will call turn Right function
  if ((adcRead(R1) == 1) && (adcRead(L1) == 0)) { adjSlightRight(); }  //if Right Sensor is white and Left Sensor is black then it will call turn Right function

  // if ((digitalRead(R1) == 0) && (digitalRead(L1) == 1)) { adjLeft(); }  //if Right Sensor is black and Left Sensor is white then it will call turn Left function
  if ((adcRead(R1) == 0) && (adcRead(L1) == 1)) { adjSlightLeft(); }  //if Right Sensor is black and Left Sensor is white then it will call turn Left function

  if ((adcRead(R1) == 1) && (adcRead(L1) == 1)) { forward(); }  //if Right Sensor and Left Sensor are at white color then it will call stop function
}
