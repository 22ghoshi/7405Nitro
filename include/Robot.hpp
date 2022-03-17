#pragma once
#include "main.h"

#include "Drive.hpp"
#include "Lift.hpp"
#include "Intake.hpp"
#include "FrontClaw.hpp"
#include "BackClaw.hpp"
#include "PID.hpp"

using namespace pros;

class Robot {
    public:
    static BackClaw backClaw;
    static Drive drive;
    static FPS fps;
    static FrontClaw frontClaw;
    static Intake intake;
    static Lift lift;
    
    Robot();
};