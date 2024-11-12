#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H
#include <Adafruit_MotorShield.h>
extern Adafruit_DCMotor* leftMotor;
extern Adafruit_DCMotor* rightMotor;
void forward();
void adjRight();
void adjLeft();
void stop();
#endif
