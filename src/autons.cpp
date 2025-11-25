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

thread intakeThread;

void skills() {
  antler.open();
  bool allColor = true;
  isAuto = true;
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
      wait(20, msec);
  }

  descore.open();
  chassis.set_coordinates(-60, 36, 0);
  intakeStore(false);
  chassis.drive_distance_with_sensor(frontDist, 55, -3, 9, 6, 4, 50, 3500); //Drives across park and gets balls

  
  chassis.turn_to_angle(90);
  chassis.set_coordinates(-59, 31, chassis.get_absolute_heading());
  // chassis.set_coordinates(-72 + (backDist.objectDistance(inches) + 7), 72 - (leftDist.objectDistance(inches) + 6.5), chassis.get_absolute_heading()); //Sets coordinates using distance sensors
  distanceReset(0);
  printf("Chassis coord: %f \n  %f", chassis.get_X_position(), chassis.get_Y_position());
  intakeThread = thread(autoIntake, &allColor);
  chassis.turn_to_point(-24, 23);
  chassis.drive_distance(14, chassis.get_absolute_heading(), 8, 6, 4, 0, 2000);
  chassis.drive_to_point(-17, 23, 0, 2, 6, 2, 50, 2000);  //Gets 4 stack
  chassis.drive_to_point(-28, 23, 0, 4, 0, 2, 50, 2000);
  chassis.drive_stop(hold);
  // wait(1000, msec);
  chassis.turn_to_point(0, 0);
  descore.close();
  matchload.open();
  chassis.drive_to_point(0, 0, 0, 5, 1, 0, 0, 1000);
  chassis.turn_to_angle(135);
  chassis.drive_stop(hold);
  intakeThread.interrupt();
  intakeMotors.stop();
  intakeScoreMid(55); //Scores 7 in upper mid
  wait(2250, msec);
  intakeScoreMid(35);
  wait(2000, msec);
  
  intakeMotors.stop();
  chassis.drive_to_point(-48, 48, 0, 10, 6, 8, 0, 2000);

  descore.open(); 
  hood.close();
  intakeMotors.spin(fwd, 100, pct);
  agitator.stop();
  matchload.open();
  chassis.turn_to_angle(-90, 9, 1, 0, 2000);
  distanceReset(0);
  chassis.drive_to_point(-70, 48, 0, 7, 2, 0, 200, 800); //Getting matchload balls #1
  chassis.drive_distance(-3);
  chassis.drive_distance(3, chassis.get_absolute_heading(), 7, 2, -1, 0, 800);
  chassis.drive_distance(-3);
  chassis.drive_distance(3, chassis.get_absolute_heading(), 7, 2, -1, 0, 800);
  chassis.drive_to_point(-48, 48, 0, 8, 6, 6, 0, 2000);
  matchload.close();
  chassis.turn_to_angle(-90);
  distanceReset(0);
  chassis.turn_to_point(0, 0);
  chassis.drive_to_point(-24, 24, 0, 8, 6, 10, 0, 2000);
  chassis.turn_to_angle(90, 9, 15, 50, 2000);
  chassis.drive_to_point(0, 24, 0, 8, 6, 10, 0, 2000); //Middle of field
  distanceReset(0);
  chassis.drive_to_point(24, 24, 0, 8, 6, 6, 0, 2000);
  chassis.turn_to_point(40, 48, 0, 9, 10, 0, 2000);
  matchload.open();
  chassis.drive_to_point(40, 48, 0, 9, 6, 4, 50, 2000);
  chassis.turn_to_angle(90);
  distanceReset(0);
  chassis.drive_to_point(70, 48, 0, 7, 2, 0, 200, 800); //Getting matchload balls #2
  chassis.drive_distance(-3);
  chassis.drive_distance(3, chassis.get_absolute_heading(), 7, 2, -1, 0, 800);
  chassis.drive_distance(-3);
  chassis.drive_distance(3, chassis.get_absolute_heading(), 7, 2, -1, 0, 800);
  chassis.drive_to_point(52, 48, 0, 8, 6, 6, 0, 2000);
  matchload.close();
  chassis.turn_to_angle(-90);
  printf("About to score in long #1 \n");
  distanceReset(0);
  intakeThread.interrupt();
  intakeMotors.stop();
  intakeThread = thread(autoScore, &allColor); //Scores 15 into long #1
  chassis.drive_to_point(-10, 50, 0, 8, 6, 0, 200, 1000);
  wait(3500, msec);
  chassis.drive_distance(-10);
  intakeThread.interrupt();
  intakeMotors.stop();
  intakeStore(false);
  chassis.turn_to_angle(180);
  distanceReset(0);
  chassis.drive_to_point(40, -48, 0, 12, 6, 4, 50, 2000); //Drives across field
  chassis.turn_to_angle(90);
  matchload.open();
  distanceReset(0);
  chassis.drive_to_point(70, -48, 0, 7, 2, 0, 200, 800); //Getting matchload balls #3
  chassis.drive_distance(-3);
  chassis.drive_distance(3, chassis.get_absolute_heading(), 7, 2, -1, 0, 800);
  chassis.drive_distance(-3);
  chassis.drive_distance(3, chassis.get_absolute_heading(), 7, 2, -1, 0, 800);
  chassis.drive_to_point(48, -48, 0, 8, 6, 6, 0, 2000);
  matchload.close();
  chassis.turn_to_angle(0);
  distanceReset(0);
  chassis.turn_to_point(0, 0);
  chassis.drive_to_point(24, -24, 0, 8, 6, 10, 0, 2000);
  chassis.turn_to_angle(-90, 9, 15, 50, 2000);
  chassis.drive_to_point(0, -24, 0, 8, 6, 10, 0, 2000); //Middle of field #2
  distanceReset(0);
  chassis.drive_to_point(-24, -24, 0, 8, 6, 6, 0, 2000);
  chassis.turn_to_point(-40, -48, 0, 9, 10, 0, 2000);
  chassis.drive_to_point(-40, -48, 0, 8, 6, 4, 50, 2000);
  matchload.open();
  chassis.turn_to_angle(-90);
  distanceReset(0);
  chassis.drive_to_point(-70, -48, 0, 7, 2, 0, 200, 800); //Getting matchload balls #4
  chassis.drive_distance(-3);
  chassis.drive_distance(3, chassis.get_absolute_heading(), 7, 2, -1, 0, 800);
  chassis.drive_distance(-3);
  chassis.drive_distance(3, chassis.get_absolute_heading(), 7, 2, -1, 0, 800);
  chassis.drive_to_point(-52, -48, 0, 8, 6, 6, 0, 2000);
  matchload.close();
  chassis.turn_to_angle(90);
  printf("About to score in long #2 \n");
  distanceReset(0);
  intakeThread.interrupt();
  intakeMotors.stop();
  intakeThread = thread(autoScore, &allColor); //Scores 15 into long for last time

  chassis.drive_to_point(-10, -50, 0, 8, 6, 0, 200, 1000);
  wait(3000, msec);
  chassis.drive_distance(-24);
  // chassis.turn_to_angle(90);
  // distanceReset(0);
  chassis.turn_to_point(-65, -30);
  chassis.drive_to_point(-65, -30, 4, 8, 6, 8, 50, 2000);
  // chassis.turn_to_angle(-30);
  chassis.drive_distance(45, -10, 12, 6, 3, 50, 2500); //Park
  // chassis.drive_distance_with_sensor(frontDist, 35, -10, 12, 6, 3, 50, 3000);



  
  
}

