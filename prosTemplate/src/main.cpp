#include "main.h"
#include "pros/imu.hpp"
#include "pros/misc.h"
#include <ios>
/**
 * Bot chassis setup. Nessicary for driving and autons.
 * 
 */
Drive chassis {
	{1, 2, 3},
	{4, 5, 6},
	(float) 60/30,
	14
};

void tank();
void arcade();
void inverseArcade();


void initialize() {
	pros::Imu IMU (chassis.IMUport);
	IMU.reset();
	pros::lcd::initialize();
	prosTemplate::lcdInit();
	AutonInit();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	/**
	 * @brief Construct a new pros Template::auton::Auton Selector object
	 * Built in auton selector to better stone all functioning autons
	 * for your bot.
	 */
	prosTemplate::auton::RunAuton(); // REQUIRED FOR AUTON SELECTOR
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller controller(pros::E_CONTROLLER_MASTER);

	while (true) {
		/**
		 * Preset Driving methods for easy driver setup.
		 */
		// tank();
		arcade();
		// inverseArcade();

		pros::delay(prosTemplate::delay); // LEAVE THIS DELAY AS IS
													   // IT IS NESSICARY FOR TIMING
	}
}

void tank() {
	pros::Controller controller(pros::E_CONTROLLER_MASTER);
	chassis.setTank(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)/100, controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)/100);
}

void arcade() {
	pros::Controller controller(pros::E_CONTROLLER_MASTER);
	int left = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
	int right = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
	chassis.setTank(left, right);
}

void inverseArcade() {
	pros::Controller controller(pros::E_CONTROLLER_MASTER);
	int left = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) + controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int right = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) - controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	chassis.setTank(left, right);
}