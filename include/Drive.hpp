#pragma once
#include "main.h"

#include "Devices.hpp"

class Drive {
    public:
    Drive();
    void arcade(double power, double turn);
    void tank(double left, double right);
    void mecanum(double power, double strafe, double turn);
    void stop(brakeType brake = brakeType::hold);
    int dampen(int input);
    void drive(int deadzone = 3);
};