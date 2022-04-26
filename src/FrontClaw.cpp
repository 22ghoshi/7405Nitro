#include "FrontClaw.hpp"

bool FrontClaw::upVal(false);
bool FrontClaw::state(true);

FrontClaw::FrontClaw() {}

void FrontClaw::up() {
    if (state == !upVal) {
        state = upVal;
    }
    Device::get<piston::FrontClaw>().set_value(state);
}

void FrontClaw::down() {
    if (state == upVal) {
        state = !upVal;
    }
    Device::get<piston::FrontClaw>().set_value(state);
}

void FrontClaw::toggle() {
    state = !state;
    Device::get<piston::FrontClaw>().set_value(state);
}

void FrontClaw::waitForGoal(double distanceLimit, double timeLimit) {
    up();
    int startTime = pros::millis();
    int currentTime = 0;
    while ((Device::get<sensor::FrontDistance>().get() > distanceLimit || Device::get<sensor::FrontDistance>().get() == 0) && currentTime < timeLimit) {
        currentTime = pros::millis() - startTime;
        pros::delay(2);
    }
    down();
}

void FrontClaw::waitForGoal(double distanceLimit, double yLimit, double timeLimit) {
    up();
    int startTime = pros::millis();
    int currentTime = 0;
    while ((Device::get<sensor::FrontDistance>().get() > distanceLimit || Device::get<sensor::FrontDistance>().get() == 0) && FPS::currentPos.y < yLimit && currentTime < timeLimit) {
        currentTime = pros::millis() - startTime;
        pros::delay(2);
    }
    down();
}

bool FrontClaw::hasGoal(double goalDistance) {
    return (Device::get<sensor::FrontDistance>().get() < goalDistance && Device::get<sensor::FrontDistance>().get() != 0);
}