#include "Intake.hpp"

bool Intake::intaking;
bool Intake::outtaking;
double Intake::intakeSpeed;
double Intake::outtakeSpeed;

Intake::Intake(double intake, double outtake) {
    intaking = false;
    outtaking = false;
    intakeSpeed = intake;
    outtakeSpeed = outtake;
    Device::get<motor::Intake>()->set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void Intake::intake() {
    if (outtaking) {
        outtaking = false;
    }
    intaking = true;
    Device::get<motor::Intake>()->move(intakeSpeed);
}

void Intake::intakeHold() {
    intaking = false;
    hold();
}

void Intake::outtake() {
    if (intaking) {
        intaking = false;
    }
    outtaking = true;
    Device::get<motor::Intake>()->move(outtakeSpeed);
}

void Intake::outtakeHold() {
    outtaking = false;
    hold();
}

void Intake::toggle() {
    if (intaking) {
        intaking = false;
        hold();
    }
    else if (!(intaking || outtaking)) {
        intaking = true;
        Device::get<motor::Intake>()->move(intakeSpeed);
    }
}

void Intake::hold() {
    if (!(intaking || outtaking)) {
        Device::get<motor::Intake>()->brake();
    }
}