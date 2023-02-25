#include "main.h"
#include <iostream>
#include <ostream>

int DRIVE_SPEED = 110; // drive spped is 110/127
                       // suggested for more accuracy with IMU
int TURN_SPEED = 87;   // drive spped is 87/127
                       // suggested for more accuracy with IMU

void Auton1() {
    chassis.SetDrivePid(12, DRIVE_SPEED);
    chassis.Wait();
}

void Auton2() {
}

void Auton3() {
}

void Auton4() {
}

void Auton5() {
}

void Auton6() {
}

void Auton7() {
}

void Auton8() {
}

void ProgSkills() {
}

void AutonInit() {
    auton::AddAuton(Auton("Auton 1", Auton1));
    auton::AddAuton(Auton("Auton 2", Auton2));
    auton::AddAuton(Auton("Auton 3", Auton3));
    auton::AddAuton(Auton("Auton 4", Auton4));
    auton::AddAuton(Auton("Auton 5", Auton5));
    auton::AddAuton(Auton("Auton 6", Auton6));
    auton::AddAuton(Auton("Auton 7", Auton7));
    auton::AddAuton(Auton("Auton 8", Auton8));
    auton::AddAuton(Auton("Prog\nSkills", ProgSkills));
}