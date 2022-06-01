#pragma once
#include "main.h"

#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <list>

enum class brakeType { coast, brake, hold };

class MotorGroup {
    private:
    std::list<pros::Motor*> group;

    public:
    MotorGroup();
    MotorGroup(std::list<pros::Motor*> motorGroupMotors);
    void operator=(std::int32_t voltage);
    void move(std::int32_t voltage);
    void moveVelocity(std::int32_t velocity);
    double getEncoders();
    void resetEncoders();
    double getAverageVelocity();
    void stop(brakeType brake = brakeType::coast);
    void setBrakeMode(brakeType brake);
};