#include "BackClaw.hpp"

BackClaw::BackClaw(bool tilterInit, bool tilterIn, bool clampInit, bool clampUp) {
    this->state = clampInit;
    this->up = clampUp;
    this->tilterState = tilterInit;
    this->tilterIn = tilterIn;    
}

void BackClaw::up() {
    if (state == !up && tilterState == !tilterIn) {
        state = up;
    }
    Devices::get<pistons::BackClaw>().set_value(state);
}

void BackClaw::down() {
    if (state == up) {
        state = !up;
    }
    Devices::get<pistons::BackClaw>().set_value(state);
}

void BackClaw::toggle() {
    state = !state;
    Devices::get<pistons::BackClaw>().set_value(state);
}

void BackClaw::tilterIn() {
    if (tilterState == !tilterIn) {
        tilterState = tilterIn;
    }
    Devices::get<pistons::Tilter>().set_value(tilterState);
}

void BackClaw::tilterOut() {
    if (tilterState == tilterIn) {
        tilterState == !tilterIn;
    }
    Devices::get<pistons::Tilter>().set_value(tilterState);
}

void BackClaw::toggleTilter() {
    tilterState = !tilterState;
    Devices::get<pistons::Tilter>().set_value(tilterState);
}