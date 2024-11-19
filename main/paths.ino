#include "line_follower.h"

extern int LED_YEL;

void testRoute() {
  /*
  setup routine:
    exitBox();
    runTillIntersection();
    turnLeft();
  */
  while(1) {
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

void competitionRoute() {
  //Box 1
  exitBox();
  runTillEvent();
  digitalWrite(LED_YEL, HIGH);
  runTillIntersection();
  turnLeft();
  runTillIntersection();
  turnRight();
  runTillIntersection();
  runTillIntersection();
  turnRight();
  runTillIntersection();
  turnRight();
  goToCenter(1);
  
  //Box 2
  runTillIntersection();
  runTillEvent();
  digitalWrite(LED_YEL, HIGH);
  turnLeft();
  delay(500);
  turnLeft();
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  delay(500);
  turnLeft();
  goToCenter(0);

  //Box 3
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  runTillEvent();
  digitalWrite(LED_YEL, HIGH);
  runTillIntersection();
  turnLeft();
  runTillIntersection();
  turnLeft();
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  goToCenter(1);

  //Box 4
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  runTillIntersection();
  turnRight();
  runTillIntersection();
  turnRight();
  runTillEvent();
  digitalWrite(LED_YEL, HIGH);
  turnLeft();
  runTillIntersection();
  turnLeft();
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  goToCenter(0);

  stop();
}

void goToCenter(bool is_magnetic) {
  /*
  Starts and ends at top T-junction between centers, facing away from the wall
  */
  
  if(is_magnetic) {
    runTillIntersection();
    turnSlightRight();
    runTillTimed(1400);
    digitalWrite(LED_YEL, LOW);
    backOutTillIntersection();
    turnRight();
    runTillIntersection();
    turnLeft();
    delay(500);
    turnLeft();
    backOutTillIntersection();
  }
  else {
    turnSlightLeft();
    runTillIntersection();
    turnSlightRight();
    runTillTimed(1400);
    digitalWrite(LED_YEL, LOW);
    backOutTillIntersection();
    turnSlightRight();
    runTillIntersection();
    turnLeft();

  }
  stop();
  delay(2000);
}

void testGoToCenter() {
  runTillIntersection();
  turnRight();

  runTillIntersection();
  runTillIntersection();
  turnRight();

  runTillIntersection();
  turnRight();
  goToCenter(1);
  goToCenter(0);
}