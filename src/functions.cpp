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
  if(sort && 
  ((isBlue == true && colorSorter.hue() > 0 && colorSorter.hue() < 20) || 
  (isBlue == false && colorSorter.hue() > 180 && colorSorter.hue() < 240))) {
    intakeCommand = true;
    hood.open();
    intakeFront.spin(fwd, 100, pct);
    intakeBack.spin(fwd, 100, pct);
    intakeTop.spin(fwd, 100, pct);
    wait(250, msec);
    intakeCommand = false;
    printf("Sorted");
  }
  else {
    hood.close();
    intakeFront.spin(fwd, 100, pct);
    intakeBack.spin(fwd, 100, pct);
    intakeTop.spin(fwd, 100, pct);
  }
}

void intakeStore(bool isBlue) {
  intakeStore(true, isBlue);
}

void outtake(bool slowed) {
  if(slowed) {
    intakeFront.spin(reverse, 33, pct);
    intakeBack.spin(fwd, 33, pct);
    intakeTop.spin(reverse, 33, pct);
    agitator.spin(fwd, 20, pct);
  }
  else {
    intakeFront.spin(reverse, 100 * 0.8, pct);
    intakeBack.spin(fwd, 67 * 0.8, pct);
    intakeTop.spin(reverse, 100 * 0.8, pct);
    agitator.spin(fwd, 75 * 0.8, pct);
  }
}

void intakeScoreTop(bool sort, bool isBlue) {
  // if(sort && 
  // // ((isBlue == true && colorSorter.hue() > 0 && colorSorter.hue() < 30) || 
  // // (isBlue == false && colorSorter.hue() > 180 && colorSorter.hue() < 240))) {
  // //   intakeCommand = true;
  // //   hood.close();
  // //   // intakeMotors.spin(fwd, 50, pct);
  // //   intakeBack.spin(fwd, 100, pct);
  // //   intakeTop.spin(fwd, 100, pct);
  // //   agitator.spin(fwd, 25, pct);
  // //   intakeFront.stop();
  // //   wait(350, msec);
  // //   intakeCommand = false;
  // // }
  // // else if ((isBlue == false && colorSorter.hue() > 0 && colorSorter.hue() < 30) || 
  // //   (isBlue == true && colorSorter.hue() > 180 && colorSorter.hue() < 240)) {
  // //   hood.open();
  // //   intakeMotors.spin(fwd, 100, pct);
  // // }
  // // else if(!sort) {
  // //   hood.open();
  // //   intakeMotors.spin(fwd, 100, pct);
  // // }
  // // else {
    hood.open();
    intakeMotors.spin(fwd, 100, pct);
  // }
}

void intakeScoreTop(bool isBlue) {
  intakeScoreTop(true, isBlue);
}

void intakeScoreMid(double speed) {
  intakeFront.spin(fwd, speed * 0.4, pct);
  intakeBack.spin(fwd, speed, pct);
  intakeTop.spin(reverse, speed * 0.75, pct);
  agitator.spin(fwd, speed, pct);
}

float sensorFilter(distance sensor, float odomValue, bool negative) { //Simple low-pass filter to remove inconsistent values

  float sensorValue;

  if(sensor.objectDistance(inches) == frontDist.objectDistance(inches)) {
    sensorValue = frontDist.objectDistance(inches) + 6;
    printf("Sensor selection: front");
  }
  else if(sensor.objectDistance(inches) == backDist.objectDistance(inches)) {
    sensorValue = backDist.objectDistance(inches) + 7;
    printf("Sensor selection: back");
  }
  else if(sensor.objectDistance(inches) == leftDist.objectDistance(inches)){
    sensorValue = leftDist.objectDistance(inches) + 6.5;
    printf("Sensor selection: left");
  }
  else {
    sensorValue = rightDist.objectDistance(inches) + 6.5;
    printf("Sensor selection: right");
  }

  printf("Sensor value: %f\n", sensorValue);

  if(!negative && fabs((72 - sensorValue - odomValue) / odomValue) < 0.4) { //Distance sensor reading is somewhat similar to odom estimation
    return 72 - sensorValue;
  }
  else if(negative && fabs((-72 + sensorValue - odomValue) / odomValue) < 0.4) {
    return -72 + sensorValue;
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