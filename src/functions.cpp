#include "vex.h"
#include "functions.h"
#include <atomic>

std::atomic<bool> sorting(false);

int autoIntake(void *isBlue) {
  while(isAuto) {
    intakeStore(true, *(bool *)isBlue);
    wait(5, msec);
  }
  return 0;
}

int autoScore(void *isBlue) {
  while(isAuto) {
    intakeScoreTop(true, *(bool *)isBlue);
    wait(5, msec);
  }
  return 0;
}

void intakeStore(bool sort, bool isBlue) {

  ramp.close();
  flapsMotor.spin(fwd, 100, pct);

  if(!sort) {
    intakeCommand = false;
    hoodMotor.stop(hold);
    return;
  }

  // Detect wrong color
  bool wrongColor =
    (sort &&
    ((isBlue && colorSorter.hue() > 0 && colorSorter.hue() < 16) ||
     (!isBlue && colorSorter.hue() > 180 && colorSorter.hue() < 240)));

  // If wrong color is detected again, extend the ejection duration
  if (wrongColor) {
    ejectEndTime = Brain.timer(msec) + 200;  // extend by 250ms
    intakeCommand = true;
    
  }

  // If currently in ejection period, keep ejecting
  if (Brain.timer(msec) < ejectEndTime) {
    hoodMotor.spin(fwd, 100, pct);
  }
  else {
    // Normal intake mode
    intakeCommand = false;
    hoodMotor.stop(hold);
  }
}

void intakeStore(bool isBlue) {
  intakeStore(true, isBlue);
}

void outtake(bool slowed) {
  intakeMotors.spin(reverse, 100, pct);
}

void intakeScoreTop(bool sort, bool isBlue) {
  ramp.close();
  intakeMotors.spin(fwd, 100, pct);

  /*
  if(sort) {
    bool wrongColor =
    (sort &&
    ((isBlue && colorSorter.hue() > 0 && colorSorter.hue() < 16) ||
     (!isBlue && colorSorter.hue() > 180 && colorSorter.hue() < 240)));
     if(wrongColor) {
       intakeMotors.stop();
     }
     else {
       ramp.close();
      intakeMotors.spin(fwd, 100, pct);
     }
  }
  else {
    ramp.close();
    intakeMotors.spin(fwd, 100, pct);
  }
  */
}

void intakeScoreTop(bool isBlue) {
  intakeScoreTop(true, isBlue);
}

void intakeScoreMid(double speed) {
  ramp.open();
  flapsMotor.spin(fwd, speed, pct);
  // hoodMotor.stop(hold);
  hoodMotor.spin(reverse, 10, pct);
}

float correctedDistance(float rawDist, float robotHeading, float expectedHeading) {
    float angleError = (robotHeading - expectedHeading) * M_PI / 180.0; // radians
    return rawDist * cos(angleError);
}

float sensorFilter(distance sensor, float odomValue, bool negative) {

  float sensorValue;

  // Select which sensor is being used & apply offset
  if(sensor.objectDistance(inches) == frontDist.objectDistance(inches)) {
    sensorValue = frontDist.objectDistance(inches) + 2;
    printf("Sensor selection: front\n");
  }
  else if(sensor.objectDistance(inches) == backDist.objectDistance(inches)) {
    sensorValue = backDist.objectDistance(inches) + 4;
    printf("Sensor selection: back\n"); 
  }
  else if(sensor.objectDistance(inches) == leftDist.objectDistance(inches)){
    sensorValue = leftDist.objectDistance(inches) + 6;
    printf("Sensor selection: left\n");
  }
  else {
    sensorValue = rightDist.objectDistance(inches) + 6;
    printf("Sensor selection: right\n");
  }

  // Expected cardinal heading (robot snaps to nearest 90°)
  int expectedHeading = std::round(chassis.get_absolute_heading() / 90.0) * 90;
  float robotHeading = chassis.get_absolute_heading();

  // Apply trig correction
  float corrected = correctedDistance(sensorValue, robotHeading, expectedHeading);

  printf("Raw sensor: %f | Corrected: %f\n", sensorValue, corrected);

  // Original consistency check, but using corrected distance
  if(!negative && fabs((72 - corrected - odomValue) / odomValue) < 0.4) {
    return 72 - corrected;
  }
  else if(negative && fabs((-72 + corrected - odomValue) / odomValue) < 0.4) {
    return -72 + corrected;
  }
  else {
    printf("ERROR: Distance failed \n");
    printf("Sensor installed: %s\n", sensor.installed() ? "true" : "false");
    return odomValue;
  }
}


