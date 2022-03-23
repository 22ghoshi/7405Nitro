#include "FPS.hpp"

Point FPS::currentPos{Point()};

FPS::FPS() {}

void FPS::run(void* params) {
    Devices::get<sensors::LeftEncoder>().reset();
    Devices::get<sensors::RightEncoder>().reset();

    while (true) {
        if (pros::Task::notify_take(true, 20)) {
            Devices::get<sensors::Inertial>().tare_rotation();
            Devices::get<sensors::LeftEncoder>().reset();
            Devices::get<sensors::RightEncoder>().reset();
            currentPos = Point();
            pros::delay(20);
        }

        currentPos.h = Devices::get<sensors::Inertial>().get_heading();
        currentPos.h = currentPos.h < 180 ? currentPos.h : currentPos.h - 360;
        double verticalMovement = ((Devices::get<sensors::LeftEncoder>().get_value() + Devices::get<sensors::RightEncoder>().get_value()) / 2.0);

        Point deltaPoint;
        deltaPoint.x = (verticalMovement * sin(toRadians(currentPos.h)));
        deltaPoint.y = (verticalMovement * cos(toRadians(currentPos.h)));
        currentPos += deltaPoint;

        Devices::get<sensors::LeftEncoder>().reset();
        Devices::get<sensors::RightEncoder>().reset();
    }
}

double FPS::toRadians(double degrees) {
    return (degrees * (M_PI / 180.0));
}

double FPS::toDegrees(double radians) {
    return (radians * (180.0 / M_PI));
}