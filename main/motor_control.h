#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H
#include <Adafruit_MotorShield.h>
extern Adafruit_DCMotor* leftMotor;
extern Adafruit_DCMotor* rightMotor;
void forward();
void reverse();
void adjRight();
void adjLeft();
void stop();
void adjSlightRight();
void adjSlightLeft();
void adjSlightRightReverse();
void adjSlightLeftReverse();
void adjSpeed(uint8_t speed);
#define LEFT_SLOW_RATIO(X) ((X * 100)/100)
#define RIGHT_SLOW_RATIO(X) ((X * 100)/100)
#endif
