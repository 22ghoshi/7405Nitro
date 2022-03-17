#include "Lift.hpp"

Lift::Lift(double kP, double kI, double kD, int delay) : liftPID(kP, kI, kD) {
    up = false;
    down = false;
    this->delay = delay;
    delayn = 0;
}

void Lift::moveUp() {
    up = true;
    delayn = 0;
    Devices::get<motors::Lift>() = 127;
}

void Lift::upHold() {
    up = false;
    hold();
}

void Lift::moveDown() {
    down = true;
    delayn = 0;
    Devices::get<motors::Lift>() = -127;
}

void Lift::downHold() {
    down = false;
    hold();
}

void Lift::hold() {
    if (!(up || down)) {
        Devices::get<motors::Lift>().move_velocity(0);
        Devices::get<motors::Lift>().set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        delayn++;
        if (delayn == delay) {
            holdVal = Devices::get<motors::Lift>().get_position();
        }
        if (delayn >= delay) {
            double err = holdVal - Devices::get<motors::Lift>().get_position();
            if (fabs(err) > 10) {
                Devices::get<motors::Lift>() = liftPID.getPID(err);
            }
            else {
                liftPID.reset = true;
                Devices::get<motors::Lift>().move_velocity(0);
                Devices::get<motors::Lift>().set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
            }
        }
    }
}