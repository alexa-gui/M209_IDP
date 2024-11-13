#include <Adafruit_MotorShield.h>
#include "motor_control.h"

void forward() {  //forword
  leftMotor->run(BACKWARD);
  rightMotor->run(BACKWARD);
}

void reverse(){
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
}

void adjRight() {  //turnRight
  rightMotor->run(FORWARD);
  leftMotor->run(BACKWARD);
}

void adjLeft() {  //turnLeft
  rightMotor->run(BACKWARD);
  leftMotor->run(FORWARD);
}

void stop() {  //stop
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);
}
void adjSlightRight(){
	leftMotor->run(BACKWARD);
	rightMotor->run(RELEASE);
}
void adjSlightLeft(){
	rightMotor->run(BACKWARD);
	leftMotor->run(RELEASE);
}

void adjSlightRightReverse(){
	rightMotor->run(FORWARD);
	leftMotor->run(RELEASE);
}

void adjSlightLeftReverse(){
	rightMotor->run(RELEASE);
	leftMotor->run(FORWARD);
}
