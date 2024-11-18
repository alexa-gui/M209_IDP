#include <Adafruit_MotorShield.h>
#include "line_follower.h"
#include "motor_control.h"
#include "tof_sensor.h"

extern Adafruit_DCMotor *leftMotor;
extern Adafruit_DCMotor *rightMotor;
extern int photo;

uint32_t hysteris_time = 0;
#define INTERSECTION_DLY 2000
bool isIntersection() {
  if (millis() - hysteris_time <= INTERSECTION_DLY)
    return false;
  bool intersection_raw = (digitalRead(L2) || digitalRead(R2));
  if (intersection_raw) {
    hysteris_time = millis();
  }
  return (digitalRead(L2) || digitalRead(R2));
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
  digitalWrite(LED, HIGH);
  stop();
  Serial.println("Detected Intersection");
}

void runTillEvent() {
  while (!isIntersection() && (getDistanceReading() == GROUND)) {
    followLine();
  }
  digitalWrite(LED, HIGH);
  stop();
  Serial.println("Detected Intersection");
}
void backOutTillIntersection() {
  while (!isIntersection()) {
    reverse();
  }
  stop();
}

// TODO: adjust this value
#define TURN_DLY 100

void turnRight() {  //turnRight

  adjRight();
  delay(TURN_DLY);
  while (1) {
    if (digitalRead(R1) == 1) {
      break;
    }
  }
}

void turnLeft() {  //turnLeft

  adjLeft();

  delay(TURN_DLY);
  while (1) {
    if (digitalRead(L1) == 1) {
      break;
    }
  }
}
void turnSlightRight() {  //turnRight

  adjSlightRight();
  delay(TURN_DLY);
  while (1) {
    if (digitalRead(R1) == 1) {
      break;
    }
  }
}

void turnSlightLeft() {  //turnLeft

  adjSlightLeft();

  delay(TURN_DLY);
  while (1) {
    if (digitalRead(L1) == 1) {
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
      if ((digitalRead(L1) == 1) || (digitalRead(R1) == 1)) {
        goto end_sweep;
      }
    }
    adjRight();
    startTime = millis();
    while ((millis() - startTime) < 2000) {
      if ((digitalRead(L1) == 1) || (digitalRead(R1) == 1)) {
        goto end_sweep;
      }
    }
    adjLeft();
    startTime = millis();
    while ((millis() - startTime) < 1000) {
      if ((digitalRead(L1) == 1) || (digitalRead(R1) == 1)) {
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
    if (digitalRead(L2) == 1) {
      exitLeft = 1;
    }
    if (digitalRead(R2) == 1) {
      exitRight = 1;
    }
  }

  delay(500);
  startTime = millis();
  while ((millis() - startTime) < 500) {
    if ((digitalRead(L2) == 1) || (digitalRead(R2) == 1)) {
      break;
    }
  }
  stop();
  sweep();
}

// void zigzag_follow(){
//   if ((digitalRead(R1) == 0) && (digitalRead(L1) == 0)) { forward(); }  //if Right Sensor and Left Sensor are at black color then it will call forword function
//
//   if ((digitalRead(R1) == 1) && (digitalRead(L1) == 0)) { adjSlightRight(); delay(50); }  //if Right Sensor is white and Left Sensor is black then it will call turn Right function
//
//   if ((digitalRead(R1) == 0) && (digitalRead(L1) == 1)) { adjSlightLeft(); delay(50); }  //if Right Sensor is black and Left Sensor is white then it will call turn Left function
//
//   if ((digitalRead(R1) == 1) && (digitalRead(L1) == 1)) { forward(); }  //if Right Sensor and Left Sensor are at white color then it will call stop function
// }

void followLine() {
  if (digitalRead(button))
    while (1) { stop(); }

  if ((digitalRead(R1) == 0) && (digitalRead(L1) == 0)) { forward(); }  //if Right Sensor and Left Sensor are at black color then it will call forword function

  // if ((digitalRead(R1) == 1) && (digitalRead(L1) == 0)) { adjRight(); }  //if Right Sensor is white and Left Sensor is black then it will call turn Right function
  if ((digitalRead(R1) == 1) && (digitalRead(L1) == 0)) { adjSlightRight(); }  //if Right Sensor is white and Left Sensor is black then it will call turn Right function

  // if ((digitalRead(R1) == 0) && (digitalRead(L1) == 1)) { adjLeft(); }  //if Right Sensor is black and Left Sensor is white then it will call turn Left function
  if ((digitalRead(R1) == 0) && (digitalRead(L1) == 1)) { adjSlightLeft(); }  //if Right Sensor is black and Left Sensor is white then it will call turn Left function

  if ((digitalRead(R1) == 1) && (digitalRead(L1) == 1)) { forward(); }  //if Right Sensor and Left Sensor are at white color then it will call stop function
}

// void followLineReverse() {
//   if (digitalRead(button))
//     while (1) { stop(); }
//   if ((digitalRead(R1) == 0) && (digitalRead(L1) == 0)) { reverse(); }  //if Right Sensor and Left Sensor are at black color then it will call forword function
//
//   // if ((digitalRead(R1) == 1) && (digitalRead(L1) == 0)) { adjRight(); }  //if Right Sensor is white and Left Sensor is black then it will call turn Right function
//   if ((digitalRead(R1) == 1) && (digitalRead(L1) == 0)) { adjSlightLeftReverse(); }  //if Right Sensor is white and Left Sensor is black then it will call turn Right function
//
//   // if ((digitalRead(R1) == 0) && (digitalRead(L1) == 1)) { adjLeft(); }  //if Right Sensor is black and Left Sensor is white then it will call turn Left function
//   if ((digitalRead(R1) == 0) && (digitalRead(L1) == 1)) { adjSlightRightReverse(); }  //if Right Sensor is black and Left Sensor is white then it will call turn Left function
//
//   if ((digitalRead(R1) == 1) && (digitalRead(L1) == 1)) { reverse(); }  //if Right Sensor and Left Sensor are at white color then it will call stop function
// }
