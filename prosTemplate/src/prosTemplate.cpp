#include "prosTemplate.h"
#include "api.h"
#include "display/lv_core/lv_obj.h"
#include "display/lv_core/lv_style.h"
#include "display/lv_draw/lv_draw_line.h"
#include "display/lv_draw/lv_draw_rect.h"
#include "display/lv_fonts/lv_font_builtin.h"
#include "display/lv_misc/lv_area.h"
#include "display/lv_misc/lv_color.h"
#include "display/lv_misc/lv_font.h"
#include "display/lv_objx/lv_btn.h"
#include "display/lv_objx/lv_btnm.h"
#include "display/lv_objx/lv_canvas.h"
#include "display/lv_objx/lv_img.h"
#include "display/lv_objx/lv_label.h"
#include <cstddef>
#include <iterator>
#include "242.h"

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

Auton prosTemplate::autons[9] = {
    Auton("Blank", NULL),
    Auton("Blank", NULL),
    Auton("Blank", NULL),
    Auton("Blank", NULL),
    Auton("Blank", NULL),
    Auton("Blank", NULL),
    Auton("Blank", NULL),
    Auton("Blank", NULL),
    Auton("Blank", NULL)
};

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

void draw();

lv_res_t atnAction0(lv_obj_t *btn){
	draw();
    prosTemplate::selected=0;
    return LV_RES_OK;
}
lv_res_t atnAction1(lv_obj_t *btn){
	draw();
    prosTemplate::selected=1;
    return LV_RES_OK;
}
lv_res_t atnAction2(lv_obj_t *btn){
	draw();
    prosTemplate::selected=2;
    return LV_RES_OK;
}
lv_res_t atnAction3(lv_obj_t *btn){
	draw();
    prosTemplate::selected=3;
    return LV_RES_OK;
}
lv_res_t atnAction4(lv_obj_t *btn){
	draw();
    prosTemplate::selected=4;
    return LV_RES_OK;
}
lv_res_t atnAction5(lv_obj_t *btn){
	draw();
    prosTemplate::selected=5;
    return LV_RES_OK;
}
lv_res_t atnAction6(lv_obj_t *btn){
	draw();
    prosTemplate::selected=6;
    return LV_RES_OK;
}
lv_res_t atnAction7(lv_obj_t *btn){
	draw();
    prosTemplate::selected=7;
    return LV_RES_OK;
}
lv_res_t atnAction8(lv_obj_t *btn){
	draw();
    prosTemplate::selected=8;
    return LV_RES_OK;
}

