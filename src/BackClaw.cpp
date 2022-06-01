#include "BackClaw.hpp"

bool BackClaw::state(true);
bool BackClaw::upVal(true);
bool BackClaw::tilterState(false);
bool BackClaw::tilterInVal(false);

BackClaw::BackClaw() {}

void BackClaw::up() {
    if (state == !upVal && tilterState == !tilterInVal) {
        state = upVal;
    }
    Device::get<piston::BackClaw>()->set_value(state);
}

void BackClaw::down() {
    if (state == upVal) {
        state = !upVal;
    }
    Device::get<piston::BackClaw>()->set_value(state);
}

void BackClaw::toggle() {
    state = !state;
    Device::get<piston::BackClaw>()->set_value(state);
}

void BackClaw::tilterIn() {
    if (tilterState == !tilterInVal) {
        tilterState = tilterInVal;
    }
    Device::get<piston::Tilter>()->set_value(tilterState);
}

void BackClaw::tilterOut() {
    if (tilterState == tilterInVal) {
        tilterState == !tilterInVal;
    }
    Device::get<piston::Tilter>()->set_value(tilterState);
}

void BackClaw::toggleTilter() {
    tilterState = !tilterState;
    Device::get<piston::Tilter>()->set_value(tilterState);
}