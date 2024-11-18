#include <Adafruit_MotorShield.h>
#include "motor_control.h"

bool is_moving = false;
void forward() {  //forword
	is_moving = true;
  leftMotor->run(BACKWARD);
  rightMotor->run(BACKWARD);
}

void reverse(){
	is_moving = true;
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
}

void adjRight() {  //turnRight
	is_moving = true;
  rightMotor->run(FORWARD);
  leftMotor->run(BACKWARD);
}

void adjLeft() {  //turnLeft
	is_moving = true;
  rightMotor->run(BACKWARD);
  leftMotor->run(FORWARD);
}

void stop() {  //stop
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

void adjSpeed(uint8_t speed){
	rightMotor->setSpeed(RIGHT_SLOW_RATIO(speed));
	leftMotor->setSpeed(LEFT_SLOW_RATIO(speed));
}
