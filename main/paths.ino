#include "line_follower.h"

extern int LED_YEL;
extern uint32_t hysteris_time;

void testRouteLoop() {
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
  // exitBox();
  bool box1_failed = false;
  if(!runTillIntersectionOrBox()) {
    box1_failed = true;
  }
  else{
    runTillIntersection();
  }
  //digitalWrite(LED_YEL, HIGH);
  turnLeft();
  runTillIntersection();
  turnRight();
  runTillIntersection();
  runTillIntersection();
  turnRight();
  runTillIntersection();
  turnRight();
  // adjSpeed(100);
  if(!box1_failed){
  goToCenter(1);
  }
  // adjSpeed(255);

  //Box 2
  runTillIntersection();
  if(!runTillIntersectionOrBox()){
    goto box3_path;
  }
  //digitalWrite(LED_YEL, HIGH);
  //runTillIntersection();
  // turnLeft();
  // delay(500);
  runTillIntersection();
  turnLeft();
  delay(500);
  turnLeft();
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  delay(500);
  turnLeft();
  backOutTillIntersection();
  goToCenter(0);

  //Box 3
  runTillIntersection();
  runTillIntersection();
  box3_path:
  turnSlightLeft();
  if(!runTillIntersectionOrBox()){
    goto box4_path;
  }
  //digitalWrite(LED_YEL, HIGH);

  turn180();
  runTillIntersection();
  turnRight();
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  delay(500);
  turnLeft();
  backOutTillIntersection();
  goToCenter(1);

  //Box 4
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  runTillIntersection();
box4_path:
  turnRight();
  runTillIntersection();
  turnSlightRight();
  if(!runTillIntersectionOrBox()){
    goto box5_path;
  }
  //digitalWrite(LED_YEL, HIGH);
  // turn180();
  // turn left with no rising edge
  adjLeft();

  delay(50);
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
  delay(500);
  turnLeft();
  backOutTillIntersection();
  goToCenter(0);
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
  if(findBox()){
    faceBox();
    runTillEvent();
    backOutTillIntersection();
    turnLeft();
    runTillIntersection();
    turnRight();
    runTillIntersection();
    runTillIntersection();
    turnRight();
    runTillIntersection();
    turnRight();
    goToCenter(1);
  } else{
    turnRight();
    runTillIntersection();
    turnRight();
    runTillIntersection();
    turnLeft();
    delay(500);
    turnLeft();
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
  turnLeft();
  delay(500);
  turnLeft();
  // runTillTimed(1000);
  // stop();
}

void testBox3() {
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  if(!runTillIntersectionOrBox()){
    turnLeft();
    delay(500);
    turnLeft();
  }
  turn180();
  runTillIntersection();
  turnRight();
  runTillIntersection();
  stop();
  delay(1000);
  hysteris_time = millis();
  runTillIntersection();
  turnLeft();
  delay(500);
  turnLeft();
  backOutTillIntersection();
  goToCenter(1);
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
  hysteris_time = millis();
}

void testGoToCenter() {
  goToCenter(1);
  goToCenter(0);
}
