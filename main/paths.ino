#include "line_follower.h"

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

void goToCenter(bool is_magnetic) {
  /*
  Starts and ends at top T-junction between centers, facing away from the wall
  */
  
  if(is_magnetic) {
    runTillIntersection();
    turnSlightRight();
    runTillTimed(1400);
    backOutTillIntersection();
    turnRight();
    runTillIntersection();
    turnLeft();
    turnLeft();
  }
  else {
    turnLeft();
    runTillIntersection();
    turnSlightRight();
    runTillTimed(1400);
    backOutTillIntersection();
    turnRight();
    runTillIntersection();
    turnLeft();

  }

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