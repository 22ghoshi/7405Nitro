#pragma once
#include "main.h"

#include "Groups.hpp"

#include <map>
#include <memory>
#include <string>
#include <stdexcept>

enum class motorGearset { GS100, GS200, GS600 };

enum class motor { BackLeft, BackRight, MidLeft, MidRight, FrontLeft, FrontRight, Intake, Lift };
enum class motorGroup { LeftDrive, RightDrive, Drive };
enum class piston { BackClaw, Tilter, FrontClaw };
enum class sensor { Inertial, LeftRotation, RightRotation, FrontDistance, BackDistance, LiftPotentiometer };

enum class controller { Master };

namespace Device {
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

    template <motor motor>
    auto get();

    template<> inline
    auto get<motor::BackLeft>() {
        return *(Device::getMotor("Back Left", 9, motorGearset::GS600, true));
    }

    template<> inline
    auto get<motor::BackRight>() {
        return *(Device::getMotor("Back Right", 7, motorGearset::GS600));
    }

    template<> inline
    auto get<motor::MidLeft>() {
        return *(Device::getMotor("Mid Left", 10, motorGearset::GS600, true));
    }

    template<> inline
    auto get<motor::MidRight>() {
        return *(Device::getMotor("Mid Right", 6, motorGearset::GS600));
    }

    template<> inline
    auto get<motor::FrontLeft>() {
        return *(Device::getMotor("Front Left", 8, motorGearset::GS600));
    }

    template<> inline
    auto get<motor::FrontRight>() {
        return *(Device::getMotor("Front Right", 20, motorGearset::GS600, true));
    }

    template<> inline
    auto get<motor::Intake>() {
        return *(Device::getMotor("Intake", 11, motorGearset::GS200, true));
    }

    template<> inline
    auto get<motor::Lift>() {
        return *(Device::getMotor("Lift", 5, motorGearset::GS100));
    }

    template <motorGroup motorGroup>
    auto get();

    template<> inline
    auto get<motorGroup::LeftDrive>() {
        return MotorGroup({get<motor::BackLeft>, get<motor::MidLeft>, get<motor::FrontLeft>});
    }

    template<> inline
    auto get<motorGroup::RightDrive>() {
        return MotorGroup({get<motor::BackRight>, get<motor::MidRight>, get<motor::FrontRight>});
    }

    template<> inline
    auto get<motorGroup::Drive>() {
        return MotorGroup({get<motor::BackLeft>, get<motor::BackRight>, get<motor::MidLeft>, 
                           get<motor::MidRight>, get<motor::FrontLeft>, get<motor::FrontRight>});
    }

    template <piston piston>
    auto get();

    template<> inline
    auto get<piston::BackClaw>() {
        return *(Device::getPiston("Back Clamp", 4, true));
    }

    template<> inline
    auto get<piston::Tilter>() {
        return *(Device::getPiston("Tilter", 2, true));
    }

    template<> inline
    auto get<piston::FrontClaw>() {
        return *(Device::getPiston("Front Clamp", 1, true));
    }

    template <sensor sensor>
    auto get();

    template<> inline
    auto get<sensor::Inertial>() {
        return *(Device::getInertial("Inertial", 3));
    }

    template<> inline
    auto get<sensor::LeftRotation>() {
        return *(Device::getRotation("Left", 4));
    }

    template<> inline
    auto get<sensor::RightRotation>() {
        return *(Device::getRotation("Right", 21));
    }
    

    template<> inline
    auto get<sensor::LiftPotentiometer>() {
        return *(Device::getPotentiometer("Lift", 8));
    }

    template<> inline
    auto get<sensor::BackDistance>() {
        return *(Device::getDistance("Back", 17));
    }

    template<> inline
    auto get<sensor::FrontDistance>() {
        return *(Device::getDistance("Front", 13));
    }

    template<controller controller>
    auto get();

    template<> inline
    auto get<controller::Master>() {
        return *(Device::getController("Master"));
    }
};