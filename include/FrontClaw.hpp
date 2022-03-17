#pragma once
#include "main.h"

#include "Devices.hpp"
#include "FPS.hpp"

class FrontClaw {
    public:
    bool upVal;
    bool state;

    FrontClaw(bool initState, bool up);
    void up();
    void down();
    void toggle();

    void waitForGoal(double distanceLimit, double timeLimit);
    void waitForGoal(double distanceLimit, double yLimit, double timeLimit);
    bool hasGoal(double goalDistance);
};