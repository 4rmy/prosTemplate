#include "prosTemplate.h"
#include "api.h"
#include "display/lv_core/lv_obj.h"
#include "display/lv_core/lv_style.h"
#include "display/lv_misc/lv_area.h"
#include "display/lv_misc/lv_color.h"
#include "display/lv_objx/lv_btn.h"
#include "display/lv_objx/lv_canvas.h"
#include "display/lv_objx/lv_label.h"
#include "display/lv_themes/lv_theme.h"
#include "display/lv_themes/lv_theme_night.h"

double targetAngle = 0;
int leftTurnSpeed = 0;
int rightTurnSpeed = 0;
bool turning = false;

double currentX = 0.0;
double currentZ = 0.0;
double targetDistance = 0.0;
int leftDriveSpeed = 0;
int rightDriveSpeed = 0;
bool driving = false;

Auton prosTemplate::autons[]{};

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
    lv_obj_t * canvas = lv_canvas_create(lv_scr_act(), NULL);
    lv_obj_set_x(canvas, 0);
    lv_obj_set_y(canvas, 0);
    lv_obj_set_width(canvas, 480);
    lv_obj_set_height(canvas, 270);

    lv_obj_t * text = lv_label_create(canvas, NULL);
    lv_label_set_text(text, "Hello prosTemplate User!");
    lv_obj_set_x(text, 5);
    lv_obj_set_y(text, 5);
}

void auton::AddAuton(Auton auton) {
    prosTemplate::autons[prosTemplate::autonCount] = auton;
    prosTemplate::autonCount++;
}

Auton::Auton(std::string name, std::function<void()> auton) {
    this->name = name;
    this->auton = auton;
}

void auton::AutonSelector() {
    int width = 480;
    int height = 270;

    lv_theme_t * th = lv_theme_get_night();
    lv_theme_set_current(th);

    lv_obj_t * canvas = lv_canvas_create(lv_scr_act(), NULL);
    lv_obj_set_x(canvas, 0);
    lv_obj_set_y(canvas, 0);
    lv_obj_set_width(canvas, width);
    lv_obj_set_height(canvas, height);

    lv_obj_t * header = lv_label_create(canvas, NULL);
    lv_obj_set_x(header, 5);
    lv_obj_set_y(header, 5);
    lv_label_set_text(header, "Auton Selector: ");

    int btnWidth = 150;
    lv_obj_t * autonbtn = lv_btn_create(canvas, NULL);
    lv_obj_t * label = lv_label_create(autonbtn, NULL);
    lv_label_set_text(label, prosTemplate::autons[0].name.c_str());
    lv_label_set_align(label, LV_ALIGN_CENTER);
    lv_obj_set_x(autonbtn, width/prosTemplate::autonCount);
    lv_obj_set_y(autonbtn, (height/2)-(btnWidth/2));
    lv_obj_set_width(autonbtn, btnWidth);
    lv_obj_set_height(autonbtn, btnWidth);

    for (int i = 1; i < prosTemplate::autonCount; i++) {
        int btnWidth = 150;
        autonbtn = lv_btn_create(canvas, NULL);
        label = lv_label_create(autonbtn, NULL);
        lv_label_set_text(label, prosTemplate::autons[i].name.c_str());
        lv_label_set_align(label, LV_ALIGN_CENTER);
        lv_obj_set_x(autonbtn, width/prosTemplate::autonCount);
        lv_obj_set_y(autonbtn, (height/2)-(btnWidth/2));
        lv_obj_set_width(autonbtn, btnWidth);
        lv_obj_set_height(autonbtn, btnWidth);
    }
}

void auton::RunAuton() {
    prosTemplate::autons[prosTemplate::selected].auton();
}

void Drive::setTank(int left, int right) {
    std::vector<std::int8_t> leftside = {static_cast<signed char>(leftDrive[0]), static_cast<signed char>(leftDrive[1]), static_cast<signed char>(leftDrive[2])};
    std::vector<std::int8_t> rightside = {static_cast<signed char>(rightDrive[0]), static_cast<signed char>(rightDrive[1]), static_cast<signed char>(rightDrive[2])};
    pros::Motor_Group leftMG {leftside};
    pros::Motor_Group rightMG {rightside};

    leftMG.move_voltage(left*12000);
    rightMG.move_voltage(right*12000);
}

void (Drive::*CheckTurn)(void);

void Drive::CheckTurn() {
    pros::Imu IMU (IMUport);
    while (turning) {

        // within 5 degrees
        if (IMU.get_heading() > boundAngle(targetAngle-5) || IMU.get_heading() < boundAngle(targetAngle+5)) {
            Drive::setTank(leftTurnSpeed/2, rightTurnSpeed/2);
        } else if (IMU.get_heading() > boundAngle(targetAngle-1) || IMU.get_heading() < boundAngle(targetAngle+1)) {
            Drive::setTank(leftTurnSpeed/3, rightTurnSpeed/3);
        } else if (IMU.get_heading() > boundAngle(targetAngle-0.5) || IMU.get_heading() < boundAngle(targetAngle+0.5)) {
            Drive::setTank(0, 0);
            turning = false;
        }
        pros::delay(prosTemplate::delay);
    }
}

void Drive::SetTurnPid(double target, int TurnSpeed) {
    pros::Imu IMU (IMUport);

    // get new direction
    double angle = IMU.get_heading() + target;

    // roll to boundaries
    targetAngle = boundAngle(angle);

    // set tank correct direction
    if (target < 0) {
        Drive::setTank(-TurnSpeed, TurnSpeed);
        leftTurnSpeed = -TurnSpeed;
        rightTurnSpeed = TurnSpeed;
    } else if (target > 0) {
        Drive::setTank(TurnSpeed, -TurnSpeed);
        leftTurnSpeed = TurnSpeed;
        rightTurnSpeed = -TurnSpeed;
    }

    // set correct action for wait
    turning = true;
    //pros::Task turnTask(&Drive::CheckTurn, "turn");
}

void (Drive::*CheckDrive)(void);

void Drive::CheckDrive()  {
    pros::Imu IMU (Drive::IMUport);
    while (driving) {
        currentX += IMU.get_accel().x;
        currentZ += IMU.get_accel().z;
        double distance = sqrt((currentX*currentX) + (currentZ*currentX));

        if (distance > targetDistance-3 || distance < targetDistance+3) {
            Drive::setTank(leftDriveSpeed/2, rightDriveSpeed/2);
        } else if (distance > targetDistance-1 || distance < targetDistance+1) {
            Drive::setTank(leftDriveSpeed/3, rightDriveSpeed/3);
        } else if (distance > targetDistance-0.5 || distance < targetDistance+0.5) {
            Drive::setTank(0, 0);
            driving = false;
        }
        pros::delay(prosTemplate::delay);
    }
}

void Drive::SetDrivePid(double target, int DriveSpeed) {
    pros::Imu IMU (IMUport);

    // reset local coords
    currentX = 0.0;
    currentZ = 0.0;
    targetDistance = target;

    if (target < 0) {
        Drive::setTank(-DriveSpeed, -DriveSpeed);
    } else if (target > 0) {
        Drive::setTank(DriveSpeed, DriveSpeed);
    }

    driving = true;
    //pros::Task driveTask(&Drive::CheckDrive, "turn");
}

void Drive::Wait() {
    while (turning || driving) {
        pros::delay(prosTemplate::delay);
    }
}