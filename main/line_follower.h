#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H
#include <Adafruit_MotorShield.h>

void exitBox();
void runTillIntersection();
void runTillTimed(uint32_t time_ms);
void turnRight();
void turnLeft();
void turnSlightRight();
void turnSlightLeft();
bool isIntersection();
void backOutTillIntersection();

#endif
