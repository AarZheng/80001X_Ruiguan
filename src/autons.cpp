#include "vex.h"
#include "functions.h"
#include <iostream>

// std::cout << "";

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

 void printCoordinates() {
   printf("X pos: %f \n Y pos: %f \n Heading: %f \n", chassis.get_X_position(), chassis.get_Y_position(), chassis.get_absolute_heading());
 }

 thread intakeThread;

//Test function to tune wheel diameter and distance sensor offsets
 void temp(bool allColor) {
    chassis.set_coordinates(0, 0, 0); //Place robot exactly at -24, -24, 90 deg
    // distanceReset(0); //Based on distance reset output, tune distance sensor offsets
    // printf("Original Encoder: %f \n", chassis.get_ForwardTracker_position());
    chassis.drive_distance(72, 0, 8, 8, 0.5, 150, 2000); //Use this to tune wheel diameter. Overshoot --> increase diameter. Undershoot --> decrease
    printf("X: %f \n", chassis.get_X_position()); //Final positions
    printf("Y: %f \n", chassis.get_Y_position());
    // printf("Encoder: %f \n", chassis.get_ForwardTracker_position());
    // flapsMotor.spin(fwd, 100, pct);
    // chassis.drive_distance_to_wall(frontDist, 38, 0, 6.25, 1.5, 5, 0, 4000); //Testing drive distance with sensor
    
 }

 void rightCounter7Ball(bool allColor) {
  chassis.set_turn_exit_conditions(6, 75, 3000);
  hood.open();
  antler.open();
  isAuto = true;
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
    wait(20, msec);
  }

  chassis.set_coordinates(-48, -16, 90);
  intakeThread = thread(autoIntake, &allColor);
  distanceReset(0);
  chassis.turn_to_point(-20, -20);
  chassis.drive_to_point(-20, -20, 0, 3, 6, 3, 50, 2000);
  matchload.open();
  chassis.turn_to_point(-6, -48);
  matchload.close();
  chassis.drive_to_point(-6, -48, 0, 3, 3, 12, 50, 2000);
  matchload.open();
  chassis.left_swing_to_angle(170, 6, 4, 0, 2000, chassis.turn_kp, chassis.turn_ki, chassis.swing_kd, chassis.swing_starti);
  chassis.drive_distance(-4, 165, 3, 3, 1, 50, 2000);
  chassis.turn_to_angle(-90);
  distanceReset(0);
  chassisMotors.stop();
  matchload.close();
  // chassis.drive_distance(36, -95);
  chassis.drive_to_point(-24, -36);
  chassis.turn_to_angle(-85);
  distanceReset(0);
  chassis.drive_to_point(-10, -38, 0, 6, 4, 2, 100, 2000);
  chassis.turn_to_angle(-95);
  distanceReset(0);
  chassisMotors.stop();
  while(Brain.timer(sec) < 7.5) {
    wait(50, msec);
  }
  antler.close();
  chassis.drive_to_point(-40, -35, 0, 8, 6, 6, 50, 2000);
  // distanceReset(0);
  matchload.open();
  intakeThread.interrupt();
  // chassis.turn_to_point(-24, -48, 180, 9, 7, 0, 2000);
  // intakeMotors.spinFor(reverse, 160, deg, 500, rpm, false);
  intakeMotors.stop();
  chassis.drive_to_point(-24, -48, 0, 7, 9, 0, 0, 600);
  intakeThread.interrupt();
  intakeScoreTop(false);
  chassis.drive_distance(-10, -90, 6, 6, 0, 0, 650);
  wait(500, msec);
  distanceReset(0, true);
  matchload.open();
  chassis.drive_to_point(-60, -48, 0, 4.5, 4, 8, 0, 2000);
  intakeStore(false);
  chassis.drive_to_point(-72, -48, 0, 3, 2, 0, 0, 600);
  distanceReset(0);
  chassis.drive_distance(-10, -90, 6, 6, 6, 0, 2000);
  distanceReset(0);
  chassis.turn_to_point(-24, -24, 0, 9, 6, 0, 2000);
  matchload.close();
  chassis.drive_to_point(-24, -22, 0, 8, 6, 8, 0, 2000);
  lowGoal.open();
  intakeMotors.spin(reverse, 40, pct);
  chassis.drive_to_point(-9, -7, 0, 6, 5, 2, 50, 1000);
  intakeMotors.spin(reverse, 37, pct);
  chassis.turn_to_angle(45);
  chassisMotors.stop();

  // chassis.drive_distance(-3, 45, 2, 1, 1, 50, 2000);
  

  
  

 }

  void rightSawp(bool allColor) {

  chassis.set_turn_exit_conditions(6, 75, 3000); //Higher settle error to increase aggressiveness
  antler.open();
  hood.open();
  isAuto = true;
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
      wait(20, msec);
  }

  chassis.set_coordinates(-60, -4, 0);
  intakeStore(false);
  distanceReset(0);
  chassis.drive_distance(12, 0, 6, 2, 2, 50, 450);
  distanceReset(3);
  chassis.drive_to_point(-45, -48, 0, 10, 8, 4, 50, 2000);
  // chassis.drive_distance_to_wall(backDist, 20, 0, 6, 6, 4, 50, 2000);
  chassis.turn_to_point(-72, -48, 0, 9, 6, 50, 2000);
  matchload.open();
  distanceReset(0);
  chassis.drive_to_point(-72, -48, 0, 3, 2, 0, 0, 1150);
  distanceReset(0);
  chassis.drive_to_point(-24, -48, 0, 10, 8, 0, 0, 700);
  intakeScoreTop(false);
  chassis.drive_distance(-10, -90, 6, 6, 0, 0, 500);
  matchload.close();
  distanceReset(0);
  wait(500, msec);

  // chassis.drive_to_point(-40, -48, 0, 8, 6, 6, 0, 2000);
  // distanceReset(0);
  // chassis.turn_to_point(-24, -24, 0, 9, 15, 0, 2000);
  // chassis.left_swing_to_angle(0, 9, 7, 0, 2000, chassis.swing_kp, chassis.swing_ki, chassis.swing_kd, chassis.swing_starti);
  chassis.turn_to_point(-24, -24);
  intakeStore(false);
  distanceReset(0);
  // printf("X: %f \n Y: %f \n Heading: %f \n", chassis.get_X_position(), chassis.get_Y_position(), chassis.get_absolute_heading());
  hoodMotor.stop();
  // chassis.turn_to_point(-20, -20, 0, 9, 6, 0, 2000);
  chassis.drive_to_point(-24, -24, 0, 9, 6, 6, 0, 2000);
  // chassis.turn_to_point(-24, 24, 0, 9, 10, 0, 2000);
  chassis.drive_to_point(-25, 24, 0, 9, 6, 11, 0, 2000);
  matchload.open();
  

  chassis.drive_to_point(-48, 44, 0, 10, 10, 4, 50, 2000);
  hoodMotor.stop();
  intakeStore(false);
  // chassis.turn_to_angle(-90);
  chassis.turn_to_point(-24, 48, 180);
  distanceReset(0);
  chassis.drive_to_point(-24, 48, 0, 6, 8, 0, 0, 500);
  intakeThread.interrupt();
  intakeScoreTop(false);
  chassis.drive_distance(-10, -90, 6, 6, 0, 0, 500);
  distanceReset(0);
  wait(900, msec);

  // chassis.turn_to_point(-72, 48, 0, 9, 6, 0, 2000);
  distanceReset(0);
  // intakeThread = thread(autoIntake, &allColor);
  chassis.drive_to_point(-60, 48, 0, 5, 4, 8, 0, 2000);
  intakeStore(false);
  chassis.drive_to_point(-72, 48, 0, 2.5, 4, 0, 0, 550);
  distanceReset(0);
  chassis.drive_to_point(-48, 48, 0, 8, 6, 4, 50, 2000);
  distanceReset(0);
  // chassis.turn_to_point(0, 0, 180, );
  // chassis.drive_to_point(-12, 12, 0, 6, 4, 8, 0, 1000);
  // intakeMotors.spin(reverse, 25, pct);
  chassis.drive_to_point(-6, 5, 0, 9, 12, 12, 0, 2000);
  // intakeMotors.spinFor(reverse, 135, deg, 500, rpm);
  
  // chassis.drive_to_point(0, -4, 0, 2, 2, 0, 0, 300);
  // chassis.set_coordinates(-9, 9, chassis.get_absolute_heading());
  // matchload.open();
  intakeThread.interrupt();
  ramp.open();
  // intakeScoreMid(60);
  flapsMotor.spin(fwd, 70, pct);
  hoodMotor.spin(reverse, 70, pct);
  chassis.drive_to_point(0, -2, 0, 3, 3, 0, 0, 1000);
  // hoodMotor.spin(reverse, 100, pct);
  wait(1000, msec);

 }

 void right7Wing(bool allColor) {
  chassis.set_turn_exit_conditions(6, 50, 2000);
  antler.open();
  isAuto = true;
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
    wait(20, msec);
  }

  chassis.set_coordinates(-48, -16, 90);
  intakeThread = thread(autoIntake, &allColor);
  distanceReset(0);
  // chassis.drive_to_point(-24, -22, 0, 7, 5, 8, 0, 2000);
  // matchload.open();
  // // wait(200, msec);
  // // chassis.turn_to_point(-46, -46, 0, 9, 8, 0, 2000);
  // chassis.drive_to_point(-46, -46, 0, 8, 6, 6, 0, 2000);
  // chassis.turn_to_point(-72, -48);

  chassis.drive_to_point(-24, -23, 0, 7, 5, 10, 0, 2000);
  matchload.open();
  chassis.drive_to_point(-46, -40, 0, 8, 6, 6, 0, 2000);
  chassis.turn_to_angle(-90, 9, 6, 0, 2000);
  distanceReset(0);
  chassis.drive_to_point(-72, -48, 0, 3.5, 3, 0, 0, 1050);
  distanceReset(0);
  intakeMotors.spinFor(reverse, 40, deg, 500, rpm, false);
  chassis.drive_to_point(-24, -48, 0, 8, 1, 0, 0, 750);
  intakeThread.interrupt();
  intakeScoreTop(false, allColor);
  matchload.close();
  chassis.drive_distance(-10, -90, 6, 6, 0, 0, 750);
  distanceReset(0);
  wait(600, msec);

  chassis.drive_distance(12, -30, 7, 9, 4, 0, 2000);
  intakeThread.interrupt();
  intakeMotors.stop();
  antler.close();
  chassis.turn_to_angle(-77, 9, 10, 0, 2000);
  chassis.drive_distance(-24, -85, 5, 1, 6, 0, 3000);
  wait(200, msec);
  chassis.turn_to_angle(-100, 9, 0, 0, 10000);
  chassisMotors.stop(hold);
 }



 void left7Wing(bool allColor) {
   chassis.set_turn_exit_conditions(6, 50, 2000);
  antler.open();
  hood.open();
  isAuto = true;
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
    wait(20, msec);
  }

  chassis.set_coordinates(-48, 16, 90);
  intakeThread = thread(autoIntake, &allColor);
  distanceReset(0);
  chassis.drive_to_point(-24, 23, 0, 12, 6, 10, 0, 2000); //9
  matchload.open();
  chassis.drive_to_point(-46, 44, 0, 12, 8, 6, 0, 2000); //10
  chassis.turn_to_angle(-90, 9, 6, 0, 2000);
  distanceReset(0);
  chassis.drive_to_point(-72, 48, 0, 3.5, 3, 0, 0, 1100);
  // distanceReset(0);
  intakeMotors.spinFor(reverse, 40, deg, 500, rpm, false);
  chassis.drive_to_point(-24, 48, 0, 10, 8, 0, 0, 750);
  intakeThread.interrupt();
  intakeScoreTop(false, allColor);
  matchload.close();
  chassis.drive_distance(-10, -90, 6, 6, 0, 0, 1350);
  distanceReset(0);

  chassis.drive_distance(12, -30, 7, 9, 4, 0, 2000);
  intakeThread.interrupt();
  intakeMotors.stop();
  antler.close();
  chassis.turn_to_angle(-77, 9, 10, 0, 2000);
  chassis.drive_distance(-24, -85, 6, 6/5, 6, 0, 3000);
  wait(200, msec);
  chassis.turn_to_angle(-100, 9, 0, 0, 10000);
  chassisMotors.stop(hold);
 }

  void delayedRight7Wing(bool allColor) {
  wait(5, sec);
  right7Wing(allColor);
 }



 void delayedLeft7Wing(bool allColor) {
   wait(5, sec);
  left7Wing(allColor);
 }

