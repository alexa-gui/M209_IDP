#include <Servo.h>
#include <Adafruit_MotorShield.h>

Servo grabber;  // create servo object to control a servo
Servo lifter;
int crash1 = 2;
int crash2 = 3;


void setup() {

  lifter.attach(10);
  lifter.write(6);
  grabber.attach(11);
  // grabber.write(0);
  // delay(2000);
  grabber.write(90);
  // int pos = 90;
  // while(digitalRead(crash1) && digitalRead(crash2)){
  //   grabber.write(pos--);
  //   delay(10);
  // }
  // delay(1000);
  lifter.write(55);
  // delay(2000);
  // grabber.write(0);
  // lifter.write(10);
  // lifter.write(55);
  // pinMode(4, OUTPUT);
  // grabber.attach(11);  // attaches the servo on pin 9 to the servo object
  // digitalWrite(4,HIGH);
  // delay(100);
  // grabber.write(0);
  // digitalWrite(4,LOW);
  // delay(100);
  // lifter.attach(3);
  // digitalWrite(4,HIGH);
  // delay(100);
  // lifter.write(90);
  // digitalWrite(4,LOW);
  // delay(100);
  // delay(1000);
  // digitalWrite(4,HIGH);
  // delay(100);
  // grabber.write(160);
  // digitalWrite(4,LOW);
  // servo2.write(0);
  //   myservo.write(0);
  // delay(1000);
  // myservo.write(160);
  // delay(1000);
  // myservo.write(0);u
}
void loop() {
  /*for (pos = 0; pos <= 90; pos += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(90);  // tell servo to go to position in variable 'pos'
    delay(15);           // waits 15 ms for the servo to reach the position
  }
  for (pos = 90; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
    myservo.write(0);                  // tell servo to go to position in variable 'pos'
    delay(15);                           // waits 15 ms for the servo to reach the position
  }
  */

}