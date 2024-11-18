#include "line_follower.h"

void test_route() {
  /*setup routine:
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