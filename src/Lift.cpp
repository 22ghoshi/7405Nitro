#include "Lift.hpp"

PID Lift::liftPID(0.3, 0.001, 0.1);
bool Lift::up(false);
bool Lift::down(false);
int Lift::delay(40);
int Lift::delayn(0);
double Lift::holdVal(0);

Lift::Lift() {}

void Lift::moveUp() {
    if (down) {
        down = false;
    }
    up = true;
    delayn = 0;
    Device::get<motor::Lift>() = 127;
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
    Device::get<motor::Lift>() = -127;
}

void Lift::downHold() {
    down = false;
    hold();
}

void Lift::hold() {
    if (!(up || down)) {
        Device::get<motor::Lift>().move_velocity(0);
        Device::get<motor::Lift>().set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        delayn++;
        if (delayn == delay) {
            holdVal = Device::get<motor::Lift>().get_position();
        }
        if (delayn >= delay) {
            double err = holdVal - Device::get<motor::Lift>().get_position();
            if (fabs(err) > 10) {
                Device::get<motor::Lift>() = liftPID.getPID(err);
            }
            else {
                liftPID.reset = true;
                Device::get<motor::Lift>().move_velocity(0);
                Device::get<motor::Lift>().set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
            }
        }
    }
}