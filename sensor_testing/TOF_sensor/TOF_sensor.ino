#include "Arduino.h"
#include "Wire.h"
#include "DFRobot_VL53L0X.h"

DFRobot_VL53L0X sensor;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  sensor.begin(0x50);
  sensor.setMode(sensor.eContinuous,sensor.eHigh);
  sensor.start();
}

void loop() {
  Serial.print("Distance:");Serial.println(sensor.getDistance());
  delay(500);
}
