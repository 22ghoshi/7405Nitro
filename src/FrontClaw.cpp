#include "FrontClaw.hpp"

bool FrontClaw::upVal;
bool FrontClaw::state;

FrontClaw::FrontClaw(bool initState, bool up) {
    state = initState;
    upVal = up;
}

void FrontClaw::up() {
    if (state == !upVal) {
        state = upVal;
    }
    Devices::get<pistons::FrontClaw>().set_value(state);
}

void FrontClaw::down() {
    if (state == upVal) {
        state = !upVal;
    }
    Devices::get<pistons::FrontClaw>().set_value(state);
}

void FrontClaw::toggle() {
    state = !state;
    Devices::get<pistons::FrontClaw>().set_value(state);
}

void FrontClaw::waitForGoal(double distanceLimit, double timeLimit) {
    up();
    int startTime = pros::millis();
    int currentTime = 0;
    while ((Devices::get<sensors::FrontDistance>().get() > distanceLimit || Devices::get<sensors::FrontDistance>().get() == 0) && currentTime < timeLimit) {
        currentTime = pros::millis() - startTime;
        pros::delay(2);
    }
    down();
}

void FrontClaw::waitForGoal(double distanceLimit, double yLimit, double timeLimit) {
    up();
    int startTime = pros::millis();
    int currentTime = 0;
    while ((Devices::get<sensors::FrontDistance>().get() > distanceLimit || Devices::get<sensors::FrontDistance>().get() == 0) && FPS::currentPos.y < yLimit && currentTime < timeLimit) {
        currentTime = pros::millis() - startTime;
        pros::delay(2);
    }
    down();
}

bool FrontClaw::hasGoal(double goalDistance) {
    return (Devices::get<sensors::FrontDistance>().get() < goalDistance && Devices::get<sensors::FrontDistance>().get() != 0);
}