#include <Adafruit_MotorShield.h>
#include "Wire.h"
#include <Servo.h>
#include "DFRobot_VL53L0X.h"

Servo servo1;

DFRobot_VL53L0X sensor;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

void setup(){
	servo1.attach(11);
	sensor.begin(0x50);
	sensor.setMode(sensor.eContinuous,sensor.eHigh);
	sensor.start();
	AFMS.begin();
}

void loop(){
	servo1.write(0);
	delay(1000);
	servo1.write(100);
}
