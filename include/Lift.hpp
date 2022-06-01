#pragma once
#include "main.h"

#include "Devices.hpp"
#include "PID.hpp"

class Lift {
    private:
    static PID liftPID;
    static bool up;
    static bool down;
    static double lowerBound, upperBound;
    static int delay, delayn;
    static double holdVal;

    public:
    Lift();
    static void moveUp();
    static void moveDown();
    static void upHold();
    static void downHold();
    static void hold();
    static void move(void* params);
    static void autonTarget(double target);
};