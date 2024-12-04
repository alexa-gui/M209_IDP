#include <Servo.h>
// extern Servo grabber;
// extern Servo lifter;
extern int Crash1, Crash2;

void grabberOpen(){
	grabber.write(90);
}

void grabberClose(){  
  grabber.write(90);
  int pos = 90;
  while(digitalRead(Crash1) && digitalRead(Crash2) && pos != 0){
    ledFlash();
    grabber.write(pos--);
    delay(10);
  }
}

void grabberUp(){
	lifter.write(35);
}

void grabberDown(){
	lifter.write(2);
}

void pickUpBox() {
  grabberOpen();
  delay(500);
  grabberDown();
  delay(500);
  grabberClose();
  grabberUp();
}