void rightCenter(bool allColor) {

}

void rightCenterLong(bool allColor) {
  descore.open();
  antler.open();
  isAuto = true;
  odom_constants();
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
      wait(20, msec);
  }

  intakeThread = thread(autoIntake, &allColor);
  
  chassis.set_coordinates(-48, -16, 90);
  distanceReset(0);
  // chassis.turn_to_point(-21, -24);
  chassis.drive_to_point(-17, -24, 0, 5, 6, 2, 50, 2000);
  chassis.drive_to_point(-23, -24, 0, 6, 0, 2, 50, 2000);
  chassis.turn_to_point(0, 0);
  chassis.drive_to_point(7, 7, 0, 6, 1, 0, 0, 1200);
  chassis.turn_to_angle(45);
  intakeThread.interrupt();
  intakeMotors.stop();
  outtake(false);
  chassis.drive_distance(-3, chassis.get_absolute_heading(), 6, 0, 1, 100, 2000); //Back up for scoring low
  chassis.drive_stop(hold);
  wait(1400, msec);
  intakeMotors.stop();
  intakeThread = thread(autoIntake, &allColor);
  chassis.drive_distance(-10, chassis.get_absolute_heading(), 12, 0, 6, 0, 2000);
  chassis.turn_to_angle(180, 9, 3, 0, 2000);
  descore.open();
  distanceReset(0);
  chassis.turn_to_point(-48, -40);
  chassis.drive_to_point(-48, -40, 0, 8, 4, 3, 50, 2000);
  chassis.turn_to_angle(-90);
  distanceReset(0);
  matchload.open();
  chassis.drive_to_point(-70, -48, 0, 5.5, 2, 0, 200, 1600); //Getting matchload balls
  chassis.drive_to_point(-48, -48, 0, 8, 6, 6, 0, 2000);
  matchload.close();
  chassis.turn_to_angle(90, 9, 1.5, 0, 1900);
  distanceReset(0);
  intakeThread.interrupt(); 
  intakeMotors.stop();
  intakeScoreTop(false); //Run motors early for faster scoring
  // chassis.drive_to_point(-32, -48, 0, 8, 6, 6, 0, 2000);
  chassis.drive_to_point(-10, -48, 0, 4, 6, 0, 150, 2000); //Scoring in long goal
}

