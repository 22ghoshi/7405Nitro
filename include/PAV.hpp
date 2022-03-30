#pragma once
#include "main.h"

class PAV {
    private:
    double P, A, V;
    double prevVel;
    double maxChange, prevSpeed;

    public:
    double kP, kA, kV;
    PAV();
    PAV(double kP, double kA, double kV, double maxChange = 256);
    double getPAV(double targetVel, double currVel);
};