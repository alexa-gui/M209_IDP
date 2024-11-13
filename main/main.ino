#include <Adafruit_MotorShield.h>
#include "line_follower.h"

// Arduino Line Follower Robot Code

int LED = 1;
int L1 = 2;
int R1 = 3;
int L2 = 5;
int R2 = 6;
int button = 4;
int turnCounter = 0;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

void setup() {

  Serial.begin(9600);  // set up Serial library at 9600 bps

  pinMode(LED, OUTPUT);
  pinMode(L1, INPUT);
  pinMode(R1, INPUT);
  pinMode(button, INPUT);

  if (!AFMS.begin()) {  // create with the default frequency 1.6KHz
                        // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1)
      ;
  }
  Serial.println("Motor Shield found.");

  // Set the speed to start, from 0 (off) to 255 (max speed)
  leftMotor->setSpeed(255);
  rightMotor->setSpeed(255);
  Serial.println("speed set");
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);

  Serial.println("entering while loop");
  while (1) {
    if (digitalRead(button) == HIGH) {
      Serial.println("setup loop exit");
      delay(1000);
      break;
    }
  }

  exitBox();
  runTillIntersection();
  turnLeft();
  runTillIntersection();

}

void loop() {
  turnRight();
  runTillIntersection();
  runTillIntersection();
  turnRight();
  runTillIntersection();
  turnRight();
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  runTillIntersection();
  turnLeft();
  runTillIntersection();
  turnLeft();
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  runTillIntersection();
  turnRight();
  runTillIntersection();
  turnRight();
  runTillIntersection();
  runTillIntersection();
}
