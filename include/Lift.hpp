#pragma once
#include "main.h"

#include "Devices.hpp"
#include "PID.hpp"

class Lift {
    private:
    PID liftPID;
    bool up;
    bool down;
    int delay, delayn;
    double holdVal;

    public:
    Lift(double kP, double kI, double kD, int delay);
    void moveUp();
    void moveDown();
    void upHold();
    void downHold();
    void hold();
};