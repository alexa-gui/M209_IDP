#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H
#include <Adafruit_MotorShield.h>

#define TURN_DLY 250

void exitBox();
void sweep();
void runTillIntersection();
void runTillTimed(uint32_t time_ms);
void runTillEvent();
void followLine();
void turnRight();
void turnLeft();
void turnSlightRight();
void turnSlightLeft();
bool isIntersection();
void backOutTillIntersection();

#endif
