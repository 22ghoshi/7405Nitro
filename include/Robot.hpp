#pragma once
#include "main.h"

#include "Thread.hpp"
#include "Drive.hpp"
#include "Lift.hpp"
#include "Intake.hpp"
#include "FrontClaw.hpp"
#include "BackClaw.hpp"
#include "PID.hpp"

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
    static bool odomMove;

    static int driveSpeed;
    
    Robot();
    static void move(void* params);
    static void moveTo(double x, double y, std::initializer_list<double> newmPID = {0.25, 0.01, 0.3}, double newmacc = 40.0, std::initializer_list<double> newtPID = {4.0, 0.02, 1.5}, double newtacc = 10.0);
    static void moveToNow(double x, double y, std::initializer_list<double> newmPID = {0.2, 0.01, 0.35}, double newmacc = 40.0, std::initializer_list<double> newtPID = {4.0, 0.02, 1.5}, double newtacc = 10.0);
    static void turnTo(double x, double y, std::initializer_list<double> newtPID = {1.5, 0.2, 1.0}, double newtacc = 1.0);
    static void turnToNow(double x, double y, std::initializer_list<double> newtPID = {1.5, 0.2, 1.0}, double newtacc = 1.0);
    static void turnTo(double deg, std::initializer_list<double> newtPID = {1.5, 0.2, 1.0}, double newtacc = 1.0);
    static void turnToNow(double deg, std::initializer_list<double> newtPID = {1.5, 0.2, 1.0}, double newtacc = 1.0);
    static void turnBackTo(double x, double y, std::initializer_list<double> newtPID = {1.5, 0.2, 1.0}, double newtacc = 1.0);
    static void turnBackToNow(double x, double y, std::initializer_list<double> newtPID = {1.5, 0.2, 1.0}, double newtacc = 1.0);
    static void setSpeed(double speed, std::initializer_list<double> newtPID = {4.0, 0.02, 1.5});
    static void waitUntilStop();

    static void brainDisplay(void* params);
    static void controllerDisplay(void* params);
};