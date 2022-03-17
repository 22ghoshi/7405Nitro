#pragma once
#include "main.h"

#include "Devices.hpp"

class Intake {
    private:
    bool intaking, outtaking;
    double intakeSpeed, outtakeSpeed;

    public:
    Intake(double intakeSpeed = 127, double outtakeSpeed = -127);
    void intake();
    void intakeHold();
    void outtake();
    void outtakeHold();
    void hold();
};