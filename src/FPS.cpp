#include "FPS.hpp"

Point FPS::currentPos{Point()};
double FPS::leftVel = 0;
double FPS::rightVel = 0;

FPS::FPS() {}

void FPS::run(void* params) {
    Devices::get<sensors::LeftRotation>().reset_position();
    Devices::get<sensors::LeftRotation>().reverse();
    Devices::get<sensors::RightRotation>().reset_position();
    Devices::get<sensors::RightRotation>().reverse();
    double prevLE, prevRE = 0;

    double prevLeftVel, prevRightVel = 0;

    while (true) {
        if (pros::Task::notify_take(true, 20)) {
            Devices::get<sensors::Inertial>().tare_rotation();
            Devices::get<sensors::LeftRotation>().reset_position();
            Devices::get<sensors::RightRotation>().reset_position();
            currentPos = Point();
            pros::delay(20);
        }

        currentPos.h = Devices::get<sensors::Inertial>().get_heading();
        currentPos.h = currentPos.h < 180 ? currentPos.h : currentPos.h - 360;

        double currLE = Devices::get<sensors::LeftRotation>().get_position();
        double currRE = Devices::get<sensors::RightRotation>().get_position();
        double deltaLE = currLE - prevLE;
        double deltaRE = currRE - prevRE;
        double verticalMovement = (((deltaLE + deltaRE) / 2.0) / 100.0 / 360.0) * (M_PI * DEADWHEEL_DIAMETER);

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