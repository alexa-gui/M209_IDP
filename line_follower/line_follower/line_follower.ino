// Arduino Line Follower Robot Code

int L1 = 2;
int R1 = 3;
int L2 = 5;
int R2 = 6;
int button = 4;
int turnCounter = 0;

#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *leftMotor = AFMS.getMotor(2);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(1);

void setup() {

  Serial.begin(9600);  // set up Serial library at 9600 bps

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
  run_till_intersection();
}
void loop() {
  // followLine();

  // if((digitalRead(L2) == 1)||(digitalRead(R2) == 1)) {
  //   if(millis() - hysteris_time > 500){
  //     switch(turnCounter){
  //       case 0:
  //         turnLeft();
  //         break;
  //       case 3:
  //         hysteris_time = millis();
  //         break;
  //       case 6:
  //         while(1) {
  //           stop();
  //         }
  //         break;
  //       default:
  //         turnRight();
  //         break;
  //     }
  //     turnCounter += 1;
  //   }
  // }
}

uint32_t hysteris_time=0;
#define INTERSECTION_DLY 1000
bool is_intersection(){
	if(millis() - hysteris_time <= INTERSECTION_DLY)
		return false;
	bool intersection_raw = (digitalRead(L2) || digitalRead(R2));
	if (intersection_raw){
		hysteris_time = millis();
	}
	return (digitalRead(L2) || digitalRead(R2));
}

void run_till_intersection(){
	while(!is_intersection()){
		followLine();
	}
	stop();
}



void turnRight() {  //turnRight

  // leftMotor->setSpeed(50);
  // rightMotor->setSpeed(50);
  leftMotor->run(FORWARD);
  rightMotor->run(BACKWARD);

  while (1) {
    if(digitalRead(R1) == 1) {
      break;
    }
  }
}

void turnLeft() {  //turnLeft

  // leftMotor->setSpeed(50);
  // rightMotor->setSpeed(50);
  leftMotor->run(BACKWARD);
  rightMotor->run(FORWARD);

  while (1) {
    if(digitalRead(L1) == 1) {
      break;
    }
  }
}

void sweep() {
  uint32_t startTime;

  leftMotor->setSpeed(150);
  rightMotor->setSpeed(150);

  while(1) {
    adjLeft();
    startTime = millis();
    while((millis() - startTime) < 1000) {
      if((digitalRead(L1) == 1)||(digitalRead(R1) == 1)) {
        goto end_sweep;
      }
    }
    adjRight();
    startTime = millis();
    while((millis() - startTime) < 2000) {
      if((digitalRead(L1) == 1)||(digitalRead(R1) == 1)) {
        goto end_sweep;
      }
    }
    adjLeft();
    startTime = millis();
    while((millis() - startTime) < 1000) {
      if((digitalRead(L1) == 1)||(digitalRead(R1) == 1)) {
        goto end_sweep;
      }
    }
  }
  end_sweep:
    leftMotor->setSpeed(255);
    rightMotor->setSpeed(255);
    return;
}

void exitBox() {
  bool exitLeft = 0;
  bool exitRight = 0;
  uint32_t startTime;

  forward();

  while((exitLeft == 0)||(exitRight == 0)) {
    if(digitalRead(L2) == 1) {
      exitLeft = 1;
    }
    if(digitalRead(R2) == 1) {
      exitRight = 1;
    }
  }

  delay(500);
  startTime = millis();
  while((millis() - startTime) < 500) {
    if((digitalRead(L2) == 1)||(digitalRead(R2) == 1)) {
      break;
    }
  }
  stop();
  sweep();
}

void followLine() {
  if ((digitalRead(R1) == 0) && (digitalRead(L1) == 0)) { forward(); }  //if Right Sensor and Left Sensor are at black color then it will call forword function

  if ((digitalRead(R1) == 1) && (digitalRead(L1) == 0)) { adjRight(); }  //if Right Sensor is white and Left Sensor is black then it will call turn Right function

  if ((digitalRead(R1) == 0) && (digitalRead(L1) == 1)) { adjLeft(); }  //if Right Sensor is black and Left Sensor is white then it will call turn Left function

  if ((digitalRead(R1) == 1) && (digitalRead(L1) == 1)) { forward(); }  //if Right Sensor and Left Sensor are at white color then it will call stop function
}
