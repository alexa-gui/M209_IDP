#include <Adafruit_MotorShield.h>
#include "motor_control.h"

void forward() {  //forword
  leftMotor->run(BACKWARD);
  rightMotor->run(BACKWARD);
}

void adjRight() {  //turnRight
  leftMotor->run(FORWARD);
  rightMotor->run(BACKWARD);
}

void adjLeft() {  //turnLeft
  leftMotor->run(BACKWARD);
  rightMotor->run(FORWARD);
}

void stop() {  //stop
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);
}
