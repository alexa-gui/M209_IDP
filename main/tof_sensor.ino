#include "tof_sensor.h"

extern int LED_YEL;
float readings_buf[100] = { 200 };
int threshold = 10;
bool getDistanceReading() {
	/*
	   Returns whether the TOF has detected a box in front of it
	   Has to have 10 readings in a row that are closer than the threshold
	 */
  float dist_raw = sensor.getDistance();
  Serial.println(dist_raw);
  int i;
  for (i = 98; i >= 0; i--)
    readings_buf[i + 1] = readings_buf[i];
  readings_buf[0] = dist_raw;
  bool all_below = true;
  for (i = 0; i < threshold; i++) {
    if (readings_buf[i] > 100) {
      all_below = false;
      break;
    }
  }
  if (all_below) {
    for (i = 0; i < threshold; i++)
      readings_buf[i] = 200;
    return true;
  }
  return false;
}
