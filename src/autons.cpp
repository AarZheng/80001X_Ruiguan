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

 void sawpRight(bool allColor) {
   antler.open();
  isAuto = true;
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
      wait(20, msec);
  }

  chassis.set_coordinates(-60, 36, 0);
  chassis.drive_to_point(45, -45);
  chassis.turn_to_angle(135);
  chassis.drive_to_pose(10, -36, 40);
  intakeMotors.spin(fwd, 100, pct);


 }

thread intakeThread;

void skills() {
  antler.open();
  bool allColor = true;
  isAuto = true;
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
      wait(20, msec);
  }

  chassis.set_coordinates(-48, 8, 90);
  distanceReset(0);

  intakeStore(false);
  chassis.drive_to_point(-24, 24, 0, 6, 6, 4, 200, 2000);
  chassis.turn_to_point(0, 0, 180);
  chassis.drive_to_point(-10, 10, 0, 5, 5, 0, 0, 700);
  intakeMotors.spin(reverse, 80, pct);
  wait(150, msec);
  intakeScoreMid(90);
  wait(750, msec);
  ramp.close();
  intakeMotors.stop();
  chassis.drive_to_point(-48, 48, 0, 8, 6, 5, 200, 2000);
  chassis.turn_to_angle(-90);
  distanceReset(0);
  matchload.open();
  intakeStore(false);
  chassis.drive_to_point(-72, 48, 0, 3, 1, 0, 0, 2000);
  // chassis.drive_distance(24, -90, 3, 1, 0, 0, 3000);
  chassis.drive_distance(-12);
  matchload.close();
  intakeMotors.stop();
  distanceReset(0);
  chassis.turn_to_angle(-150);

  //Going to other side
  chassis.drive_to_point(0, 60, 0, 8, 2, 8, 0, 2000);
  distanceReset(0);
  chassis.drive_to_point(40, 60);
  chassis.turn_to_angle(50); 
  chassis.drive_to_point(24, 48, 0, 6, 2, 0, 0, 1000);
  chassis.drive_distance(-10, 90, 2, 10, 0, 0, 500);
  intakeScoreTop(false);
  wait(2000, msec);
  matchload.open();
  intakeStore(false);
  // chassis.drive_distance(48, 92, 4, 1, 0, 0, 3500);
  chassis.drive_to_point(72, 48, 0, 4, 1, 0, 0, 2500);
  // chassis.drive_distance(-48, 92, 6, 2, 0, 0, 1750);
  chassis.drive_to_point(24, 48, 0, 6, 1, 0, 0, 1750);
  intakeScoreTop(false);
  matchload.close();
  distanceReset(0);
  wait(2000, msec);
  chassis.drive_to_point(60, 32);
  chassis.turn_to_angle(155);
  intakeStore(false);
  chassis.drive_distance(84, 180, 7, 1, 5, 0, 3250);
  chassis.turn_to_angle(-90);
  distanceReset(0);
  intakeMotors.stop();
  chassis.drive_to_point(24, -24);
  chassis.turn_to_point(0, 0, 180);
  chassis.drive_to_point(0, 0, 0, 4, 4, 0, 0, 1500);
  matchload.open();
  intakeMotors.spin(reverse, 80, pct);
  wait(150, msec);
  //Score top mid
  intakeScoreMid(80);
  wait(3000, msec);
  ramp.close();
  matchload.close();
  wait(500, msec);
  
  
  //Second half
  chassis.drive_to_point(48, -48, 0, 8, 6, 5, 200, 2000);
  chassis.turn_to_angle(90);
  distanceReset(0);
  matchload.open();
  intakeStore(false);
  chassis.drive_distance(24, 90, 3, 1, 0, 0, 3000);
  chassis.drive_distance(-12);
  matchload.close();
  intakeMotors.stop();
  chassis.turn_to_angle(-90);
  distanceReset(0);
  chassis.turn_to_angle(-150);
  chassis.drive_distance(24, -105, 6, 2, 6, 0, 2000);
  chassis.drive_to_point(-48, -60);
  chassis.turn_to_angle(-130); 
  chassis.drive_distance(-48, -90, 6, 1, 0, 0, 1750);
  intakeScoreTop(false);
  wait(2000, msec);
  matchload.open();
  intakeStore(false);
  chassis.drive_distance(-10, -90, 2, 10, 0, 0, 500);
  chassis.drive_distance(48, -92, 4, 1, 0, 0, 3500);
  chassis.drive_distance(-48, -92, 6, 2, 0, 0, 1750);
  intakeScoreTop(false);
  matchload.close();
  wait(2000, msec);
  chassis.drive_to_point(-60, -36);
  chassis.turn_to_angle(-20);
  chassis.drive_distance(30, 0, 6, 1, 5, 0, 3500);
  

}

//   descore.open();
//   chassis.set_coordinates(-60, 36, 0);
//   intakeStore(false);
//   chassis.set_coordinates(-59, 31, chassis.get_absolute_heading());
//   distanceReset(0);
//   printf("Chassis coord: %f \n  %f", chassis.get_X_position(), chassis.get_Y_position());



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