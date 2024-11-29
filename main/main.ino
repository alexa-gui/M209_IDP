#include <Adafruit_MotorShield.h>
#include "line_follower.h"
#include "motor_control.h"
#include "box_finder.h"
#include "paths.h"
#include "Wire.h"
#include "DFRobot_VL53L0X.h"
#include <Servo.h>

//Servo servo1;  // create servo object to control a servo

DFRobot_VL53L0X sensor;
// Arduino Line Follower Robot Code

int Crash1 = 2;
int Crash2 = 3;
int BlueLED = 4;
int RedLED = 5; 
int GreenLED = 6;
int L1 = A0;
int R1 = A1;
int L2 = A2;
int R2 = A3;
int button = 12;
int photo = 13;
int turnCounter = 0;
int Magnetic1 = 8;
int Magnetic2 = 9;
Servo grabber;
Servo lifter;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

extern bool is_moving;
// ISR(TIMER1_COMPA_vect){//timer1 interrupt 2Hz toggles BlueLED
// 	static bool toggle = false;
// 	if(!is_moving){
// 		digitalWrite(BlueLED,0);
// 		return;
// 	}
// 	digitalWrite(BlueLED,!toggle);
// 	toggle = !toggle;
//
//   if(digitalRead(button)) {
//     stop();
//     while(1);
//   }
// }

void setup() {
  // TCCR1A = 0;// set entire TCCR1A register to 0
  // TCCR1B = 0;// same for TCCR1B
  // TCNT1  = 0;//initialize counter value to 0
  // // set compare match register for 1hz increments
  // OCR1A = 15624>>2;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // // turn on CTC mode
  // TCCR1B |= (1 << WGM12);
  // // Set CS12 and CS10 bits for 1024 prescaler
  // TCCR1B |= (1 << CS12) | (1 << CS10);
  // // enable timer compare interrupt
  // TIMSK1 |= (1 << OCIE1A);
  Serial.begin(9600);  // set up Serial library at 9600 bps


 pinMode(BlueLED, OUTPUT);
 pinMode(RedLED, OUTPUT);
 pinMode(GreenLED, OUTPUT);
//  pinMode(LED_YEL, OUTPUT);
//  digitalWrite(LED_YEL, LOW);
 pinMode(L1, INPUT);
 pinMode(R1, INPUT);
 pinMode(L2, INPUT);
 pinMode(R2, INPUT);
 pinMode(button, INPUT);
//  pinMode(photo, INPUT);

  grabber.attach(11);
  lifter.attach(10);
  grabberUp();
  grabberClose();
  // Initialize TOF
  Wire.begin();
  sensor.begin(0x50);
  sensor.setMode(sensor.eContinuous,sensor.eHigh);
  sensor.start();
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
    Serial.println("setup loop");
    if (digitalRead(button) == HIGH) {
      Serial.println("setup exit");
      delay(1000);
      break;
    }
  }

  grabberOpen();
  delay(2000);
  adjSpeed(255);
  // servo1.write(0);
  // delay(1000);
  // servo1.write(150);

  exitBox();
  // runTillIntersection();
  // if(findBox()){
  //   faceBox();
  // }
  // runTillEvent();
}

void loop() {
  competitionRoute();
  // testBox3();
  //testGoToCenter();
}
