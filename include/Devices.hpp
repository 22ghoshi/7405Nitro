#pragma once
#include "main.h"

#include "Groups.hpp"

#include <map>
#include <memory>
#include <string>
#include <stdexcept>

enum class motorGearset { GS100, GS200, GS600 };

enum class motors { BackLeft, BackRight, MidLeft, MidRight, FrontLeft, FrontRight, Intake, Lift };
enum class motorGroups { LeftDrive, RightDrive, Drive };
enum class pistons { BackClaw, Tilter, FrontClaw };
enum class sensors { Inertial, LeftEncoder, RightEncoder, FrontDistance, LiftPotentiometer };

enum class controllers { Master };

namespace Devices {
    //defaults to 200rpm/unreversed
    pros::Motor* getMotor(std::string name, int port, motorGearset gearset = motorGearset::GS200, bool reversed = false);

    //defaults to start false
    pros::ADIDigitalOut* getPiston(std::string name, int port, bool start = false);
    
    pros::ADIButton* getButton(std::string name, int port);
    pros::ADILineSensor* getLine(std::string name, int port);
    pros::ADIPotentiometer* getPotentiometer(std::string name, int port);
    pros::ADIUltrasonic* getUltrasonic(std::string name, int port);

    //defaults to unreversed
    pros::ADIEncoder* getEncoder(std::string name, int port, bool reversed = false);
    
    pros::Rotation* getRotation(std::string name, int port);
    pros::IMU* getInertial(std::string name, int port);
    pros::Vision* getVision(std::string name, int port);
    pros::Distance* getDistance(std::string name, int port);

    pros::Controller* getController(std::string name);

    template <motors motor>
    auto get();

    template<> inline
    auto get<motors::BackLeft>() {
        return *(Devices::getMotor("Back Left", 10, motorGearset::GS200));
    }

    template<> inline
    auto get<motors::BackRight>() {
        return *(Devices::getMotor("Back Right", 13, motorGearset::GS200));
    }

    template<> inline
    auto get<motors::MidLeft>() {
        return *(Devices::getMotor("Mid Left", 6, motorGearset::GS200, true));
    }

    template<> inline
    auto get<motors::MidRight>() {
        return *(Devices::getMotor("Mid Right", 3, motorGearset::GS200));
    }

    template<> inline
    auto get<motors::FrontLeft>() {
        return *(Devices::getMotor("Front Left", 9, motorGearset::GS200));
    }

    template<> inline
    auto get<motors::FrontRight>() {
        return *(Devices::getMotor("Front Right", 2, motorGearset::GS200, true));
    }

    template<> inline
    auto get<motors::Intake>() {
        return *(Devices::getMotor("Intake", 14, motorGearset::GS200, true));
    }

    template<> inline
    auto get<motors::Lift>() {
        return *(Devices::getMotor("Lift", 12, motorGearset::GS100, true));
    }

    template <motorGroups motorGroup>
    auto get();

    template<> inline
    auto get<motorGroups::LeftDrive>() {
        return MotorGroup({get<motors::BackLeft>, get<motors::MidLeft>, get<motors::FrontLeft>});
    }

    template<> inline
    auto get<motorGroups::RightDrive>() {
        return MotorGroup({get<motors::BackRight>, get<motors::MidRight>, get<motors::FrontRight>});
    }

    template<> inline
    auto get<motorGroups::Drive>() {
        return MotorGroup({get<motors::BackLeft>, get<motors::BackRight>, get<motors::MidLeft>, get<motors::MidRight>, get<motors::FrontLeft>, get<motors::FrontRight>});
    }

    template <pistons piston>
    auto get();

    template<> inline
    auto get<pistons::BackClaw>() {
        return *(Devices::getPiston("Back Clamp", 1, true));
    }

    template<> inline
    auto get<pistons::Tilter>() {
        return *(Devices::getPiston("Tilter", 3, true));
    }

    template<> inline
    auto get<pistons::FrontClaw>() {
        return *(Devices::getPiston("Front Clamp", 8, true));
    }

    template <sensors sensor>
    auto get();

    template<> inline
    auto get<sensors::Inertial>() {
        return *(Devices::getInertial("Inertial", 21));
    }

    // template<> inline
    // auto get<sensors::LeftEncoder>() {
    //     return *(Devices::getEncoder("Left", 7));
    // }

    // template<> inline
    // auto get<sensors::RightEncoder>() {
    //     return *(Devices::getEncoder("Right", 5));
    // }

    template<> inline
    auto get<sensors::LiftPotentiometer>() {
        return *(Devices::getPotentiometer("Lift", 2));
    }

    // template<> inline
    // auto get<sensors::BackDistance>() {
    //     return *(Devices::getDistance("Back", 9));
    // }

    template<> inline
    auto get<sensors::FrontDistance>() {
        return *(Devices::getDistance("Front", 5));
    }

    template<controllers controller>
    auto get();

    template<> inline
    auto get<controllers::Master>() {
        return *(Devices::getController("Master"));
    }
};