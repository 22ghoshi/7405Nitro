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
    Device::get<motor::Intake>() = intakeSpeed;
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
    Device::get<motor::Intake>() = outtakeSpeed;
}

void Intake::outtakeHold() {
    outtaking = false;
    hold();
}

void Intake::hold() {
    if (!(intaking || outtaking)) {
        Device::get<motor::Intake>() = 0;
    }
}