#pragma once
#include "JAR-Template/drive.h"

class Drive;

extern Drive chassis;

void default_constants();
void odom_constants();

void drive_test();
void turn_test();
void swing_test();
void full_test();
void odom_test();
void tank_odom_test();
void holonomic_odom_test();

// void left4Wing(bool allColor);
// void right4Wing(bool allColor);
void left7Wing();
void right7Wing();
void delayedRight7Wing();
void delayedLeft7Wing();
void leftCenterLong();
void rightCenterLong();
void rightSawp();
void temp(bool allColor);
void skills();
void rightCounter7Ball();
void leftCounter7Ball();

extern thread intakeThread;