void leftCenterLong(bool allColor) {
  descore.open();
  antler.open();
  isAuto = true;
  odom_constants();
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
      wait(20, msec);
  }

  intakeThread = thread(autoIntake, &allColor);
  
  chassis.set_coordinates(-48, 16, 90);
  distanceReset(0);
  chassis.drive_to_point(-17, 26, 0, 4, 6, 2, 50, 2000);
  chassis.drive_to_point(-21, 24, 0, 6, 0, 2, 50, 2000);
  chassis.turn_to_angle(90);
  distanceReset(0);
  chassis.turn_to_point(0, 0);
  intakeThread.interrupt();
  intakeMotors.stop();
  descore.close();
  intakeScoreMid(65);
  chassis.drive_to_point(-10, 10, 0, 4, 3, 3, 0, 850);
  chassis.drive_stop(hold);
  wait(1400, msec);
  intakeMotors.stop();
  intakeThread = thread(autoIntake, &allColor);
  chassis.drive_distance(-10, chassis.get_absolute_heading(), 12, 0, 6, 0, 2000);
  chassis.turn_to_angle(0, 9, 1, 0, 2000);
  descore.open();
  distanceReset(0);
  chassis.turn_to_point(-48, 46);
  chassis.drive_to_point(-48, 46, 0, 6, 4, 3, 50, 2000);
  chassis.turn_to_angle(-90);
  distanceReset(0);
  matchload.open();
  chassis.drive_to_point(-70, 48, 0, 5.25, 6, 0, 200, 2200); //Getting matchload balls
  chassis.drive_to_point(-48, 48, 0, 8, 6, 6, 0, 2000);
  matchload.close();
  chassis.turn_to_angle(90, 9, 1.5, 0, 1900);
  distanceReset(0);
  intakeThread.interrupt(); 
  intakeMotors.stop();
  intakeScoreTop(false); 
  // printf("Desired heading: %f \n", reduce_negative_180_to_180(to_deg(atan2(48 - chassis.get_Y_position(), -10 - chassis.get_X_position()))) - chassis.get_absolute_heading());
  // printf("Actual heading: %f \n", chassis.get_absolute_heading());
  chassis.drive_to_point(-10, 48, 0, 8, 4, 6, 0, 2000);

}

void leftLong(bool allColor) {

  descore.open();
  antler.open();
  isAuto = true;
  odom_constants();
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
      wait(20, msec);
  }

  intakeThread = thread(autoIntake, &allColor);
  
  chassis.set_coordinates(-48, 16, 90);
  distanceReset(0);
  // chassis.turn_to_point(-21, -24);
  chassis.drive_to_point(-17, 24, 0, 5, 6, 2, 50, 2000);
  chassis.drive_to_point(-23, 24, 0, 6, 0, 2, 50, 2000);
  chassis.turn_to_angle(90);
  distanceReset(0);
  matchload.open();
  chassis.turn_to_point(-48, 48);
  chassis.drive_to_point(-45, 48, 0, 8, 6, 5, 150, 2000);
  chassis.turn_to_angle(-90);
  distanceReset(0);
  matchload.open();
  chassis.drive_to_point(-70, 48, 0, 5.25, 6, 0, 200, 2200); //Getting matchload balls
  chassis.drive_to_point(-48, 48, 0, 8, 6, 6, 0, 2000);
  matchload.close();
  chassis.turn_to_angle(90, 9, 1.5, 0, 1900);
  distanceReset(0);
  intakeThread.interrupt(); 
  intakeMotors.stop();
  intakeScoreTop(false); //Run motors early for faster scoring
  chassis.drive_to_point(-32, 48, 0, 8, 6, 6, 0, 2000);
  chassis.drive_to_point(-24, 48, 0, 4, 6, 0, 150, 500); //Scoring in long goal
  wait(2000, msec);
  chassis.drive_distance(-5);
  hood.close();
  chassis.drive_distance(20, 0, 6, 0, 0, 0, 5000);

}