void distanceReset(int quadrant) {
  if(quadrant == 0) { //auto-select quadrant
    if(chassis.get_X_position() > 0) {
      if(chassis.get_Y_position() > 0) {
        quadrant = 1;
      }
      else if(chassis.get_Y_position() < 0) {
        quadrant = 4;
      }
    }
    else if(chassis.get_X_position() < 0) {
      if(chassis.get_Y_position() > 0) {
        quadrant = 2;
      }
      else if(chassis.get_Y_position() < 0) {
        quadrant = 3;
      }
    }

    printf("Quadrant selected: %i\n", quadrant);
  }

  int resetAngle = std::round(chassis.get_absolute_heading() / 90.0);
  if(resetAngle == 360) resetAngle = 0;
  printf("Heading detected as: %i\n", resetAngle * 90);
  printf("Actual heading: %f\n", chassis.get_absolute_heading());

  printf("Position updated from: X = %f, Y = %f\n", chassis.get_X_position(), chassis.get_Y_position());

  switch (quadrant) {
    case 1:
      if(resetAngle == 0) { //0 deg
        chassis.odom.X_position = sensorFilter(rightDist, chassis.get_X_position(), false);
        chassis.odom.Y_position = sensorFilter(frontDist, chassis.get_Y_position(), false);
      }
      else if(resetAngle == 1) { //90 deg
        chassis.odom.X_position = sensorFilter(frontDist, chassis.get_X_position(), false);
        chassis.odom.Y_position = sensorFilter(leftDist, chassis.get_Y_position(), false);
      }
      else if(resetAngle == 2) { //180 deg
        chassis.odom.X_position = sensorFilter(leftDist, chassis.get_X_position(), false);
        chassis.odom.Y_position = sensorFilter(backDist, chassis.get_Y_position(), false);
      }
      else if(resetAngle == 3) { //270 deg
        chassis.odom.X_position = sensorFilter(backDist, chassis.get_X_position(), false);
        chassis.odom.Y_position = sensorFilter(rightDist, chassis.get_Y_position(), false);
      }
      break;
    case 2:
      if(resetAngle == 0) { //0 deg
        chassis.odom.X_position = sensorFilter(leftDist, chassis.get_X_position(), true);
        chassis.odom.Y_position = sensorFilter(frontDist, chassis.get_Y_position(), false);
      }
      else if(resetAngle == 1) { //90 deg
        chassis.odom.X_position = sensorFilter(backDist, chassis.get_X_position(), true);
        chassis.odom.Y_position = sensorFilter(leftDist, chassis.get_Y_position(), false);
      }
      else if(resetAngle == 2) { //180 deg
        chassis.odom.X_position = sensorFilter(rightDist, chassis.get_X_position(), true);
        chassis.odom.Y_position = sensorFilter(backDist, chassis.get_Y_position(), false);
      }
      else if(resetAngle == 3) { //270 deg
        chassis.odom.X_position = sensorFilter(frontDist, chassis.get_X_position(), true);
        chassis.odom.Y_position = sensorFilter(rightDist, chassis.get_Y_position(), false);
      }
      break;
    case 3:
      if(resetAngle == 0) { //0 deg
        chassis.odom.X_position = sensorFilter(leftDist, chassis.get_X_position(), true);
        chassis.odom.Y_position = sensorFilter(backDist, chassis.get_Y_position(), true);
      }
      else if(resetAngle == 1) { //90 deg
        chassis.odom.X_position = sensorFilter(backDist, chassis.get_X_position(), true);
        chassis.odom.Y_position = sensorFilter(rightDist, chassis.get_Y_position(), true);
      }
      else if(resetAngle == 2) { //180 deg
        chassis.odom.X_position = sensorFilter(rightDist, chassis.get_X_position(), true);
        chassis.odom.Y_position = sensorFilter(frontDist, chassis.get_Y_position(), true);
      }
      else if(resetAngle == 3) { //270 deg
        chassis.odom.X_position = sensorFilter(frontDist, chassis.get_X_position(), true);
        chassis.odom.Y_position = sensorFilter(leftDist, chassis.get_Y_position(), true);
      }
      break;
    case 4:
      if(resetAngle == 0) { //0 deg
        chassis.odom.X_position = sensorFilter(rightDist, chassis.get_X_position(), false);
        chassis.odom.Y_position = sensorFilter(backDist, chassis.get_Y_position(), true);
      }
      else if(resetAngle == 1) { //90 deg
        chassis.odom.X_position = sensorFilter(frontDist, chassis.get_X_position(), false);
        chassis.odom.Y_position = sensorFilter(rightDist, chassis.get_Y_position(), true);
      }
      else if(resetAngle == 2) { //180 deg
        chassis.odom.X_position = sensorFilter(leftDist, chassis.get_X_position(), false);
        chassis.odom.Y_position = sensorFilter(frontDist, chassis.get_Y_position(), true);
      }
      else if(resetAngle == 3) { //270 deg
        chassis.odom.X_position = sensorFilter(backDist, chassis.get_X_position(), false);
        chassis.odom.Y_position = sensorFilter(leftDist, chassis.get_Y_position(), true);
      }
      break;
  }
  printf("Position updated to: X = %f, Y = %f\n", chassis.get_X_position(), chassis.get_Y_position());
}

