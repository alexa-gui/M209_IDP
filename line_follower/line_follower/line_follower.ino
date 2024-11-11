// Arduino Line Follower Robot Code

int L_S = 2;
int R_S = 3;
int button = 4;

#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

void setup(){ 

  Serial.begin(9600);           // set up Serial library at 9600 bps

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  // Set the speed to start, from 0 (off) to 255 (max speed)
  leftMotor->setSpeed(150);
  rightMotor->setSpeed(150); 

  while (1) {
    if (digitalRead(button) == HIGH) {
      break;
    }
  }

}

void loop(){  

if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0)){forward();}   //if Right Sensor and Left Sensor are at black color then it will call forword function

if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0)){turnRight();} //if Right Sensor is white and Left Sensor is black then it will call turn Right function  

if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1)){turnLeft();}  //if Right Sensor is black and Left Sensor is white then it will call turn Left function

if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 1)){Stop();} //if Right Sensor and Left Sensor are at white color then it will call Stop function

}

void forward(){  //forword

  leftMotor->run(FORWARD);
  rightMotor->run(BACKWARD);

}

void turnRight(){ //turnRight

  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);

}

void turnLeft(){ //turnLeft

  leftMotor->run(BACKWARD);
  rightMotor->run(BACKWARD);

}

void Stop(){ //stop

  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);

}