void rightLong(bool allColor) {
  descore.open();
  antler.open();
  isAuto = true;
  odom_constants();
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
      wait(20, msec);
  }

  intakeThread = thread(autoIntake, &allColor);
  
  chassis.set_coordinates(-48, -16, 90);
  distanceReset(0);
  // chassis.turn_to_point(-21, -24);
  chassis.drive_to_point(-17, -24, 0, 5, 6, 2, 50, 2000);
  chassis.drive_to_point(-23, -24, 0, 6, 0, 2, 50, 2000);
  chassis.turn_to_angle(90);
  distanceReset(0);
  matchload.open();
  chassis.turn_to_point(-48, -48);
  chassis.drive_to_point(-45, -48, 0, 8, 6, 5, 150, 2000);
  chassis.turn_to_angle(-90);
  distanceReset(0);
  matchload.open();
  chassis.drive_to_point(-70, -48, 0, 5.25, 6, 0, 200, 2200); //Getting matchload balls
  chassis.drive_to_point(-48, -48, 0, 8, 6, 6, 0, 2000);
  matchload.close();
  chassis.turn_to_angle(90, 9, 1.5, 0, 1900);
  distanceReset(0);
  intakeThread.interrupt(); 
  intakeMotors.stop();
  intakeScoreTop(false); //Run motors early for faster scoring
  chassis.drive_to_point(-32, -48, 0, 8, 6, 6, 0, 2000);
  chassis.drive_to_point(-24, -48, 0, 4, 6, 0, 150, 500); //Scoring in long goal
  wait(2000, msec);
  chassis.drive_distance(-5);
  hood.close();
  chassis.drive_distance(20, 0, 6, 0, 0, 0, 5000);

}

void temp(bool allColor) {
  intakeThread = thread(autoIntake, &allColor);
}

void sawpRight(bool allColor) {
  descore.open();
  antler.open();
  isAuto = true;
  odom_constants();
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
      wait(20, msec);
  }

  intakeThread = thread(autoIntake, &allColor);
  
  chassis.set_coordinates(-49, -17, 180);
  chassis.drive_to_point(-48, -48, 0, 8, 6, 8, 0, 2000);
  chassis.turn_to_angle(-90, 9, 1, 0, 2000);
  distanceReset(0);
  matchload.open();
  chassis.drive_to_point(-70, -48, 0, 4.5, 2, 0, 200, 1450); //Getting matchload balls
  chassis.drive_to_point(-51, -48, 0, 8, 8, 3, 0, 2000);
  matchload.close();
  chassis.turn_to_angle(90, 9, 3, 50, 1900);
  distanceReset(0);
  intakeThread.interrupt(); 
  intakeMotors.stop();
  intakeMotors.spin(fwd, 65, pct);
  chassis.drive_to_point(-30, -48, 0, 8, 11, 4, 0, 1000);
  intakeScoreTop(false); //Run motors early for faster scoring
  // chassis.drive_to_point(-24, 48, 0, 4, 4, 0, 150, 500); //Scoring in long goal
  distanceReset(0);
  wait(900, msec);
  intakeThread.interrupt();
  intakeMotors.stop();
  // intakeThread = thread(autoIntake, &allColor);
  intakeStore(false);

  chassis.drive_to_point(-48, -48, 0, 10, 6, 5, 0, 2000); //drive back and reset
  intakeThread.interrupt();
  intakeMotors.stop();
  intakeThread = thread(autoIntake, &allColor);
  chassis.turn_to_angle(90, 9, 1.5, 0, 1900);
  distanceReset(0);
  chassis.turn_to_point(0, 0, 0, 9, 2, 50, 2000); //Go towards middle

  chassis.drive_to_point(-23, -24, 0, 6, 0, 2, 50, 2000);
  // chassis.turn_to_point(0, 0);
  chassis.drive_to_point(7, 7, 0, 6, 1, 0, 0, 1000);
  intakeThread.interrupt();
  intakeMotors.stop();
  outtake(false);
  chassis.turn_to_angle(45);
  chassis.drive_distance(-3, chassis.get_absolute_heading(), 6, 0, 1, 100, 2000); //Back up for scoring low
  chassis.drive_stop(hold);
  wait(500, msec);
  intakeMotors.stop();
  intakeThread = thread(autoIntake, &allColor);
  chassis.drive_distance(-10, chassis.get_absolute_heading(), 12, 0, 6, 0, 2000);
  chassis.turn_to_angle(0, 9, 1, 0, 2000);
  descore.open();
  distanceReset(0);

  intakeMotors.stop();
  intakeThread = thread(autoIntake, &allColor);
  chassis.drive_to_point(-24, 24, 0, 10, 6, 8, 0, 2000); //Get other 3 stack
  chassis.drive_to_point(-40, 48, 0, 10, 6, 8, 0, 2000);
  chassis.turn_to_angle(90, 9, 1.5, 0, 2000);
  distanceReset(0);
  printf("in time");
  intakeThread.interrupt();
  ejectEndTime = 0;
  hood.open();
  intakeMotors.stop();
  intakeScoreTop(false);
  chassis.drive_to_point(-27, 48, 0, 8, 8, 0, 150, 500);

  
}

