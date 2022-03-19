#include "includes.hpp"

void left() {

}

void middle() {

}

void right() {

}

void skills() {

}

void test() {
    
}

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
    Devices::get<sensors::Inertial>().tare_rotation();
    pros::delay(20);
    Thread::startTask("move", Robot::move);

    switch(auton) {
        case autons::left:
            left();
            break;
        case autons::middle:
            middle();
            break;
        case autons::right:
            right();
            break;
        case autons::skills:
            skills();
            break;
        case autons::test:
            test();
            break;
    }
    Robot::waitUntilStop();
    Thread::notifyTask("move");
    pros::delay(20);
    Thread::killTask("move");
    Robot::drive.stop();
}