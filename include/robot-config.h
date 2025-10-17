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
extern pneumatics descore;

extern optical colorSorter;
extern distance frontDist;
extern distance rightDist;
extern distance leftDist;
extern distance backDist;

extern bool matchloadActive;
extern bool topScoring;
extern bool descoreActive;

void  vexcodeInit( void );