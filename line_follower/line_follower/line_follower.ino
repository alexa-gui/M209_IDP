// Arduino Line Follower Robot Code

int L_S = 2;
int R_S = 3;
int button = 4;

#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *leftMotor = AFMS.getMotor(2);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(1);

void setup() {

  Serial.begin(9600);  // set up Serial library at 9600 bps

  pinMode(L_S, INPUT);
  pinMode(R_S, INPUT);
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

  /*turnLeft();
  while(1){
    if(digitalRead(L_S) == 1){
      break;
    }
  }*/
}

void loop() {
  if (digitalRead(button) == HIGH) {
    turnLeft();
    while (1) {
      if (digitalRead(L_S) == 1) {
        break;
      }
    }
  }

  if ((digitalRead(R_S) == 0) && (digitalRead(L_S) == 0)) { forward(); }  //if Right Sensor and Left Sensor are at black color then it will call forword function

  if ((digitalRead(R_S) == 1) && (digitalRead(L_S) == 0)) { correctRight(); }  //if Right Sensor is white and Left Sensor is black then it will call turn Right function

  if ((digitalRead(R_S) == 0) && (digitalRead(L_S) == 1)) { correctLeft(); }  //if Right Sensor is black and Left Sensor is white then it will call turn Left function

  if ((digitalRead(R_S) == 1) && (digitalRead(L_S) == 1)) { forward(); }  //if Right Sensor and Left Sensor are at white color then it will call Stop function
}

void forward() {  //forword

  // leftMotor->setSpeed(150);
  // rightMotor->setSpeed(150);
  leftMotor->run(BACKWARD);
  rightMotor->run(BACKWARD);
}

void correctRight() {  //turnRight

  // leftMotor->setSpeed(50);
  // rightMotor->setSpeed(50);
  leftMotor->run(FORWARD);
  rightMotor->run(BACKWARD);
}

void turnRight() {  //turnRight

  // leftMotor->setSpeed(50);
  // rightMotor->setSpeed(50);
  leftMotor->run(RELEASE);
  rightMotor->run(BACKWARD);
}

void correctLeft() {  //turnLeft

  // leftMotor->setSpeed(50);
  // rightMotor->setSpeed(50);
  leftMotor->run(BACKWARD);
  rightMotor->run(FORWARD);
}

void turnLeft() {  //turnLeft

  // leftMotor->setSpeed(50);
  // rightMotor->setSpeed(50);
  leftMotor->run(BACKWARD);
  rightMotor->run(RELEASE);
}

void Stop() {  //stop

  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);
}
