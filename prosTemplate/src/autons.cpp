#include "main.h"

int DRIVE_SPEED = 100; // drive spped is 100/127
                      // suggested for more accuracy with IMU
int TURN_SPEED = 87; // drive spped is 87/127
                      // suggested for more accuracy with IMU

void basicAuton() {
    chassis.SetDrivePid(12, DRIVE_SPEED);
    chassis.WaitDrive();

    chassis.SetTurnPid(-45, TURN_SPEED);
    chassis.WaitDrive();

    chassis.SetTurnPid(90, TURN_SPEED);
    chassis.WaitDrive();

    chassis.SetDrivePid(-12, DRIVE_SPEED);
    chassis.WaitDrive();
}

void AutonInit() {
    prosTemplate::auton::AddAuton(Auton("Basic Auton", basicAuton));
}