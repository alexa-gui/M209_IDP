#include "tof_sensor.h"

uint8_t getDistanceReading(){
	// TODO
	float dist_raw = sensor.getDistance();
	if(dist_raw <= GROUND_FLAT)
		return FLAT;
	return GROUND;
}
