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