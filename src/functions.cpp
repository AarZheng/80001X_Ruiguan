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

void intakeStore(bool sort, bool isBlue) {
  Controller.Screen.clearScreen();
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print(Brain.timer(sec));
  if(sort && 
  ((isBlue == true && colorSorter.hue() > 0 && colorSorter.hue() < 30) || 
  (isBlue == false && colorSorter.hue() > 180 && colorSorter.hue() < 240))) {
    intakeCommand = true;
    hood.open();
    intakeFront.spin(fwd, 100, pct);
    intakeBack.spin(fwd, 100, pct);
    intakeTop.spin(fwd, 100, pct);
    wait(350, msec);
    intakeCommand = false;
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

void outtake() {
  intakeFront.spin(reverse, 100, pct);
  intakeBack.spin(fwd, 100, pct);
  intakeTop.spin(reverse, 100, pct);
  agitator.spin(fwd, 100, pct);
}

void intakeScoreTop() {
  hood.open();
  intakeMotors.spin(fwd, 100, pct);
}

void intakeScoreMid() {
  intakeFront.spin(fwd, 100, pct);
  intakeBack.spin(fwd, 100, pct);
  intakeTop.spin(reverse, 100, pct);
  agitator.spin(fwd, 100, pct);
}