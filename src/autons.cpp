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
  isAuto = true;
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
      wait(20, msec);
  }

  chassis.set_coordinates(-48, 24, 90);
  chassis.turn_to_point(-24, -24);
  chassis.drive_to_point(-24, -24, 0, 6, 6, 3, 100, 2000);
  printf( " %f\n", chassis.get_X_position());
  printf( " %f\n", chassis.get_Y_position());
}

void leftLong(bool allColor) {

}

void rightLong(bool allColor) {
  isAuto = true;
  odom_constants();
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
      wait(20, msec);
  }

  intakeThread = thread(autoIntake, &allColor);
  chassis.set_coordinates(-48, -16, 90);
  chassis.drive_to_point(-24, -24, 6, 10, 6, 6, 0, 2000);
  matchload.open();
  chassis.drive_to_pose(-18, -42, 105);
  chassis.drive_to_point(-36, -33, 0, 8, 6, 8, 100, 2000);
  matchload.close();
  chassis.turn_to_point(-48, -48);
  chassis.drive_to_point(-48, -48, 0, 8, 6, 5, 150, 2000);
  chassis.turn_to_angle(-90);
  distanceReset(0);
  matchload.open();
  chassis.drive_to_point(-70, -48, 0, 4, 6, 0, 200, 2000);
  chassis.drive_to_point(-48, -48, 0, 8, 6, 6, 50, 2000);
  matchload.close();


}

void temp(bool allColor) {
  intakeThread = thread(autoIntake, &allColor);
}

void rightCenter(bool allColor) {
  isAuto = true;
  odom_constants();
  Brain.resetTimer();
  while(chassis.Gyro.isCalibrating()) {
      wait(20, msec);
  }

  intakeThread = thread(autoIntake, &allColor);
  agitator.spin(fwd, 100, pct);
  chassis.set_coordinates(-48, -16, 180);
  chassis.drive_to_point(-48, -48, 0, 10, 6, 2, 100, 2000);
  chassis.turn_to_angle(-90);
  distanceReset(0);
  matchload.open();
  chassis.drive_to_point(-70, -48, 0, 4, 6, 0, 200, 2000); //Getting matchload balls
  chassis.drive_to_point(-48, -48, 0, 8, 6, 6, 50, 2000);
  matchload.close();
  chassis.turn_to_angle(90);
  distanceReset(0);
  chassis.drive_to_point(-24, -48, 0, 4, 6, 0, 200, 1000);
  intakeThread.interrupt();
  intakeMotors.stop();
  intakeThread = thread(autoScore, &allColor); //Scores 4 into long
  wait(500, msec);
  chassis.drive_to_point(-48, -48, 0, 8, 6, 6, 50, 2000);
  distanceReset(0);
  intakeThread.interrupt();
  intakeThread = thread(autoIntake, &allColor);
  chassis.drive_to_point(-21, -21, 0, 8, 6, 3, 100, 2000);
  chassis.drive_to_point(-5, -5, 0, 4, 2, 0, 0, 1000);
  chassis.drive_to_point(-10, -10, 0, 4, 2, 3, 100, 2000);
  intakeThread.interrupt();
  outtake(); //Scores 3 balls into bottom mid
  wait(500, msec);
  chassis.drive_to_point(-21, -21, 4, 8, 6, 6, 20, 2000);
  chassis.drive_to_point(-21, 21, 0, 8, 6, 3, 100, 2000);
  chassis.turn_to_angle(0);
  distanceReset(0);
  chassis.turn_to_point(0, 0);
  chassis.drive_to_point(-9, 9, 0, 4, 2, 3, 100, 2000);
  intakeScoreMid(75); //Scores 3 balls into top mid
}

//Entirely theory coded. Needs to score 10, in 3 goals, 2 blocks/goal, 3 blocks out of matchloader
void sawp(bool allColor) {
  
}

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(10, 1.25, 0.05, 12.5, 5);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3.5, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 150, 5000);
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