#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen.
brain  Brain;
controller Controller;

motor leftBack = motor(PORT12, ratio6_1, true);
motor leftMid = motor(PORT1, ratio18_1, true);
motor leftFront = motor(PORT3, ratio6_1, true);
motor rightBack = motor(PORT20, ratio6_1, false); 
motor rightMid = motor(PORT10, ratio18_1, false);
motor rightFront = motor(PORT9, ratio6_1, false);

motor_group chassisMotors = motor_group(leftBack, leftMid, leftFront, rightBack, rightMid, rightFront);

motor flapsMotor = motor(PORT2, true);
motor hoodMotor = motor(PORT19, true);

motor_group intakeMotors = motor_group(flapsMotor, hoodMotor);

pneumatics matchload = pneumatics(Brain.ThreeWirePort.D);
pneumatics ramp = pneumatics(Brain.ThreeWirePort.A);
pneumatics antler = pneumatics(Brain.ThreeWirePort.B);
pneumatics midDescore = pneumatics(Brain.ThreeWirePort.C);

bool matchloadActive = false;
bool topScoring = true;
bool antlerActive = false;
bool midDescoreActive = false;

optical colorSorter = optical(PORT14);
distance rightDist = distance(PORT18); //6
distance backDist = distance(PORT17); //4
distance frontDist = distance(PORT8); //2
distance leftDist = distance(PORT13);

void vexcodeInit( void ) {
  colorSorter.setLightPower(100);
  colorSorter.integrationTime(15);
  // colorSorter.objectDetectThreshold(10);
}