#pragma once
#include "main.h"

class PID {
    public:
    double kP, kI, kD;
    double P, I, D;
    double prevErr;
    double maxSpeed, minSpeed;
    double maxChange, prevSpeed;
    int n;
    
    PID(double kP, double kI, double kD, double minSpeed = 0, double maxSpeed = 128, double maxChange = 256);
    double getPID(double err);
};