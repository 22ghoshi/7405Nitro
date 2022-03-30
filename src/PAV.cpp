#include "PAV.hpp"

PAV::PAV() {}

PAV::PAV(double kP, double kA, double kV, double maxChange) {
    this->kP = kP;
    this->kA = kA;
    this->kV = kV;
    this->maxChange = maxChange;

    P = 0;
    A = 0;
    V = 0;
    prevVel = 0;
    prevSpeed = 0;
}

double PAV::getPAV(double targetVel, double currVel) {
    P = targetVel - currVel;
    A = targetVel - prevVel;
    V = targetVel;
    double speed = (kP * P) + (kA * A) + (kV * V);

    double change = speed - prevSpeed;
    if (fabs(change) > maxChange) {
        speed = change > 0 ? prevSpeed + maxChange : prevSpeed - maxChange;
    }

    prevVel = targetVel;

    return speed;
}