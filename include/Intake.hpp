#pragma once
#include "main.h"

#include "Devices.hpp"

class Intake {
    private:
    static bool intaking, outtaking;
    static double intakeSpeed, outtakeSpeed;

    public:
    Intake(double intake = 127, double outtake = -127);
    static void intake();
    static void intakeHold();
    static void outtake();
    static void outtakeHold();
    static void hold();
};