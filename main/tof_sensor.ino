#include "tof_sensor.h"

extern int LED_YEL;

uint8_t getDistanceReading(){
	// TODO
	float dist_raw = sensor.getDistance();
	if(dist_raw <= GROUND_FLAT) {
    digitalWrite(LED_YEL, HIGH);
		return FLAT;
  }
  digitalWrite(LED_YEL, LOW);
	return GROUND;
}
