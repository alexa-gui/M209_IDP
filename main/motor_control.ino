#include <Adafruit_MotorShield.h>
#include "motor_control.h"

bool is_moving = false;

void forward() {
	is_moving = true;
  leftMotor->run(BACKWARD);
  rightMotor->run(BACKWARD);
}

void reverse(){
	is_moving = true;
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
}

void adjRight() {
	is_moving = true;
  rightMotor->run(FORWARD);
  leftMotor->run(BACKWARD);
}

void adjLeft() {
	is_moving = true;
  rightMotor->run(BACKWARD);
  leftMotor->run(FORWARD);
}

void stop() {
	is_moving = false;
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);
}
void adjSlightRight(){
	is_moving = true;
	leftMotor->run(BACKWARD);
	rightMotor->run(RELEASE);
}
void adjSlightLeft(){
	is_moving = true;
	rightMotor->run(BACKWARD);
	leftMotor->run(RELEASE);
}

void adjSlightRightReverse(){
	is_moving = true;
	rightMotor->run(FORWARD);
	leftMotor->run(RELEASE);
}

void adjSlightLeftReverse(){
	is_moving = true;
	rightMotor->run(RELEASE);
	leftMotor->run(FORWARD);
}

void adjDiffRight(int speed) {
  is_moving = true;
  rightMotor->setSpeed(speed);
  rightMotor->run(FORWARD);
  leftMotor->run(BACKWARD);
}

void adjDiffLeft(int speed) {
  is_moving = true;
  leftMotor->setSpeed(speed);
  leftMotor->run(FORWARD);
  rightMotor->run(BACKWARD);
}

void adjSpeed(uint8_t speed){
	rightMotor->setSpeed(speed);
	leftMotor->setSpeed(speed);
}
