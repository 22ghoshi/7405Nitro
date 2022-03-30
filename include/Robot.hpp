#pragma once
#include "main.h"

#include "Drive.hpp"
#include "Lift.hpp"
#include "Intake.hpp"
#include "FrontClaw.hpp"
#include "BackClaw.hpp"
#include "PID.hpp"
#include "Pursuit.hpp"

#include <queue>

class Robot {
    public:
    static BackClaw backClaw;
    static Drive drive;
    static FrontClaw frontClaw;
    static Intake intake;
    static Lift lift;

    static Point targetPos;
    static PID mPID;
    static PID tPID;
    static double moveErr, turnErr;
    static double macc, tacc;
    static bool turning;
    static bool turningDeg;
    static bool turningBack;
    static int moven;
    
    Robot();
    static void move(void* params);
    static void moveTo(double x, double y, std::initializer_list<double> newmPID, double newmacc, std::initializer_list<double> newtPID, double newtacc);
    static void moveToNow(double x, double y, std::initializer_list<double> newmPID, double newmacc, std::initializer_list<double> newtPID, double newtacc);
    static void turnTo(double x, double y, std::initializer_list<double> newtPID, double newtacc);
    static void turnToNow(double x, double y, std::initializer_list<double> newtPID, double newtacc);
    static void turnTo(double deg, std::initializer_list<double> newtPID, double newtacc);
    static void turnToNow(double deg, std::initializer_list<double> newtPID, double newtacc);
    static void turnBackTo(double x, double y, std::initializer_list<double> newtPID, double newtacc);
    static void turnBackToNow(double x, double y, std::initializer_list<double> newtPID, double newtacc);
    static void waitUntilStop();

    static void brainDisplay(void* params);
    static void controllerDisplay(void* params);
};