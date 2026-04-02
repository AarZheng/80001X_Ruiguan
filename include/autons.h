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

void left4Wing(bool allColor);
void right4Wing(bool allColor);
void left7Wing(bool allColor);
void right7Wing(bool allColor);
void delayedRight7Wing(bool allColor);
void delayedLeft7Wing(bool allColor);
void leftCenterLong(bool allColor);
void rightCenterLong(bool allColor);
void leftCenter(bool allColor);
void rightCenter(bool allColor);
void rightSawp(bool allColor);
void temp(bool allColor);
void skills();
void rightCounter7Ball(bool allColor);
void leftCounter7Ball(bool allColor);

extern thread intakeThread;