void rightCenterLong(bool allColor) {
  antler.open();
  hood.open();
  isAuto = true;
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
    wait(20, msec);
  }

  chassis.set_coordinates(-48, -16, 180);
  intakeThread = thread(autoIntake, &allColor);
  distanceReset(0);
  chassis.drive_to_point(-48, -45, 0, 10, 8, 4, 50, 2000);
  matchload.open();
  chassis.turn_to_point(-72, -48, 0, 9, 6, 50, 2000);
  distanceReset(0);
  chassis.drive_to_point(-72, -48, 0, 3, 3, 0, 0, 1200);
  distanceReset(0);
  chassis.drive_to_point(-24, -48, 0, 6, 1, 0, 0, 750);
  distanceReset(0);
  intakeThread.interrupt();
  intakeScoreTop(false);
  chassis.drive_distance(-10, -90, 6, 10, 0, 0, 1000);
  distanceReset(0);
  chassisMotors.stop();
  matchload.close();
  intakeThread = thread(autoIntake, &allColor);
  distanceReset(0, true);
  chassis.turn_to_point(-24, -24);
  distanceReset(0);

  // intakeStore(true, allColor);
  // chassis.drive_to_point(-30, -29, 0, 6, 4, 14, 0, 2000);
  chassis.drive_to_point(-24, -24, 0, 4, 4, 3, 100, 2000);
  matchload.open();
  chassis.turn_to_point(0, 0);
  matchload.close();
  wait(50, msec);
  chassis.drive_to_point(-11, -12, 0, 6, 6, 3, 0, 2000);
  chassis.drive_to_point(-4, -5, 0, 4, 2, 2, 50, 750);
  chassis.turn_to_angle(45);
  intakeThread.interrupt();
  intakeMotors.stop();
  lowGoal.open();
  hoodMotor.spin(reverse, 100, pct);
  flapsMotor.spin(reverse, 150, rpm);
  chassis.drive_distance(-2, 0, 2, 0, 1, 50, 2000);
  chassisMotors.stop();
  wait(1600, msec);
  chassis.drive_to_point(-26, -36);
  antler.close();
  chassis.turn_to_angle(-75, 9, 6, 75, 2000);
  chassis.drive_distance(-30, -90, 5, 1, 6, 0, 3000);
  chassis.turn_to_angle(-90, 5, 0, 0, 10000);
  chassisMotors.stop(hold);


}

