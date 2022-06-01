#pragma once
#include "main.h"

#include "Devices.hpp"
#include "FPS.hpp"

class Drive {
    public:
    static bool driveHold;

    Drive();

    static void arcade(double power, double turn);
    static void tank(double left, double right);
    static void mecanum(double power, double strafe, double turn);
    static void stop(brakeType brake = brakeType::hold);
    static int dampen(int input);
    static void drive(int deadzone = 0);
    static void toggleHold();
};