void draw() {
    static lv_style_t style_btn_rel;
    lv_style_copy(&style_btn_rel, &lv_style_plain);
    style_btn_rel.body.radius = 10;
    style_btn_rel.body.border.width = 2;
    style_btn_rel.body.border.color.alpha = 255;
    style_btn_rel.body.border.color.red = 255;
    style_btn_rel.body.border.color.green = 0;
    style_btn_rel.body.border.color.blue = 0;
    style_btn_rel.body.main_color.alpha = 255;
    style_btn_rel.body.main_color.red = 50;
    style_btn_rel.body.main_color.green = 50;
    style_btn_rel.body.main_color.blue = 50;
    style_btn_rel.body.grad_color.full = style_btn_rel.body.main_color.full;
    style_btn_rel.text.color.full = 0xFFFFFFFF;

    static lv_style_t style_btn_pr;
    lv_style_copy(&style_btn_pr, &style_btn_rel);
    style_btn_rel.body.main_color.red = 255;
    style_btn_rel.body.main_color.green = 255;
    style_btn_rel.body.main_color.blue = 255;
    style_btn_rel.body.grad_color.full = style_btn_rel.body.main_color.full;
    style_btn_rel.text.color.full = 0xFF000000;
    

    lv_obj_t * canvas = lv_canvas_create(lv_scr_act(), NULL);
    lv_obj_set_x(canvas, 0);
    lv_obj_set_y(canvas, 0);
    lv_obj_set_width(canvas, 480);
    lv_obj_set_height(canvas, 240);

    int x = 0;
    int i = 0;

    lv_obj_t * atn1 = lv_btn_create(canvas, NULL);
    lv_obj_set_x(atn1, 5 + x*85);
    lv_obj_set_y(atn1, 5);
    lv_obj_set_width(atn1, 75);
    lv_obj_set_height(atn1, 75);
    lv_btn_set_action(atn1, LV_BTN_ACTION_CLICK, *atnAction0);
    lv_btn_set_style(atn1, LV_BTN_STYLE_PR, &style_btn_rel);
    lv_btn_set_style(atn1, LV_BTN_STYLE_REL, &style_btn_pr);
    lv_obj_t * atn1lbl = lv_label_create(atn1, NULL);
    lv_label_set_text(atn1lbl, prosTemplate::autons[i].name.c_str());
    lv_label_set_align(atn1lbl, LV_LABEL_ALIGN_CENTER);

    x++;
    i++;

    lv_obj_t * atn2 = lv_btn_create(canvas, NULL);
    lv_obj_set_x(atn2, 5 + x*85);
    lv_obj_set_y(atn2, 5);
    lv_obj_set_width(atn2, 75);
    lv_obj_set_height(atn2, 75);
    lv_btn_set_action(atn2, LV_BTN_ACTION_CLICK, *atnAction1);
    lv_btn_set_style(atn2, LV_BTN_STYLE_PR, &style_btn_rel);
    lv_btn_set_style(atn2, LV_BTN_STYLE_REL, &style_btn_pr);
    lv_obj_t * atn2lbl = lv_label_create(atn2, NULL);
    lv_label_set_text(atn2lbl, prosTemplate::autons[i].name.c_str());
    lv_label_set_align(atn2lbl, LV_LABEL_ALIGN_CENTER);

    x++;
    i++;

    lv_obj_t * atn3 = lv_btn_create(canvas, NULL);
    lv_obj_set_x(atn3, 5 + x*85);
    lv_obj_set_y(atn3, 5);
    lv_obj_set_width(atn3, 75);
    lv_obj_set_height(atn3, 75);
    lv_btn_set_action(atn3, LV_BTN_ACTION_CLICK, *atnAction2);
    lv_btn_set_style(atn3, LV_BTN_STYLE_PR, &style_btn_rel);
    lv_btn_set_style(atn3, LV_BTN_STYLE_REL, &style_btn_pr);
    lv_obj_t * atn3lbl = lv_label_create(atn3, NULL);
    lv_label_set_text(atn3lbl, prosTemplate::autons[i].name.c_str());
    lv_label_set_align(atn3lbl, LV_LABEL_ALIGN_CENTER);

    x++;
    i++;

    lv_obj_t * atn4 = lv_btn_create(canvas, NULL);
    lv_obj_set_x(atn4, 5 + x*85);
    lv_obj_set_y(atn4, 5);
    lv_obj_set_width(atn4, 75);
    lv_obj_set_height(atn4, 75);
    lv_btn_set_action(atn4, LV_BTN_ACTION_CLICK, *atnAction3);
    lv_btn_set_style(atn4, LV_BTN_STYLE_PR, &style_btn_rel);
    lv_btn_set_style(atn4, LV_BTN_STYLE_REL, &style_btn_pr);
    lv_obj_t * atn4lbl = lv_label_create(atn4, NULL);
    lv_label_set_text(atn4lbl, prosTemplate::autons[i].name.c_str());
    lv_label_set_align(atn4lbl, LV_LABEL_ALIGN_CENTER);

    x = 0;
    i++;

    lv_obj_t * atn5 = lv_btn_create(canvas, NULL);
    lv_obj_set_x(atn5, 5 + x*85);
    lv_obj_set_y(atn5, 160);
    lv_obj_set_width(atn5, 75);
    lv_obj_set_height(atn5, 75);
    lv_btn_set_action(atn5, LV_BTN_ACTION_CLICK, *atnAction4);
    lv_btn_set_style(atn5, LV_BTN_STYLE_PR, &style_btn_rel);
    lv_btn_set_style(atn5, LV_BTN_STYLE_REL, &style_btn_pr);
    lv_obj_t * atn5lbl = lv_label_create(atn5, NULL);
    lv_label_set_text(atn5lbl, prosTemplate::autons[i].name.c_str());
    lv_label_set_align(atn5lbl, LV_LABEL_ALIGN_CENTER);

    x++;
    i++;

    lv_obj_t * atn6 = lv_btn_create(canvas, NULL);
    lv_obj_set_x(atn6, 5 + x*85);
    lv_obj_set_y(atn6, 160);
    lv_obj_set_width(atn6, 75);
    lv_obj_set_height(atn6, 75);
    lv_btn_set_action(atn6, LV_BTN_ACTION_CLICK, *atnAction5);
    lv_btn_set_style(atn6, LV_BTN_STYLE_PR, &style_btn_rel);
    lv_btn_set_style(atn6, LV_BTN_STYLE_REL, &style_btn_pr);
    lv_obj_t * atn6lbl = lv_label_create(atn6, NULL);
    lv_label_set_text(atn6lbl, prosTemplate::autons[i].name.c_str());
    lv_label_set_align(atn6lbl, LV_LABEL_ALIGN_CENTER);

    x++;
    i++;

    lv_obj_t * atn7 = lv_btn_create(canvas, NULL);
    lv_obj_set_x(atn7, 5 + x*85);
    lv_obj_set_y(atn7, 160);
    lv_obj_set_width(atn7, 75);
    lv_obj_set_height(atn7, 75);
    lv_btn_set_action(atn7, LV_BTN_ACTION_CLICK, *atnAction6);
    lv_btn_set_style(atn7, LV_BTN_STYLE_PR, &style_btn_rel);
    lv_btn_set_style(atn7, LV_BTN_STYLE_REL, &style_btn_pr);
    lv_obj_t * atn7lbl = lv_label_create(atn7, NULL);
    lv_label_set_text(atn7lbl, prosTemplate::autons[i].name.c_str());
    lv_label_set_align(atn7lbl, LV_LABEL_ALIGN_CENTER);

    x++;
    i++;

    lv_obj_t * atn8 = lv_btn_create(canvas, NULL);
    lv_obj_set_x(atn8, 5 + x*85);
    lv_obj_set_y(atn8, 160);
    lv_obj_set_width(atn8, 75);
    lv_obj_set_height(atn8, 75);
    lv_btn_set_action(atn8, LV_BTN_ACTION_CLICK, *atnAction7);
    lv_btn_set_style(atn8, LV_BTN_STYLE_PR, &style_btn_rel);
    lv_btn_set_style(atn8, LV_BTN_STYLE_REL, &style_btn_pr);
    lv_obj_t * atn8lbl = lv_label_create(atn8, NULL);
    lv_label_set_text(atn8lbl, prosTemplate::autons[i].name.c_str());
    lv_label_set_align(atn8lbl, LV_LABEL_ALIGN_CENTER);

    i++;

    lv_obj_t * skills = lv_btn_create(canvas, NULL);
    lv_obj_set_x(skills, 355);
    lv_obj_set_y(skills, 135);
    lv_obj_set_width(skills, 100);
    lv_obj_set_height(skills, 100);
    lv_btn_set_action(skills, LV_BTN_ACTION_CLICK, *atnAction8);
    lv_btn_set_style(skills, LV_BTN_STYLE_PR, &style_btn_rel);
    lv_btn_set_style(skills, LV_BTN_STYLE_REL, &style_btn_pr);
    lv_obj_t * skillslbl = lv_label_create(skills, NULL);
    lv_label_set_text(skillslbl, prosTemplate::autons[i].name.c_str());
    lv_label_set_align(skillslbl, LV_LABEL_ALIGN_CENTER);
}

void auton::AutonSelector() {
    draw();
}

void auton::RunAuton() {
    if (prosTemplate::autons[prosTemplate::selected].auton != NULL) {
        prosTemplate::autons[prosTemplate::selected].auton();
    }
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