void leftCenterLong(bool allColor) {
  antler.open();
  hood.open();
  isAuto = true;
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
    wait(20, msec);
  }

  chassis.set_coordinates(-48, 16, 0);
  intakeThread = thread(autoIntake, &allColor);
  distanceReset(0);
  chassis.drive_to_point(-48, 45, 0, 10, 8, 4, 50, 2000);
  matchload.open();
  chassis.turn_to_point(-72, 48, 0, 9, 6, 50, 2000);
  distanceReset(0);
  chassis.drive_to_point(-72, 48, 0, 3, 3, 0, 0, 1200);
  distanceReset(0);
  chassis.drive_to_point(-24, 48, 0, 6, 1, 0, 0, 750);
  distanceReset(0);
  intakeThread.interrupt();
  intakeScoreTop(false);
  chassis.drive_distance(-10, -90, 6, 10, 0, 0, 1000);
  distanceReset(0);
  chassisMotors.stop();
  matchload.close();
  // wait(1000, msec);
  intakeThread = thread(autoIntake, &allColor);
  distanceReset(0, true);
  chassis.turn_to_point(-24, 24);
  distanceReset(0);

  // intakeStore(true, allColor);
  // chassis.drive_to_point(-30, -29, 0, 6, 4, 14, 0, 2000);
  chassis.drive_to_point(-24, 24, 0, 4, 4, 3, 100, 2000);
  matchload.open();
  chassisMotors.stop();
  
  // chassis.turn_to_point(0, 0, 175);
  wait(750, msec);
  chassis.turn_to_point(0, 0, 180);
  matchload.close();
  
  chassis.drive_to_point(-12, 12, 0, 6, 6, 2, 100, 300);
  // chassis.drive_to_point(0, 0, 0, 3, 2, 2, 50, 500);
  intakeThread.interrupt();
  chassis.drive_distance(-10, -45, 3, 6, 0, 0, 500);
  intakeScoreMid(60);
  hoodMotor.spin(reverse, 80, pct);
  chassis.set_coordinates(-9, 9, chassis.get_absolute_heading());
  wait(1400, msec);
  matchload.close();
  chassis.drive_distance(14);
  midDescore.open();
  chassis.drive_distance(-14, chassis.get_absolute_heading(), 4, 2);
  while(Brain.timer(sec) < 12) {
    wait(50, msec);
  }
  chassis.drive_distance(2);
  chassis.drive_to_point(-24, 32);
  chassis.turn_to_angle(75);
  antler.close();
  chassis.drive_distance(20, 90, 7, 1, 3, 0, 1000);
  chassis.turn_to_angle(120, 9, 0, 0, 5000);
  
}

