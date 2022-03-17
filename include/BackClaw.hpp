#pragma once
#include "main.h"

#include "Devices.hpp"

class BackClaw {
    public:
    bool state;
    bool upVal;
    bool tilterState;
    bool tilterInVal;


    BackClaw(bool clampInit, bool clampUp, bool tilterInit, bool tilterIn);
    void up();
    void down();
    void toggle();
    void tilterIn();
    void tilterOut();
    void toggleTilter();
};