//Needs to score 10 in 3 goals, 2 blocks/goal, 3 blocks out of matchloader
void sawpLeft(bool allColor) {
  descore.open();
  antler.open();
  isAuto = true;
  odom_constants();
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
      wait(20, msec);
  }

  intakeThread = thread(autoIntake, &allColor);
  
  chassis.set_coordinates(-49, 17, 0);
  chassis.drive_to_point(-48, 48, 0, 8, 6, 8, 0, 2000);
  chassis.turn_to_angle(-90, 9, 1, 0, 2000);
  distanceReset(0);
  matchload.open();
  // descore.close();
  chassis.drive_to_point(-70, 48, 0, 4.5, 2, 0, 200, 1450); //Getting matchload balls
  // chassis.drive_to_point(-70, -48, 0, 1, 6, 0, 200, 700); 
  chassis.drive_to_point(-51, 48, 0, 8, 8, 3, 0, 2000);
  matchload.close();
  // descore.open();
  chassis.turn_to_angle(90, 9, 3, 50, 1900);
  distanceReset(0);
  intakeThread.interrupt(); 
  intakeMotors.stop();
  intakeMotors.spin(fwd, 65, pct);
  chassis.drive_to_point(-30, 48, 0, 8, 11, 4, 0, 2000);
  intakeScoreTop(false); //Run motors early for faster scoring
  // chassis.drive_to_point(-24, 48, 0, 4, 4, 0, 150, 500); //Scoring in long goal
  distanceReset(0);
  wait(900, msec);
  intakeThread.interrupt();
  intakeMotors.stop();
  // intakeThread = thread(autoIntake, &allColor);
  intakeStore(false);

  chassis.drive_to_point(-48, 48, 0, 10, 6, 5, 0, 2000); //drive back and reset
  chassis.turn_to_angle(90, 9, 1.5, 0, 1900);
  distanceReset(0);
  chassis.turn_to_point(0, 0, 0, 9, 2, 50, 2000); //Go towards middle
  chassis.drive_to_point(-29, 29, 0, 8, 6, 5, 0, 2000);
  descore.close();
  intakeThread.interrupt();
  intakeMotors.stop();
  // intakeScoreMid(40);
  intakeFront.spin(fwd, 40, pct);
  intakeBack.spin(fwd, 40, pct);
  intakeTop.spin(reverse, 40, pct);
  chassis.drive_to_point(-10, 10, 0, 5, 3, 3, 0, 1250);
  // intakeScoreMid(80);
  intakeFront.spin(fwd, 60, pct);
  intakeBack.spin(fwd, 60, pct);
  intakeTop.spin(reverse, 60, pct);
  chassis.drive_stop(hold);
  wait(1000, msec);
  intakeMotors.stop();
  chassis.drive_distance(-10, chassis.get_absolute_heading(), 12, 0, 6, 0, 2000);
  chassis.turn_to_angle(180, 9, 1, 0, 2000);
  descore.open();
  distanceReset(0);

  intakeMotors.stop();
  intakeThread = thread(autoIntake, &allColor);
  chassis.drive_to_point(-24, -24, 0, 8, 6, 8, 0, 2000); //Get other 3 stack
  chassis.drive_to_point(-40, -48, 0, 8, 6, 8, 0, 2000);
  chassis.turn_to_angle(90, 9, 1.5, 0, 2000);
  distanceReset(0);
  chassis.drive_to_point(-27, -48, 0, 8, 8, 0, 150, 500);
  intakeThread.interrupt();
  intakeMotors.stop();
  intakeScoreTop(false);

  
}

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(10, 1.25, 0.05, 12.5, 5);
  chassis.set_heading_constants(6, .3, 0, 1.5, 0);
  chassis.set_turn_constants(12, .4, .03, 3.5, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

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