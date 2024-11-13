#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *leftMotor = AFMS.getMotor(2);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(1);

void setup() {

  Serial.begin(9600);  // set up Serial library at 9600 bps

  pinMode(LED, OUTPUT);
  pinMode(L1, INPUT);
  pinMode(R1, INPUT);
  pinMode(button, INPUT);

  if (!AFMS.begin()) {  // create with the default frequency 1.6KHz
                        // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1)
      ;
  }
  Serial.println("Motor Shield found.");

  // Set the speed to start, from 0 (off) to 255 (max speed)
  leftMotor->setSpeed(255);
  rightMotor->setSpeed(255);
  Serial.println("speed set");
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);

  Serial.println("entering while loop");
  while (1) {
    if (digitalRead(button) == HIGH) {
      Serial.println("setup loop exit");
      delay(1000);
      break;
    }
  }

  exitBox();
  run_till_intersection();
  turnRight();
  digitalWrite(LED, LOW);
  run_till_intersection();
  turnLeft();
  digitalWrite(LED, LOW);
  run_till_intersection();
  turnLeft();
  digitalWrite(LED, LOW);
  run_till_intersection();
  digitalWrite(LED, LOW);
  run_till_intersection();
  turnLeft();
  digitalWrite(LED, LOW);
  run_till_intersection();
  turnLeft();
  digitalWrite(LED, LOW);
  run_till_intersection();
  turnRight();
  digitalWrite(LED, LOW);
  run_till_intersection();
  digitalWrite(LED, LOW);
}
void loop() {
  // followLine();

  // if((digitalRead(L2) == 1)||(digitalRead(R2) == 1)) {
  //   if(millis() - hysteris_time > 500){
  //     switch(turnCounter){
  //       case 0:
  //         turnLeft();
  //         break;
  //       case 3:
  //         hysteris_time = millis();
  //         break;
  //       case 6:
  //         while(1) {
  //           stop();
  //         }
  //         break;
  //       default:
  //         turnRight();
  //         break;
  //     }
  //     turnCounter += 1;
  //   }
  // }
}
