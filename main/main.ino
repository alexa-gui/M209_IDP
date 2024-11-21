#include <Adafruit_MotorShield.h>
#include "line_follower.h"
#include "motor_control.h"
#include "box_finder.h"
#include "paths.h"
#include "Wire.h"
#include "DFRobot_VL53L0X.h"
//#include <Servo.h>

//Servo servo1;  // create servo object to control a servo

DFRobot_VL53L0X sensor;
// Arduino Line Follower Robot Code

int BlueLED = 4;
int LED_YEL = 5;
int L1 = A0;
int R1 = A1;
int L2 = A2;
int R2 = A3;
int button = 2;
int photo = 6;
int turnCounter = 0;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

extern bool is_moving;

ISR(TIMER0_COMPA_vect){//timer0 interrupt 2kHz toggles BlueLED
	static bool toggle = false;
	static int interrupt_count = 0;
	interrupt_count++;
	if (interrupt_count == 1000){
		if(!is_moving){
			digitalWrite(BlueLED,0);
			return;
		}
		digitalWrite(BlueLED,!toggle);
		toggle = !toggle;
		interrupt_count = 0;
	}
  if(digitalRead(button)) {
    stop();
    while(1);
  }
}

void setup() {
	// 2kHz interrupt
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  Serial.begin(9600);  // set up Serial library at 9600 bps

  // Initialize TOF
  Wire.begin();
  sensor.begin(0x50);
  sensor.setMode(sensor.eContinuous,sensor.eHigh);
  sensor.start();

 pinMode(BlueLED, OUTPUT);
 pinMode(LED_YEL, OUTPUT);
 digitalWrite(LED_YEL, LOW);
 pinMode(L1, INPUT);
 pinMode(R1, INPUT);
 pinMode(L2, INPUT);
 pinMode(R2, INPUT);
 pinMode(button, INPUT);
 pinMode(photo, INPUT);
 //servo1.attach(9);

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

  Serial.println("setup hold");
  while (1) {
    if (digitalRead(button) == HIGH) {
      Serial.println("setup exit");
      delay(1000);
      break;
    }
  }

  adjSpeed(255);
  // servo1.write(0);
  // delay(1000);
  // servo1.write(150);

  competitionRoute();
}

void loop() {
  //testGoToCenter();
}
