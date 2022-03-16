#include "FrontClaw.cpp"

FrontClaw::FrontClaw(bool initState, bool up) {
    this->state = initState;
    this->up = up;
}

void FrontClaw::up() {
    if (state == !up) {
        state = up;
    }
    Devices::get<pistons::FrontClaw>().set_value(up);
}

void FrontClaw::down() {
    if (state == up) {
        state = !up;
    }
    Devices::get<pistons::FrontClaw>().set_value(state);
}

void FrontClaw::toggle() {
    state = !state;
    Devices::get<pistons::FrontClaw>().set_value(state);
}

double FrontClaw::waitForGoal(double distanceLimit, double timeLimit) {
    up();
    int startTime = pros::millis();
    int currentTime = 0;
    while ((Devices::get<sensors::FrontDistance>().get() > distanceLimit || Devices::get<sensors::FrontDistance>().get() == 0) && currentTime < timeLimit) {
        currentTime = pros::millis() - startTime;
        pros::delay(2);
    }
    down();
}

double FrontClaw::waitForGoal(double distanceLimit, double yLimit, double timeLimit) {
    up();
    int startTime = pros::millis();
    int currentTime = 0;
    while ((Devices::get<sensors::FrontDistance>().get() > distanceLimit || Devices::get<sensors::FrontDistance>().get() == 0) && FPS::currentPos.y < yLimit && currentTime < timeLimit) {
        currentTime = pros::millis() - startTime;
        pros::delay(2);
    }
    down();
}

double FrontClaw::hasGoal(double hasDistance) {
    return (Devices::get<sensors::FrontDistance>().get() < goalDistance && Devices::get<sensors::FrontDistance>().get() != 0)
}