void skills() {
  antler.open();
  hood.open();
  isAuto = true;
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
      wait(20, msec);
  }

  chassis.set_coordinates(-48, 8, 90);
  distanceReset(0);

  intakeStore(false);
  chassis.turn_to_point(-24, 24);
  chassis.drive_to_point(-25, 23, 0, 2.5, 6, 3, 100, 2000);
  matchload.open();
  wait(50, msec);
  chassis.turn_to_point(0, 0, 180);
  intakeMotors.spinFor(reverse, 160, deg, 500, rpm, false);
  chassis.drive_to_point(-10, 8, 0, 3, 4, 0, 0, 1000);
  printCoordinates();
  intakeScoreMid(53);
  wait(1300, msec);
  // intakeMotors.spin(fwd, 100, pct);
  ramp.close();
  intakeMotors.spinFor(reverse, 200, deg, 500, rpm, false);
  chassis.drive_to_point(-48, 48, 0, 8, 6, 5, 200, 2000);
  intakeStore(false);
  chassis.turn_to_angle(-90);
  distanceReset(0);
  chassis.drive_to_point(-24, 48, 0, 6, 2, 0, 0, 600);
  intakeScoreTop(false);
  chassis.drive_distance(-10, -90, 6, 10, 0, 0, 250);
  chassisMotors.stop();
  wait(500, msec);
  chassis.drive_to_point(-60, 48, 0, 7, 6, 12, 0, 2000);
  intakeMotors.stop();
  matchload.open();
  intakeStore(false);
  chassis.drive_to_point(-72, 48, 0, 3, 2, 0, 0, 2100);
  // chassis.drive_distance(24, -90, 3, 1, 0, 0, 3000);
  chassis.drive_distance(-12);
  flapsMotor.spin(fwd, 100, pct);
  distanceReset(0);
  chassis.turn_to_angle(-150);

  //Going to other side
  chassis.drive_to_point(24, 64, 0, 8, 2, 8, 0, 2000);
  distanceReset(0);
  matchload.close();
  chassis.drive_to_point(40, 48);
  // chassis.turn_to_angle(40); 
  // chassis.turn_to_angle(0);
  // distanceReset(0);
  // chassis.drive_to_point(45, 48, 0, 6, 6, 2, 150, 2000);
  chassis.turn_to_angle(90);
  distanceReset(0);
  chassis.drive_to_point(24, 48, 0, 6, 2, 0, 0, 600);
  intakeMotors.spinFor(reverse, 40, deg, 500, rpm, false);
  chassis.drive_distance(-10, 90, 2, 10, 0, 0, 250);
  intakeScoreTop(false);
  wait(1800, msec);
  matchload.open();
  distanceReset(0);
  intakeStore(false);
  chassis.drive_to_point(56, 48, 0, 5, 2, 8, 0, 2000);
  chassis.drive_to_point(72, 48, 0, 3, 2, 0, 0, 2100);
  intakeMotors.spinFor(reverse, 40, deg, 500, rpm, false);
  chassis.drive_to_point(24, 48, 0, 6, 1, 0, 0, 1200);
  intakeScoreTop(false);
  matchload.close();
  distanceReset(0);
  wait(2000, msec);
  chassis.drive_to_point(60, 32);
  chassis.turn_to_angle(150);
  bool allColor = false; 
  intakeStore(true, allColor);
  chassis.drive_distance(16, 175, 7, 1, 4, 0, 2000);
  chassis.drive_distance_to_wall(frontDist, 38, 175, 6.25, 1.5, 5, 0, 4000);
  // chassis.drive_distance(70, 180, 6, 1, 5, 0, 2500); //5 volts //80
  // distanceReset(4);
  // chassis.drive_to_point(chassis.get_X_position(), -30);
  chassis.turn_to_angle(-90);
  chassis.drive_distance(3);
  chassis.turn_to_angle(-90);
  distanceReset(0, true);
  chassis.drive_to_point(26, -18, 0, 5, 5, 2, 0, 2000); //28, -19
  chassis.drive_to_point(30, -30);
  chassis.turn_to_angle(0);
  distanceReset(0);
  // chassis.drive_distance(-12);
  chassis.turn_to_point(0, 0, 180);
  intakeMotors.stop();
  chassis.drive_to_point(8, -10, 0, 4, 6, 0, 0, 1500);
  chassisMotors.stop(coast);
  chassis.turn_to_angle(135);
  // chassis.drive_to_point(0, 0, 0, 2, 10, 0, 0, 500);
  matchload.open();
  intakeMotors.spinFor(reverse, 160, deg, 500, rpm, false);
  chassis.drive_distance(-16, 135, 2, 5, 0, 0, 750);
  // intakeMotors.spin(reverse, 90, pct);
  // wait(150, msec);
  //Score top mid
  intakeScoreMid(60);
  chassis.set_coordinates(10, -10, chassis.get_absolute_heading());
  wait(1250, msec); //3000
  flapsMotor.spin(fwd, 60, pct);
  hoodMotor.spin(reverse, 60, pct);
  wait(2000, msec);
  
  //Second half
  chassis.drive_to_point(46, -46, 0, 6, 6, 4, 150, 2000);
  ramp.close();
  matchload.open();
  chassis.turn_to_angle(90);
  printf("First matchloader on other side \n \n \n \n \n ");
  distanceReset(0);
  intakeStore(false);
  // chassis.drive_distance(72, 90, 3, 6, 0, 0, 2500);
  chassis.drive_to_point(72, -48, 0, 3, 2, 0, 0, 2100);
  chassis.drive_distance(-12);
  flapsMotor.spin(fwd, 100, pct);
  distanceReset(0);
  chassis.turn_to_angle(30);

  //Going to other side
  chassis.drive_to_point(-24, -64, 0, 8, 2, 8, 0, 2000);
  distanceReset(0);
  matchload.close();
  chassis.drive_to_point(-40, -48);
  // chassis.turn_to_angle(180);
  // distanceReset(0);
  // chassis.drive_to_point(-45, -48, 0, 6, 6, 2, 150, 2000);
  chassis.turn_to_angle(-90);
  distanceReset(0);
  // chassis.turn_to_angle(-140); 
  chassis.drive_to_point(-24, -48, 0, 6, 2, 0, 0, 600);
  intakeMotors.spinFor(reverse, 40, deg, 500, rpm, false);
  chassis.drive_distance(-10, -90, 6, 10, 0, 0, 250);

  intakeScoreTop(false);
  distanceReset(0);
  wait(1800, msec);
  matchload.open();
  intakeStore(false);
  chassis.turn_to_point(-72, -48);
  printf("Heading: %f", chassis.get_absolute_heading());
  chassis.drive_to_point(-56, -48, 0, 5, 2, 8, 0, 2000);
  chassis.drive_to_point(-72, -48, 0, 3, 2, 0, 0, 2100);
  intakeMotors.spinFor(reverse, 40, deg, 500, rpm, false);
  chassis.drive_to_point(-24, -48, 0, 6, 1, 0, 0, 1200);
  intakeScoreTop(false);
  matchload.close();
  distanceReset(0);
  wait(2000, msec);
  intakeStore(false);
  chassis.drive_to_point(-60, -34);
  chassis.turn_to_angle(-30);
  chassis.drive_distance(50, -5, 6.5, 1.5, 5, 0, 3500);
  // chassis.drive_distance_to_wall(frontDist, 72, 180, 6, 1, 5, 0, 4000);
  

}



