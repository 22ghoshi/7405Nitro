#include "PID.hpp"

PID::PID(double kP, double kI, double kD, double minSpeed, double maxSpeed, double maxChange) {
    this->kP = kP;
    this->kI = kI;
    this->kD = kD;
    this->minSpeed = minSpeed;
    this->maxSpeed = maxSpeed;
    this->maxChange = maxChange;

    P = 0;
    I = 0;
    D = 0;
    prevErr = 0;
    prevSpeed = 0;

    reset = true;
}

double PID::getPID(double err) {
    if (reset) {
        prevErr = err;
        I = 0;
    }

    P = err;
    I += err;
    D = err - prevErr;
    double speed = (kP * P) + (kI * I) + (kD * D);

    if (fabs(speed) > maxSpeed) {
        speed = speed > 0 ? maxSpeed : -maxSpeed;
    }
    if (fabs(speed) < minSpeed) {
        speed = speed > 0 ? minSpeed : -minSpeed;
    }

    double change = speed - prevSpeed;
    if (fabs(change) > maxChange) {
        speed = change > 0 ? prevSpeed + maxChange : prevSpeed - maxChange;
    }

    prevErr = err;
    prevSpeed = speed;
    reset = false;

    return speed;
}