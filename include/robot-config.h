using namespace vex;

extern brain Brain;

extern controller Controller;

extern motor leftBack;
extern motor leftMid;
extern motor leftFront;
extern motor rightBack;
extern motor rightMid;
extern motor rightFront;

extern motor_group chassisMotors;

extern motor flapsMotor;
extern motor hoodMotor;

extern motor_group intakeMotors;

extern pneumatics matchload;
extern pneumatics ramp;
extern pneumatics antler;

extern optical colorSorter;
extern distance frontDist;
extern distance rightDist;
extern distance leftDist;
extern distance backDist;


extern bool matchloadActive;
extern bool topScoring;
extern bool antlerActive;

void  vexcodeInit( void );