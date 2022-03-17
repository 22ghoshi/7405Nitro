#include "Intake.hpp"

Intake::Intake(double intakeSpeed, double outtakeSpeed) {
    intaking = false;
    outtaking = false;
    this->intakeSpeed = intakeSpeed;
    this->outtakeSpeed = outtakeSpeed;
}

void intake() {
    intaking = true;
    Devices::get<motors::Intake>() = intakeSpeed;
}

void intakeHold() {
    intaking = false;
    hold();
}

void outtake() {
    outtaking = true;
    Devices::get<motors::Intake>() = outtakeSpeed;
}

void outtakeHold() {
    outtaking = false;
    hold();
}

void hold() {
    if (!(intaking || outtaking)) {
        Devices::get<motors::Intake>() = 0;
    }
}