#pragma once
#include "main.h"

#include "Devices.hpp"

class Intake {
    private:
    static double intakeSpeed, outtakeSpeed;

    public:
    static bool intaking, outtaking;

    Intake(double intake = 127, double outtake = -127);
    static void intake();
    static void intakeHold();
    static void outtake();
    static void outtakeHold();
    static void toggle();
    static void hold();
};