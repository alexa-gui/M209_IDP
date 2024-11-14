#include <Adafruit_MotorShield.h>
#include "line_follower.h"
#include "motor_control.h"
#include "Wire.h"
#include "DFRobot_VL53L0X.h"

DFRobot_VL53L0X sensor;
// Arduino Line Follower Robot Code

int LED = 9;
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

extern bool is_moving;
ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
	static bool toggle = false;
	if(!is_moving){
		digitalWrite(LED,0);
		return;
	}
	digitalWrite(LED,!toggle);
	toggle = !toggle;
}

void setup() {

  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624>>2;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  Serial.begin(9600);  // set up Serial library at 9600 bps

  // Initialize TOF
  Wire.begin();
  sensor.begin(0x50);
  sensor.setMode(sensor.eContinuous,sensor.eHigh);
  sensor.start();

  pinMode(LED, OUTPUT);
 pinMode(L1, INPUT);
 pinMode(R1, INPUT);
 pinMode(L2, INPUT);
 pinMode(R2, INPUT);
 pinMode(button, INPUT);

  if (!AFMS.begin()) {  // create with the default frequency 1.6KHz
                        // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1)
      ;
  }
  Serial.println("Motor Shield found.");
  // Set the speed to start, from 0 (off) to 255 (max speed)
  leftMotor->setSpeed(LEFT_SLOW_RATIO(255));
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
  turnSlightRight();
  runTillTimed(1400);
  backOutTillIntersection();
  turnLeft();
  runTillIntersection();

  turnLeft();
  runTillIntersection();

  turnLeft();
  runTillIntersection();

  turnLeft();
  runTillIntersection();
  turnSlightLeft();
  runTillTimed(1400);
  backOutTillIntersection();
  turnRight();
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