// static int skillsScoringState = 0;
// static int numBalls = 0;
// void scoreTopSkills() {
//   switch(skillsScoringState) {
//     case 0: //Scoring blue, counting

//     if(numBalls >= 6) {
//       skillsScoringState = 1;
//       numBalls = 0;
//       return;
//     }

//     if(colorSorter.hue() > 180 && colorSorter.hue() < 240) {
//       hood.close();
//       numBalls++;
//       intakeCommand = true;
//       intakeFront.spin(fwd, 100, pct);
//       intakeBack.spin(fwd, 100, pct);
//       intakeTop.spin(fwd, 100, pct);
//       wait(250, msec);
//       intakeCommand = false;
//     }

//     else if (colorSorter.hue() > 0 && colorSorter.hue() < 30){
//       hood.open();
//       intakeCommand = true;
//       intakeFront.spin(fwd, 100, pct);
//       intakeBack.spin(fwd, 100, pct);
//       intakeTop.spin(fwd, 100, pct);
//       wait(250, msec);
//       intakeCommand = false;
//     }
//     break;
//     case 1: //Scoring red, counting

//     if(numBalls >= 5) {
//       skillsScoringState = 2;
//       numBalls = 0;
//       return;
//     }

//     if(colorSorter.hue() > 0 && colorSorter.hue() < 30) {
//       hood.close();
//       numBalls++;
//       intakeCommand = true;
//       intakeFront.spin(fwd, 100, pct);
//       intakeBack.spin(fwd, 100, pct);
//       intakeTop.spin(fwd, 100, pct);
//       wait(250, msec);
//       intakeCommand = false;
//     }

//     else if (colorSorter.hue() > 180 && colorSorter.hue() < 240){
//       hood.open();
//       intakeCommand = true;
//       intakeFront.spin(fwd, 100, pct);
//       intakeBack.spin(fwd, 100, pct);
//       intakeTop.spin(fwd, 100, pct);
//       wait(250, msec);
//       intakeCommand = false;
//     }
//     break;
//     case 2:

//     break;
//   }
// }