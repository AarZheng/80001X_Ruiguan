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

void leftHood(bool allColor);
void rightHood(bool allColor);
void leftWing(bool allColor);
void rightWing(bool allColor);
void leftCenterLong(bool allColor);
void rightCenterLong(bool allColor);
void leftCenter(bool allColor);
void rightCenter(bool allColor);
void sawpRight(bool allColor);
void temp(bool allColor);
void skills();

extern thread intakeThread;