#include "includes.hpp"

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
	// Controller::registerButtonNewPress(pros::E_CONTROLLER_DIGITAL_Y, BackClaw::toggle);
	// Controller::registerButtonNewPress(pros::E_CONTROLLER_DIGITAL_X, BackClaw::toggleTilter);
	// Controller::registerButtonNewPress(pros::E_CONTROLLER_DIGITAL_B, FrontClaw::up);
	// Controller::registerButtonNewPress(pros::E_CONTROLLER_DIGITAL_A, FrontClaw::down);
	// Controller::registerButton(pros::E_CONTROLLER_DIGITAL_R2, Intake::intake, Intake::intakeHold);
	// Controller::registerButton(pros::E_CONTROLLER_DIGITAL_R1, Intake::outtake, Intake::outtakeHold);
	// Controller::registerButton(pros::E_CONTROLLER_DIGITAL_L1, Lift::moveUp, Lift::upHold);
	// Controller::registerButton(pros::E_CONTROLLER_DIGITAL_L2, Lift::moveDown, Lift::downHold);
	Controller::registerButtonNewPress(pros::E_CONTROLLER_DIGITAL_DOWN, autonomous);
	while (true) {
		
		Drive::drive(0);
		Controller::update();
		Controller::act();
        pros::delay(20);
	}
}