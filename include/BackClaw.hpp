#pragma once
#include "main.h"

#include "Devices.hpp"

class BackClaw {
    public:
    bool state;
    bool up;
    bool tilterState;
    bool tilterIn;


    BackClaw(bool tilterInit, bool tilterIn, bool clampInit, bool clampUp);
    void up();
    void down();
    void toggle();
    void tilterIn();
    void tilterOut();
    void toggleTilter();
};