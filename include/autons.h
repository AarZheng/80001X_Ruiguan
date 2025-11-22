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

void leftLong(bool allColor);
void rightLong(bool allColor);
void leftCenterLong(bool allColor);
void rightCenterLong(bool allColor);
void leftCenter(bool allColor);
void rightCenter(bool allColor);
void sawp(bool allColor);
void temp(bool allColor);
void skills();

extern thread intakeThread;