#include <Adafruit_MotorShield.h>
#include "line_follower.h"
#include "motor_control.h"
#include "box_finder.h"
#include "paths.h"
#include "Wire.h"
#include "DFRobot_VL53L0X.h"
#include <Servo.h>


DFRobot_VL53L0X sensor;

int Crash1 = 2;
int Crash2 = 3;
int BlueLED = 8;
int RedLED = 9;
int GreenLED = 12;
int L1 = A2;
int R1 = A1;
int L2 = A0;
int R2 = A3;
int button = 13;
int photo = 6;
int Magnetic1 = 4;
int Magnetic2 = 5;
Servo grabber;
Servo lifter;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);  // set up Serial library at 9600 bps


  // Set up pins for sensors and LEDs
 pinMode(BlueLED, OUTPUT);
 pinMode(RedLED, OUTPUT);
 pinMode(GreenLED, OUTPUT);
 pinMode(L1, INPUT);
 pinMode(R1, INPUT);
 pinMode(L2, INPUT);
 pinMode(R2, INPUT);
 pinMode(button, INPUT);
 pinMode(photo, INPUT);

	// Initialize Servos and initial positions
  grabber.attach(11);
  lifter.attach(10);
  grabberUp();
  grabberClose();

  // Initialize TOF
  Wire.begin();
  sensor.begin(0x50);
  sensor.setMode(sensor.eContinuous,sensor.eHigh);
  sensor.start();

  // Connect to MotorShield for DC Motors
  if (!AFMS.begin()) {  // create with the default frequency 1.6KHz
                        // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1)
      ;
  }
  Serial.println("Motor Shield found.");

  // Set the speed to start, from 0 (off) to 255 (max speed)
  adjSpeed(255);
  Serial.println("speed set");
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);


  // Wait for Button press to start
  Serial.println("setup hold");
  while (1) {
    Serial.println("setup loop");
    if (digitalRead(button) == HIGH) {
      Serial.println("setup exit");
      delay(1000);
      break;
    }
  }

  adjSpeed(255);
  exitBox();
  competitionRoute();
}

void loop() {
}
