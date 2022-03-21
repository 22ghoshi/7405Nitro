#include "Lift.hpp"

PID Lift::liftPID;
bool Lift::up;
bool Lift::down;
int Lift::delay;
int Lift::delayn;
double Lift::holdVal;

Lift::Lift(double kP, double kI, double kD, int delayset) {
    up = false;
    down = false;
    delay = delayset;
    delayn = 0;
    liftPID = PID(kP, kI, kD);
}

void Lift::moveUp() {
    if (down) {
        down = false;
    }
    up = true;
    delayn = 0;
    Devices::get<motors::Lift>() = 127;
}

void Lift::upHold() {
    up = false;
    hold();
}

void Lift::moveDown() {
    if (up) {
        up = false;
    }
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