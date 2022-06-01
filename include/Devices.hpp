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
enum class sensor { Inertial, /*LeftRotation, RightRotation,*/ FrontDistance, /*BackDistance,*/ LiftPotentiometer };

enum class controller { Master };

namespace Device {
    void initAll();

    void initMotor(motor motorName, std::uint8_t port, motorGearset gearset = motorGearset::GS200, bool reversed = false);
    pros::Motor* getMotor(motor motorName);

    void initMotorGroup(motorGroup motorGroupName, std::vector<motor> groupMotors);
    MotorGroup* getMotorGroup(motorGroup motorGroupName);

    void initPiston(piston pistonName, std::uint8_t port, bool initState = false);
    void initPiston(piston pistonName, std::uint8_t smartPort, std::uint8_t ADIPort, bool initState = false);
    pros::ADIDigitalOut* getPiston(piston pistonName);
    
    void initButton(sensor buttonName, std::uint8_t port);
    void initButton(sensor buttonName, std::uint8_t smartPort, std::uint8_t ADIPort);
    pros::ADIButton* getButton(sensor buttonName);

    void initLine(sensor lineName, std::uint8_t port);
    void initLine(sensor lineName, std::uint8_t smartPort, std::uint8_t ADIPort);
    pros::ADILineSensor* getLine(sensor lineName);

    void initPotentiometer(sensor potName, std::uint8_t port);
    void initPotentiometer(sensor potName, std::uint8_t smartPort, std::uint8_t ADIPort);
    pros::ADIPotentiometer* getPotentiometer(sensor potName);

    void initUltrasonic(sensor ultName, std::uint8_t port);
    void initUltrasonic(sensor ultName, std::uint8_t smartPort, std::uint8_t ADIPort);
    pros::ADIUltrasonic* getUltrasonic(sensor ultName);

    void initEncoder(sensor encName, std::uint8_t port, bool reverse = false);
    void initEncoder(sensor encName, std::uint8_t smartPort, std::uint8_t ADIPort, bool reverse = false);
    pros::ADIEncoder* getEncoder(sensor encName);
    
    void initRotation(sensor rotName, std::uint8_t port);
    pros::Rotation* getRotation(sensor rotName);

    void initInertial(sensor IMUName, std::uint8_t port);
    pros::IMU* getInertial(sensor IMUName);

    void initVision(sensor visionName, std::uint8_t port);
    pros::Vision* getVision(sensor visionName);

    void initDistance(sensor distanceName, std::uint8_t port);
    pros::Distance* getDistance(sensor distanceName);

    void initController(controller ctrlName);
    pros::Controller* getController(controller ctrlName);

    template <motor motor>
    auto get();

    template<> inline
    auto get<motor::BackLeft>() {
        return Device::getMotor(motor::BackLeft);
    }

    template<> inline
    auto get<motor::BackRight>() {
        return Device::getMotor(motor::BackRight);
    }

    template<> inline
    auto get<motor::MidLeft>() {
        return Device::getMotor(motor::MidLeft);
    }

    template<> inline
    auto get<motor::MidRight>() {
        return Device::getMotor(motor::MidRight);
    }

    template<> inline
    auto get<motor::FrontLeft>() {
        return Device::getMotor(motor::FrontLeft);
    }

    template<> inline
    auto get<motor::FrontRight>() {
        return Device::getMotor(motor::FrontRight);
    }

    template<> inline
    auto get<motor::Intake>() {
        return Device::getMotor(motor::Intake);
    }

    template<> inline
    auto get<motor::Lift>() {
        return Device::getMotor(motor::Lift);
    }

    template <motorGroup motorGroup>
    auto get();

    template<> inline
    auto get<motorGroup::LeftDrive>() {
        return Device::getMotorGroup(motorGroup::LeftDrive);
    }

    template<> inline
    auto get<motorGroup::RightDrive>() {
        return Device::getMotorGroup(motorGroup::RightDrive);
    }

    template<> inline
    auto get<motorGroup::Drive>() {
        return Device::getMotorGroup(motorGroup::Drive);
    }

    template <piston piston>
    auto get();

    template<> inline
    auto get<piston::BackClaw>() {
        return Device::getPiston(piston::BackClaw);
    }

    template<> inline
    auto get<piston::Tilter>() {
        return Device::getPiston(piston::Tilter);
    }

    template<> inline
    auto get<piston::FrontClaw>() {
        return Device::getPiston(piston::FrontClaw);
    }

    template <sensor sensor>
    auto get();

    template<> inline
    auto get<sensor::Inertial>() {
        return Device::getInertial(sensor::Inertial);
    }

    // template<> inline
    // auto get<sensor::LeftRotation>() {
    //     return Device::getRotation(sensor::LeftRotation);
    // }

    // template<> inline
    // auto get<sensor::RightRotation>() {
    //     return Device::getRotation(sensor::RightRotation);
    // }
    

    template<> inline
    auto get<sensor::LiftPotentiometer>() {
        return Device::getPotentiometer(sensor::LiftPotentiometer);
    }

    template<> inline
    auto get<sensor::FrontDistance>() {
        return Device::getDistance(sensor::FrontDistance);
    }

    // template<> inline
    // auto get<sensor::BackDistance>() {
    //     return Device::getDistance(sensor::BackDistance);
    // }

    template<controller controller>
    auto get();

    template<> inline
    auto get<controller::Master>() {
        return Device::getController(controller::Master);
    }
};