void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(10, 1.25, 0.05, 12.5, 5);
  chassis.set_heading_constants(6, .3, 0, 1.5, 0);
  chassis.set_turn_constants(12, .4, .03, 3.5, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // chassis.set_drive_constants(10, 2.5, 0.05, 12.5, 5);
  // chassis.set_heading_constants(6, .3, 0, 1.5, 0);
  // chassis.set_turn_constants(12, 0.8, .03, 3.5, 15);
  // chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 150, 5000);
  chassis.set_turn_exit_conditions(1.5, 75, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

void odom_constants(){
  default_constants();
  chassis.heading_max_voltage = 6;
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 4;
  chassis.boomerang_lead = 0.3;
  chassis.drive_min_voltage = 0;
}

/**
 * The expected behavior is to return to the start position.
 */

void drive_test(){
  chassis.drive_distance(6);
  chassis.drive_distance(12);
  chassis.drive_distance(18);
  chassis.drive_distance(-36);
  chassis.drive_stop(hold);
}

/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */

void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

/**
 * Should swing in a fun S shape.
 */

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

/**
 * A little of this, a little of that; it should end roughly where it started.
 */

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

/**
 * Doesn't drive the robot, but just prints coordinates to the Brain screen 
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

/**
 * Should end in the same place it began, but the second movement
 * will be curved while the first is straight.
 */

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

/**
 * Drives in a square while making a full turn in the process. Should
 * end where it started.
 */

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_pose(0, 18, 90);
  chassis.holonomic_drive_to_pose(18, 0, 180);
  chassis.holonomic_drive_to_pose(0, 18, 270);
  chassis.holonomic_drive_to_pose(0, 0, 0);
}

//  void left4Wing(bool allColor) {
//   chassis.set_turn_exit_conditions(6, 50, 2000);
//   antler.open();
//   isAuto = true;
//   Brain.resetTimer();
//   while(chassis.Gyro.isCalibrating()) {
//     wait(20, msec);
//   }

//   chassis.set_coordinates(-48, 16, 0);
//   intakeThread = thread(autoIntake, &allColor);
//   distanceReset(0);
//   chassis.drive_to_point(-48, 48, 0, 8, 6, 4, 50, 2000);
//   chassis.turn_to_point(-72, 48);
//   matchload.open();
//   distanceReset(0);
//   chassis.drive_to_point(-60, 48, 0, 6, 2, 8, 0, 2000);
//   chassis.drive_to_point(-72, 48, 0, 3, 2, 0, 0, 650);
//   distanceReset(0);
//   chassis.drive_to_point(-24, 48, 0, 8, 1, 0, 0, 750);
//   intakeThread.interrupt();
//   intakeScoreTop(false, allColor);
//   matchload.close();
//   chassis.drive_distance(-10, -90, 3, 6, 0, 0, 750);
//   distanceReset(0);
//   wait(250, msec);

//   intakeThread.interrupt();
//   intakeMotors.stop();
//   chassis.drive_distance(16, -30, 6, 8, 6, 0, 2000);
//   antler.close();
//   chassis.turn_to_angle(-65, 9, 4, 75, 2000);
//   chassis.drive_distance(-30, -90, 5, 1, 6, 0, 3000);
//   chassis.turn_to_angle(-100, 9, 0, 0, 10000);
//   chassisMotors.stop(hold);
//  }

//  void right4Wing(bool allColor) {
//   chassis.set_turn_exit_conditions(6, 50, 2000);
//   antler.open();
//   isAuto = true;
//   Brain.resetTimer();
//   while(chassis.Gyro.isCalibrating()) {
//     wait(20, msec);
//   }

//   chassis.set_coordinates(-48, -16, 180);
//   intakeThread = thread(autoIntake, &allColor);
//   distanceReset(0);
//   chassis.drive_to_point(-48, -48, 0, 8, 6, 4, 50, 2000);
//   chassis.turn_to_point(-72, -48);
//   matchload.open();
//   distanceReset(0);
//   chassis.drive_to_point(-60, -48, 0, 6, 2, 8, 0, 2000);
//   chassis.drive_to_point(-72, -48, 0, 3, 2, 0, 0, 650);
//   distanceReset(0);
//   chassis.drive_to_point(-24, -48, 0, 8, 1, 0, 0, 750);
//   intakeThread.interrupt();
//   intakeScoreTop(false, allColor);
//   matchload.close();
//   chassis.drive_distance(-10, -90, 3, 6, 0, 0, 750);
//   distanceReset(0);
//   wait(250, msec);

//   intakeThread.interrupt();
//   intakeMotors.stop();
//   chassis.drive_distance(16, -30, 6, 8, 6, 0, 2000);
//   antler.close();
//   chassis.turn_to_angle(-65, 9, 4, 75, 2000);
//   chassis.drive_distance(-30, -90, 5, 1, 6, 0, 3000);
//   chassis.turn_to_angle(-100, 9, 0, 0, 10000);
//   chassisMotors.stop(hold);
//  }