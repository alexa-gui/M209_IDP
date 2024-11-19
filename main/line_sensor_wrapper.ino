#include "line_sensor_wrapper.h"

const float adcThreshold = 500;
bool adcRead(int port){
	float raw_reading = analogRead(port);
	return raw_reading > adcThreshold;
}

bool risingEdgeRead(int port){
	static bool prev_result = false;
	bool dig_reading = adcRead(port);
	bool result = (dig_reading && (!prev_result));
	prev_result = dig_reading;
	return result;
}
