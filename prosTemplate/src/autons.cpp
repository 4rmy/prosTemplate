#include "main.h"
#include <iostream>
#include <ostream>

int DRIVE_SPEED = 110; // drive spped is 110/127
                       // suggested for more accuracy with IMU
int TURN_SPEED = 87;   // drive spped is 87/127
                       // suggested for more accuracy with IMU

void basicAuton() {
    chassis.SetDrivePid(12, DRIVE_SPEED);
    chassis.Wait();
}

void fancyAuton() {
    chassis.SetDrivePid(12, DRIVE_SPEED);
    chassis.Wait();
}

void AutonInit() {
    auton::AddAuton(Auton("Basic Auton", basicAuton));
    auton::AddAuton(Auton("Fancy Auton", fancyAuton));
    
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