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
  bool box1_failed = false;
  if(!runTillIntersectionOrBox()){
    box1_failed = true;
  }else{
    runTillIntersection();
  }
  digitalWrite(LED_YEL, HIGH);
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
  digitalWrite(LED_YEL, HIGH);
  //runTillIntersection();
  // turnLeft();
  // delay(500);
  turn180();
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
  turnLeft();
  if(!runTillIntersectionOrBox()){
    goto box4_path;
  }
  digitalWrite(LED_YEL, HIGH);
  
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
  turnRight();
  if(!runTillIntersectionWithBox()){
    goto home_path;
  }
  digitalWrite(LED_YEL, HIGH);
  turn180();
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

  // return to start
  runTillIntersection();
  runTillIntersection();
  turnLeft();
  runTillIntersection();
  turnRight();
  runTillIntersection();
  turnRight();
  home_path:
  runTillIntersection();
  turnLeft();
  runTillIntersection();
  runTillTimed(1000);
  stop();
}

extern uint32_t hysteris_time;

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
  hysteris_time = millis();
}

void testGoToCenter() {
  goToCenter(1);
  goToCenter(0);
}