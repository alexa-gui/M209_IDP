#include "line_sensor_wrapper.h"

const float adcThreshold = 500;
bool adcRead(int port){
	float raw_reading = analogRead(port);
	return raw_reading > adcThreshold;
}
