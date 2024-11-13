#ifndef TOF_SENSOR_H
#define TOF_SENSOR_H
#include "DFRobot_VL53L0X.h"

#define GROUND_FLAT 65

#define GROUND 0
#define FLAT 1
#define HALF_RAISED 2
#define FULL_RAISED 3

uint8_t getDistanceReading();

#endif
