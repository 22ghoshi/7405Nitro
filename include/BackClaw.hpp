#pragma once
#include "main.h"

#include "Devices.hpp"

class BackClaw {
    public:
    static bool state;
    static bool upVal;
    static bool tilterState;
    static bool tilterInVal;


    BackClaw();
    static void up();
    static void down();
    static void toggle();
    static void tilterIn();
    static void tilterOut();
    static void toggleTilter();
};