#include "prosTemplate.h"
#include "pros/imu.hpp"
#include "pros/motors.hpp"
#include "pros/optical.h"
#include <array>
#include <cmath>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <vector>

int action = 0;

double targetAngle = 0;
int leftTurnSpeed = 0;
int rightTurnSpeed = 0;

double currentX = 0.0;
double currentZ = 0.0;
double targetDistance = 0.0;
int leftDriveSpeed = 0;
int rightDriveSpeed = 0;

double boundAngle(double angle) {
    while (angle <= 0) {
        angle += 360;
    }
    while (angle > 360) {
        angle -= 360;
    }
    return angle;
}

void prosTemplate::lcdInit() {
    pros::lcd::clear();
    pros::lcd::print(0, "Hello prosTemplate user");
}

void prosTemplate::auton::AddAuton(Auton auton) {
    autons[autonCount] = auton;
    autonCount++;
}

Auton::Auton(std::string name, std::function<void()> auton) {
    this->name = name;
    this->auton = auton;
}

void prosTemplate::auton::AutonSelector() {
    pros::screen::set_pen(0x00000000);
    pros::screen::fill_rect(0, 0, 480, 272);
    
    int y = 0;
    for (int i = 0; i < autonCount; i++) {
        pros::screen::set_pen(0x00FF0000);
        if (i % 3 == 0) {
            y++;
        }
        pros::screen::fill_rect(5 + i*20, 5 + y*25, 25 + i*20, 25 + y*25);
        pros::screen::set_pen(0x00FFFFFF);
        pros::screen::print(pros::E_TEXT_MEDIUM,i, 0, autons[i].name);
    }
}

void prosTemplate::auton::RunAuton() {
    autons[selected].auton();
}

void Drive::setTank(int left, int right) {
    std::vector<std::int8_t> leftside = {static_cast<signed char>(leftDrive[0]), static_cast<signed char>(leftDrive[1]), static_cast<signed char>(leftDrive[2])};
    std::vector<std::int8_t> rightside = {static_cast<signed char>(rightDrive[0]), static_cast<signed char>(rightDrive[1]), static_cast<signed char>(rightDrive[2])};
    pros::Motor_Group leftMG {leftside};
    pros::Motor_Group rightMG {rightside};

    leftMG.move_voltage(left*12000);
    rightMG.move_voltage(right*12000);
}

void Drive::SetTurnPid(double target, int TurnSpeed) {
    pros::Imu IMU (IMUport);

    // get new direction
    double angle = IMU.get_heading() + target;

    // roll to boundaries
    targetAngle = boundAngle(angle);

    // set tank correct direction
    if (target < 0) {
        setTank(-TurnSpeed, TurnSpeed);
        leftTurnSpeed = -TurnSpeed;
        rightTurnSpeed = TurnSpeed;
    } else if (target > 0) {
        setTank(TurnSpeed, -TurnSpeed);
        leftTurnSpeed = TurnSpeed;
        rightTurnSpeed = -TurnSpeed;
    }

    // set correct action for wait
    action = 1;
}

void Drive::CheckTurn() {
    pros::Imu IMU (IMUport);

    // within 5 degrees
    if (IMU.get_heading() > boundAngle(targetAngle-5) || IMU.get_heading() < boundAngle(targetAngle+5)) {
        setTank(leftTurnSpeed/2, rightTurnSpeed/2);
    } else if (IMU.get_heading() > boundAngle(targetAngle-1) || IMU.get_heading() < boundAngle(targetAngle+1)) {
        setTank(leftTurnSpeed/3, rightTurnSpeed/3);
    } else if (IMU.get_heading() > boundAngle(targetAngle-0.5) || IMU.get_heading() < boundAngle(targetAngle+0.5)) {
        setTank(0, 0);
        action = 0;
    }
}

void Drive::SetDrivePid(double target, int DriveSpeed) {
    pros::Imu IMU (IMUport);

    // reset local coords
    currentX = 0.0;
    currentZ = 0.0;
    targetDistance = target;

    if (target < 0) {
        setTank(-DriveSpeed, -DriveSpeed);
    } else if (target > 0) {
        setTank(DriveSpeed, DriveSpeed);
    }

    action = 2;
}

void Drive::CheckDrive()  {
    pros::Imu IMU (IMUport);

    currentX += IMU.get_accel().x;
    currentZ += IMU.get_accel().z;
    double distance = sqrt((currentX*currentX) + (currentZ*currentX));

    if (distance > targetDistance-3 || distance < targetDistance+3) {
        setTank(leftDriveSpeed/2, rightDriveSpeed/2);
    } else if (distance > targetDistance-1 || distance < targetDistance+1) {
        setTank(leftDriveSpeed/3, rightDriveSpeed/3);
    } else if (distance > targetDistance-0.5 || distance < targetDistance+0.5) {
        setTank(0, 0);
        action = 0;
    }
}

void Drive::WaitDrive() {
    while (action != 0) {
        if (action == 1) {
            CheckTurn();
        }
        pros::delay(prosTemplate::delay);
    }
}