#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen.
brain  Brain;
controller Controller;

motor leftBack = motor(PORT7, ratio6_1, true);
motor leftMid = motor(PORT9, ratio18_1, false);
motor leftFront = motor(PORT8, ratio6_1, true);
motor rightBack = motor(PORT10, ratio6_1, false);//needs rewiring
motor rightMid = motor(PORT5, ratio18_1, true);
motor rightFront = motor(PORT6, ratio6_1, false);

motor_group chassisMotors = motor_group(leftBack, leftMid, leftFront, rightBack, rightMid, rightFront);

motor intakeFront = motor(PORT12, false);
motor intakeBack = motor(PORT2, false);//Needs rewiring
motor intakeTop = motor(PORT11, true);
motor agitator = motor(PORT20, true); //needs rewiring

motor_group intakeMotors = motor_group(intakeFront, intakeBack, intakeTop, agitator);

pneumatics matchload = pneumatics(Brain.ThreeWirePort.G);
pneumatics hood = pneumatics(Brain.ThreeWirePort.A);

bool matchloadActive = false;
bool topScoring = true;

distance hookPos = distance(PORT21);

void vexcodeInit( void ) {
  // nothing to initialize
}