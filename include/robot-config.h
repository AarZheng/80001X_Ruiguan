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

extern motor intakeFront;
extern motor intakeBack;
extern motor intakeTop;
extern motor agitator;

extern motor_group intakeMotors;

extern pneumatics matchload;
extern pneumatics hood;

extern bool matchloadActive;
extern bool topScoring;

void  vexcodeInit( void );