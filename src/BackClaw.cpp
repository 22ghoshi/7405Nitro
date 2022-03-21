#include "BackClaw.hpp"

bool BackClaw::state;
bool BackClaw::upVal;
bool BackClaw::tilterState;
bool BackClaw::tilterInVal;

BackClaw::BackClaw(bool clampInit, bool clampUp, bool tilterInit, bool tilterIn) {
    state = clampInit;
    upVal = clampUp;
    tilterState = tilterInit;
    tilterInVal = tilterIn;    
}

void BackClaw::up() {
    if (state == !upVal && tilterState == !tilterInVal) {
        state = upVal;
    }
    Devices::get<pistons::BackClaw>().set_value(state);
}

void BackClaw::down() {
    if (state == upVal) {
        state = !upVal;
    }
    Devices::get<pistons::BackClaw>().set_value(state);
}

void BackClaw::toggle() {
    state = !state;
    Devices::get<pistons::BackClaw>().set_value(state);
}

void BackClaw::tilterIn() {
    if (tilterState == !tilterInVal) {
        tilterState = tilterInVal;
    }
    Devices::get<pistons::Tilter>().set_value(tilterState);
}

void BackClaw::tilterOut() {
    if (tilterState == tilterInVal) {
        tilterState == !tilterInVal;
    }
    Devices::get<pistons::Tilter>().set_value(tilterState);
}

void BackClaw::toggleTilter() {
    tilterState = !tilterState;
    Devices::get<pistons::Tilter>().set_value(tilterState);
}