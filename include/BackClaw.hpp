#pragma once
#include "main.h"

#include "Devices.hpp"

class BackClaw {
    public:
    bool state;
    bool upVal;
    bool tilterState;
    bool tilterInVal;


    BackClaw(bool tilterInit, bool tilterIn, bool clampInit, bool clampUp);
    void up();
    void down();
    void toggle();
    void tilterIn();
    void tilterOut();
    void toggleTilter();
};