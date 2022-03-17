#include "Intake.hpp"

Intake::Intake(double intakeSpeed, double outtakeSpeed) {
    intaking = false;
    outtaking = false;
    this->intakeSpeed = intakeSpeed;
    this->outtakeSpeed = outtakeSpeed;
}

void Intake::intake() {
    if (outtaking) {
        outtaking = false;
    }
    intaking = true;
    Devices::get<motors::Intake>() = intakeSpeed;
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
    Devices::get<motors::Intake>() = outtakeSpeed;
}

void Intake::outtakeHold() {
    outtaking = false;
    hold();
}

void Intake::hold() {
    if (!(intaking || outtaking)) {
        Devices::get<motors::Intake>() = 0;
    }
}