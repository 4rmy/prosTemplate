#include "main.h"

int DRIVE_SPEED = 110; // drive spped is 110/127
                       // suggested for more accuracy with IMU
int TURN_SPEED = 87;   // drive spped is 87/127
                       // suggested for more accuracy with IMU

void basicAuton() {
    chassis.SetDrivePid(12, DRIVE_SPEED);
    chassis.Wait();
}

void AutonInit() {
    prosTemplate::auton::AddAuton(Auton("Basic Auton", basicAuton));
}