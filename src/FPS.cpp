#include "FPS.hpp"

Point FPS::currentPos{Point()};
double FPS::leftVel = 0;
double FPS::rightVel = 0;

FPS::FPS() {}

void FPS::run(void* params) {
    // Device::get<sensor::LeftRotation>()->reset_position();
    // Device::get<sensor::LeftRotation>()->reverse();
    // Device::get<sensor::RightRotation>()->reset_position();
    // Device::get<sensor::RightRotation>()->reverse();
    Device::get<motorGroup::Drive>()->resetEncoders();
    double prevLE, prevRE = 0;

    double prevLeftVel, prevRightVel = 0;

    while (true) {
        if (pros::Task::notify_take(true, 20)) {
            Device::get<sensor::Inertial>()->tare_rotation();
            // Device::get<sensor::LeftRotation>()->reset_position();
            // Device::get<sensor::RightRotation>()->reset_position();
            Device::get<motorGroup::Drive>()->resetEncoders();
            currentPos = Point();
            pros::delay(20);
        }

        currentPos.h = Device::get<sensor::Inertial>()->get_heading();
        currentPos.h = currentPos.h < 180 ? currentPos.h : currentPos.h - 360;

        double currLE = Device::get<motorGroup::LeftDrive>()->getEncoders(); //Device::get<sensor::LeftRotation>()->get_position();
        double currRE = Device::get<motorGroup::RightDrive>()->getEncoders(); //Device::get<sensor::RightRotation>()->get_position();
        double deltaLE = currLE - prevLE;
        double deltaRE = currRE - prevRE;
        double verticalMovement = (deltaLE + deltaRE) / 2.0;

        Point delta;
        delta.x = (verticalMovement * sin(toRadians(currentPos.h)));
        delta.y = (verticalMovement * cos(toRadians(currentPos.h)));
        currentPos += delta;

        prevLE = currLE;
        prevRE = currRE;

        leftVel = ((deltaLE / 100.0f / 360.0f) * (M_PI * DEADWHEEL_DIAMETER)) / (20.0f / 1000.0f);
        rightVel = ((deltaRE / 100.0f / 360.0f) * (M_PI * DEADWHEEL_DIAMETER)) / (20.0f / 1000.0f);
        double leftAccel = (leftVel - prevLeftVel) / (20.0f / 1000.0f);
        double rightAccel = (rightVel - prevRightVel) / (20.0f / 1000.0f);
        prevLeftVel = leftVel;
        prevRightVel = rightVel;

        // printf("time: %d, vels: (%f, %f), accels: (%f, %f)\n", pros::millis(), leftVel, rightVel, leftAccel, rightAccel);
    }
}

double FPS::toRadians(double degrees) {
    return (degrees * (M_PI / 180.0));
}

double FPS::toDegrees(double radians) {
    return (radians * (180.0 / M_PI));
}