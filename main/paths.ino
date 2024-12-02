#include "line_follower.h"
#include "grabber.h"

// extern int LED_YEL;
extern uint32_t hysteris_time;

void testRouteLoop() {
  /*
  setup routine:
    exitBox();
    runTillIntersection();
    turnLeft();
  */

  while (1) {
    runTillIntersection();
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
  }
}

extern int Magnetic1, Magnetic2;
void competitionRoute() {
  /*
  Route to be followed in competition
  */

  //Box 1
  bool box1_failed = false;
  if (!runTillIntersectionOrBox()) {
    box1_failed = true;
  } 
  else {
    pickUpBox();
    runTillIntersection();
  }
  turnLeft();
  runTillIntersection();
  turnRight();
  runTillIntersection();
  runTillIntersection();
  turnRight();
  runTillIntersection();
  turnRight();
  if (!box1_failed) {
    // if box 1 detected, drive to delivery center
    goToCenter(digitalRead(Magnetic1) || digitalRead(Magnetic2));
  }

  //Box 2
  runTillIntersection();
  hysteris_time = millis();
  if (!runTillIntersectionOrBox()) {
    // if not found box 2, continue onto box 3 without going back
    goto box3_path;
  }
  stop();
  pickUpBox();
  runTillIntersection();
  turnLeft();
  delayWithFlash(500);
  turnLeft();
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  delayWithFlash(500);
  turnLeft();
  backOutTillIntersection();
  goToCenter(digitalRead(Magnetic1) || digitalRead(Magnetic2));

  //Box 3
  runTillIntersection();
  runTillIntersection();
box3_path:
  turnSlightLeft();
  hysteris_time = millis();
  if (!runTillIntersectionOrBox()) {
    // if not found box 3, continue onto box 4 without going back
    goto box4_path;
  }
  stop();
  pickUpBox();

  turn180();
  runTillIntersection();
  turnRight();
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  delayWithFlash(500);
  turnLeft();
  backOutTillIntersection();
    goToCenter(digitalRead(Magnetic1) || digitalRead(Magnetic2));

  //Box 4
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  runTillIntersection();
box4_path:
  turnRight();
  runTillIntersection();
  turnSlightRight();
  hysteris_time = millis();
  if (!zigzagRunTillIntersectionOrBox()) {
    // if not found box 4, continue onto box 5 without going back
    goto box5_path;
  }
  stop();
  pickUpBox();
  // turn left with no rising edge
  adjLeft();
  delayWithFlash(50);
  while (1) {
    if (adcRead(L1) == 1) {
      break;
    }
  }
  runTillIntersection();
  turnLeft();
  runTillIntersection();
  turnLeft();
  runTillIntersection();
  turnRight();
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  delayWithFlash(500);
  turnLeft();
  backOutTillIntersection();
  goToCenter(digitalRead(Magnetic1) || digitalRead(Magnetic2));

  // box 5: offline box close to home
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  runTillIntersection();
  turnRight();
  runTillIntersection();
  turnSlightRight();
  runTillIntersection();
box5_path:
  if (findBox()) {
    // detected box, pick up and go to drop off center
    collectBox();
    turnLeft();
    runTillIntersection();
    turnRight();
    runTillIntersection();
    runTillIntersection();
    turnRight();
    runTillIntersection();
    turnRight();
    goToCenter(digitalRead(Magnetic1) || digitalRead(Magnetic2));
  } else {
    // didn't detect box, run back to finish box and turn around to complete loop
    turnRight();
    runTillIntersection();
    turnRight();
    runTillIntersection();
    runTillTimed(1000);
    stop();
    // turnLeft();
    // delayWithFlash(500);
    // turnLeft();
    return;
  }

  // return to start
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  runTillIntersection();
  turnRight();
  runTillIntersection();
  turnRight();
  runTillIntersection();
home_path:
  turnLeft();
  runTillIntersection();
  // turnLeft();
  // delay(500);
  // turnLeft();
  runTillTimed(1000);
  stop();
}

void testBox3() {
  /*
  Run as loop from goToCenter origin, picks up box 3 and drops at center
  */

  runTillIntersection();
  runTillIntersection();
  turnLeft();
  if (!runTillIntersectionOrBox()) {
    turnLeft();
    delayWithFlash(500);
    turnLeft();
  }
  turn180();
  runTillIntersection();
  turnRight();
  runTillIntersection();
  stop();
  delayWithFlash(1000);
  hysteris_time = millis();
  runTillIntersection();
  turnLeft();
  delayWithFlash(500);
  turnLeft();
  backOutTillIntersection();
  goToCenter(1);
}
extern int GreenLED, RedLED;
void goToCenter(bool is_magnetic) {
  /*
  Starts and ends at top T-junction between centers, facing away from the wall
  Delivers the box to the corresponding delivery center depending on is_magnetic
  */

  if (is_magnetic) {
    digitalWrite(RedLED, HIGH);
    runTillIntersection();
    turnSlightRight();
    runTillTimed(2000);
    grabberOpen();
    grabberDown();
    delayWithFlash(1000);
    grabberUp();
    delayWithFlash(500);
    grabberClose();
    digitalWrite(RedLED, LOW);
    // digitalWrite(LED_YEL, LOW);
    backOutTillIntersection();
    turnRight();
    runTillIntersection();
    turnLeft();
    delayWithFlash(500);
    turnLeft();
    backOutTillIntersection();
  } else {
    digitalWrite(GreenLED, HIGH);
    turnSlightLeft();
    runTillIntersection();
    // turnSlightRight();
    turnRight();
    runTillTimed(2000);
    grabberOpen();
    grabberDown();
    delayWithFlash(1000);
    grabberUp();
    delayWithFlash(500);
    grabberClose();
    digitalWrite(GreenLED, LOW);
    // digitalWrite(LED_YEL, LOW);
    backOutTillIntersection();
    turnSlightRight();
    runTillIntersection();
    turnLeft();
  }
  stop();
  hysteris_time = millis();
}

void testGoToCenter() {
  /*
  Run as loop from goToCenter origin, goes continually from one center to other
  */

  goToCenter(1);
  goToCenter(0);
}
