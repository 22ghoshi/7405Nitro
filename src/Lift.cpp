#include "Lift.hpp"

PID Lift::liftPID(1.0, 0.0005, 0);
bool Lift::up(false);
bool Lift::down(false);
double Lift::lowerBound(21.4);
double Lift::upperBound(141);
int Lift::delay(40);
int Lift::delayn(0);
double Lift::holdVal = lowerBound;

Lift::Lift() {
    Device::get<motor::Lift>()->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void Lift::moveUp() {
    if (down) {
        down = false;
    }
    up = true;
    delayn = 0;
    Device::get<motor::Lift>()->move(127);
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
        Device::get<motor::Lift>()->move(-127);
}

void Lift::downHold() {
    down = false;
    hold();
}

void Lift::hold() {
    if (!(up || down)) {
        delayn++;
        if (delayn < delay) {
            Device::get<motor::Lift>()->brake();
        }
        if (delayn == delay) {
            holdVal = Device::get<sensor::LiftPotentiometer>()->get_angle();
        }
        if (delayn >= delay) {
            double err = holdVal - Device::get<sensor::LiftPotentiometer>()->get_angle();
            if (fabs(err) > 1.0) {
                Device::get<motor::Lift>()->move(liftPID.getPID(err));
            }
            else {
                liftPID.reset = true;
                Device::get<motor::Lift>()->brake();
            }
        }
    }
}

void Lift::move(void* params) {
    while (true) {
        double err = holdVal - Device::get<sensor::LiftPotentiometer>()->get_angle();
        printf("\nlift err: %.2f", err);
        if (fabs(err) > 0.5) {
            Device::get<motor::Lift>()->move(liftPID.getPID(err));
        }
        else {
            liftPID.reset = true;
            Device::get<motor::Lift>()->brake();
        }
    }

}

void Lift::autonTarget(double target) {
    holdVal = target;
}