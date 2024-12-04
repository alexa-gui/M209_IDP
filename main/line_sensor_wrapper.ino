#include "line_sensor_wrapper.h"

const float adcThreshold = 500;
bool adcRead(int port){
	// Take reading from analog port and convert it to a digital reading
	float raw_reading = analogRead(port);
	return raw_reading > adcThreshold;
}

bool risingEdgeRead(int port){
	// A rising edge detector for the line sensor
	static bool prev_result = false;
	bool dig_reading = adcRead(port);
	bool result = (dig_reading && (!prev_result));
	prev_result = dig_reading;
	return result;
}
