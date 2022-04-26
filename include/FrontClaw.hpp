#pragma once
#include "main.h"

#include "Devices.hpp"
#include "FPS.hpp"

class FrontClaw {
    public:
    static bool upVal;
    static bool state;

    FrontClaw();
    static void up();
    static void down();
    static void toggle();

    static void waitForGoal(double distanceLimit, double timeLimit);
    static void waitForGoal(double distanceLimit, double yLimit, double timeLimit);
    static bool hasGoal(double goalDistance);
};