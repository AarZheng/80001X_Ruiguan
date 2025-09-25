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

void leftLong(bool allColor) {
  isAuto = true;
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
      wait(20, msec);
  }

  hood.open();
  wait(50, msec);
  hood.close();

  intakeThread = thread(autoIntake, &allColor);
  // chassis.set_coordinates(-45.5, 8, 90);
  chassis.set_coordinates(-48, 18, 90);
  chassis.drive_max_voltage = 6;
  chassis.turn_to_point(-18, 20);
  chassis.drive_to_point(-18, 20); 
  // chassis.drive_distance(-3);
  chassis.drive_stop(hold);
  chassis.drive_max_voltage = 6;
  chassis.turn_to_angle(75);
  chassis.drive_max_voltage = 8;
  chassis.turn_to_point(-43, 45);
  chassis.drive_to_point(-43, 45);
  chassis.drive_stop(hold);
  chassis.turn_to_angle(-90);
  matchload.open();
  wait(500, msec);
  // chassis.drive_to_point(-50, 48);
  chassis.drive_to_point(-70, 48, 0, 6, 2, chassis.drive_settle_error, chassis.drive_settle_time, 1750);
  chassis.drive_to_point(-48, 52);
  Controller.Screen.clearScreen();
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print(chassis.get_X_position());
  Controller.Screen.setCursor(2, 1);
  Controller.Screen.print(chassis.get_Y_position());
  chassis.drive_stop(hold);
  matchload.close();
  chassis.turn_to_point(-34, 52);
  chassis.drive_to_point(-34, 52);
  chassis.drive_stop(hold);
  chassis.turn_to_angle(90);
  chassis.drive_to_point(0, 48, 0, 2, 2, chassis.drive_settle_error, chassis.drive_settle_time, 300);
  intakeThread.interrupt();
  intakeScoreTop();

}

void rightLong(bool allColor) {
  isAuto = true;
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
      wait(20, msec);
  }

  hood.open();
  wait(50, msec);
  hood.close();

  intakeThread = thread(autoIntake, &allColor);
  // chassis.set_coordinates(45.5, 8, -90);
  chassis.set_coordinates(48, 18, -90);
  chassis.drive_max_voltage = 8;
  chassis.turn_to_point(20, 22);
  chassis.drive_to_point(20, 22);
  // matchload.open();
  chassis.drive_distance(-3); 
  chassis.drive_max_voltage = 8;
  chassis.turn_to_angle(-75);
  // chassis.drive_max_voltage = 10;
  chassis.turn_to_point(43, 48);
  // matchload.close();
  chassis.drive_to_point(43, 48);
  chassis.turn_to_angle(90);
  matchload.open();
  wait(500, msec);
  // chassis.drive_to_point(50, 48);
  // Controller.Screen.clearScreen();
  // Controller.Screen.print(chassis.get_Y_position());
  chassis.drive_to_point(70, 48, 0, 5, 0, chassis.drive_settle_error, chassis.drive_settle_time, 1300);
  chassis.drive_to_point(48, 48);
  // chassis.drive_distance(-20);
  chassis.turn_to_point(34, 50);
  matchload.close();
  agitator.spin(reverse, 100, pct);
  chassis.drive_to_point(34, 51);
  chassis.turn_to_angle(-90);
  intakeThread.interrupt();
  intakeScoreTop();
  chassis.drive_to_point(0, 51, 0, 2, 0, chassis.drive_settle_error, chassis.drive_settle_time, 300);
  // wait(2000, msec);
  // chassis.drive_distance(-8);
  // descore.open();
  // chassis.drive_max_voltage = 12;
  // chassis.drive_distance(100);
}

// void rightLong(bool allColor) {
//   isAuto = true;
//   Brain.resetTimer();
//   while(chassis.Gyro.isCalibrating()) {
//       wait(20, msec);
//   }

//   hood.open();
//   wait(50, msec);
//   hood.close();

