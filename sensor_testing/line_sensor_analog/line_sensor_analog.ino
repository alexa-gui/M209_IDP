int line_sensor_pin = A0;

void setup(){
	Serial.begin(9600);
}

float raw_reading;
const float threshold = 500;
bool dig_reading;
void loop(){
	raw_reading = analogRead(line_sensor_pin);
  dig_reading = raw_reading > 500;
	Serial.println(dig_reading);
}
