#include <Servo.h>
extern Servo grabber;
extern Servo lifter;
extern int Crash1, Crash2;

void grabberOpen(){
	// Open Grabber
	grabber.write(90);
}

void grabberClose(){
	// Close Grabber either until it hits 0 degrees or either crash sensor activate
  grabber.write(90);
  int pos = 90;
  while(digitalRead(Crash1) && digitalRead(Crash2) && pos != 0){
    ledFlash();
    grabber.write(pos--);
    delay(10);
  }
}

void grabberUp(){
	// Lifts the grabber up off the floor
	lifter.write(35);
}

void grabberDown(){
	// Turns the grabber onto the floor
	lifter.write(2);
}

void pickUpBox() {
	// Picks up a box starting from grabber up and open
  grabberOpen();
  delay(500);
  grabberDown();
  delay(500);
  grabberClose();
  grabberUp();
}