//   intakeThread = thread(autoIntake, &allColor);
//   // chassis.set_coordinates(45.5, 8, -90);
//   chassis.set_coordinates(48, 18, -90);
//   chassis.drive_max_voltage = 8;
//   chassis.turn_to_point(43, 48);
//   chassis.drive_distance(31);
//   // chassis.drive_to_point(43, 46);
//   chassis.turn_to_angle(90);
//   // chassis.drive_max_voltage = 8;
//   // chassis.turn_to_point(30, 27);
//   // chassis.drive_to_point(30, 27);
//   // chassis.drive_distance(-3); 
//   // chassis.turn_to_angle(-75);
//   // chassis.drive_max_voltage = 10;
//   // chassis.turn_to_point(43, 48);
//   // chassis.drive_to_point(43, 48);
//   Controller.Screen.clearScreen();
//   Controller.Screen.setCursor(1, 1);
//   Controller.Screen.print(chassis.get_Y_position());
//   Controller.Screen.setCursor(2, 1);
//   Controller.Screen.print(chassis.get_X_position());
//   chassis.odom.Y_position = 48;
//   chassis.turn_to_angle(90);
//   matchload.open();
//   wait(500, msec);
//   chassis.drive_to_point(50, 48);
//   Controller.Screen.clearScreen();
//   Controller.Screen.print(chassis.get_Y_position());
//   chassis.drive_to_point(70, 48, 0, 5, 2, chassis.drive_settle_error, chassis.drive_settle_time, 750);
//   // chassis.drive_to_point(48, 48);
//   chassis.drive_distance(-20);
//   matchload.close();
//   // chassis.turn_to_point(34, 46);
//   // chassis.drive_to_point(34, 46);
//   chassis.turn_to_angle(-90);
//   // chassis.drive_to_point(0, 46, 0, 2, 0, chassis.drive_settle_error, chassis.drive_settle_time, 300);
//   chassis.drive_distance(50, -90, 4, 2, chassis.drive_settle_error, chassis.drive_settle_time, 2000);
//   intakeThread.interrupt();
//   intakeScoreTop();
// }

void temp(bool allColor) {
  intakeThread = thread(autoIntake, &allColor);
}

void leftCenter(bool allColor) {

}

void rightCenter(bool allColor) {
  isAuto = true;
  odom_constants();
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
      wait(20, msec);
  }

  hood.open();
  wait(50, msec);
  hood.close();
  
  chassis.set_coordinates(0, 0, 0);
  // chassis.drive_to_point(0, 48);
  chassis.turn_to_point(-24, 24);
  chassis.drive_to_point(-24, 24);
  chassis.drive_stop(hold);
  Controller.Screen.clearScreen();
  Controller.Screen.print(chassis.get_X_position());
  // Controller.Screen.setCursor(2, 1);
  // Controller.Screen.print(chassis.get_Y_position());
}

void sawp(bool allColor) {
  isAuto = true;
  odom_constants();
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
      wait(20, msec);
  }

  hood.open();
  wait(50, msec);
  hood.close();


  chassis.set_coordinates(-48, -18, 90);
  chassis.turn_to_point(-42, -48);
  chassis.drive_to_point(-42, -48);
  chassis.turn_to_point(0, -46);
  Controller.Screen.clearScreen();
  Controller.Screen.print(chassis.get_X_position());
  Controller.Screen.setCursor(2, 1);
  Controller.Screen.print(chassis.get_Y_position());
  wait(500, msec);
  // chassis.drive_to_point(-32, -48);
  chassis.drive_distance(40, 90, 6, 2, chassis.drive_settle_error, chassis.drive_settle_time, 1000);
  // chassis.drive_to_point(0, -46, 0, 2, 2, chassis.drive_settle_error, chassis.drive_settle_time, 1000);
  intakeScoreTop();
  wait(200, msec);
  chassis.drive_distance(-20);
  chassis.turn_to_point(-100, -48);
  intakeThread = thread(autoIntake, &allColor);
  matchload.open();
  chassis.drive_to_point(-50, -48);
  chassis.drive_to_point(-70, -48, 0, 6, 2, chassis.drive_settle_error, chassis.drive_settle_time, 850);
  chassis.drive_to_point(-48, -48);
  matchload.close();
  chassis.drive_to_point(-22, -22);
  chassis.drive_to_point(-11, -11);
  chassis.turn_to_point(11, 11);
  intakeThread.interrupt();
  intakeScoreMid();
  wait(1, sec);
  chassis.drive_to_point(-22, -22);
  intakeThread = thread(autoIntake, &allColor);
  chassis.turn_to_point(-22, 22);
  chassis.drive_to_point(-22, 22);
  

}

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(10, 1.25, 0.05, 12.5, 5);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3.5, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1.5, 150, 3000);
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
  chassis.drive_settle_error = 6;
  chassis.boomerang_lead = 0.2;
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