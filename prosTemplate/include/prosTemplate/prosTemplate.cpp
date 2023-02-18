#include "prosTemplate.h"
#include <array>
#include <functional>
#include <iostream>
#include <iterator>

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