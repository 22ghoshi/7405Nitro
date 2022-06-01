#include "Devices.hpp"

std::map<motor, pros::Motor*> motors;
std::map<motorGroup, MotorGroup*> motorGroups;
std::map<piston, pros::ADIDigitalOut*> pistons;

std::map<sensor, pros::ADIButton*> buttons;
std::map<sensor, pros::ADILightSensor*> lines;
std::map<sensor, pros::ADIPotentiometer*> potentiometers;
std::map<sensor, pros::ADIUltrasonic*> ultrasonics;
std::map<sensor, pros::ADIEncoder*> encoders;

std::map<sensor, pros::Rotation*> rotations;
std::map<sensor, pros::IMU*> inertials;
std::map<sensor, pros::Vision*> visions;
std::map<sensor, pros::Distance*> distances;

std::map<controller, pros::Controller*> controllers;

void Device::initAll() {
	initMotor(motor::BackLeft, 16, motorGearset::GS600, true);
	initMotor(motor::BackRight, 5, motorGearset::GS600);
	initMotor(motor::MidLeft, 7, motorGearset::GS600, true);
	initMotor(motor::MidRight, 3, motorGearset::GS600);
	initMotor(motor::FrontLeft, 21, motorGearset::GS600);
	initMotor(motor::FrontRight, 13, motorGearset::GS600, true);
	initMotor(motor::Intake, 8, motorGearset::GS600);
	initMotor(motor::Lift, 4, motorGearset::GS100);

	initMotorGroup(motorGroup::LeftDrive, {motor::BackLeft, motor::MidLeft, motor::FrontLeft});
	initMotorGroup(motorGroup::RightDrive, {motor::BackRight, motor::MidRight, motor::FrontRight});
	initMotorGroup(motorGroup::Drive, {motor::BackLeft, motor::MidLeft, motor::FrontLeft,
									   motor::BackRight, motor::MidRight, motor::FrontRight});

	initPiston(piston::BackClaw, 6, 2, true);
	initPiston(piston::Tilter, 6, 3, false);
	initPiston(piston::FrontClaw, 6, 1, true);

	initPotentiometer(sensor::LiftPotentiometer, 6, 5);

	// initRotation(sensor::LeftRotation, 13);
	// initRotation(sensor::RightRotation, 6);

	initInertial(sensor::Inertial, 12);

	initDistance(sensor::FrontDistance, 10);
	// initDistance(sensor::BackDistance, 17);

	initController(controller::Master);
}

void Device::initMotor(motor motorName, std::uint8_t port, motorGearset gearset, bool reversed) {
	if (motors.find(motorName) == motors.end()) {
		switch (gearset) {
			case motorGearset::GS100:
				motors[motorName] = new pros::Motor(port, pros::E_MOTOR_GEARSET_36, reversed);
				break;
			case motorGearset::GS200:
				motors[motorName] = new pros::Motor(port, pros::E_MOTOR_GEARSET_18, reversed);
				break;
			case motorGearset::GS600:
				motors[motorName] = new pros::Motor(port, pros::E_MOTOR_GEARSET_06, reversed);
				break;
		}
	}
}

pros::Motor* Device::getMotor(motor motorName) {
	return motors[motorName];
}

void Device::initMotorGroup(motorGroup motorGroupName, std::vector<motor> groupMotors) {
	if (motorGroups.find(motorGroupName) == motorGroups.end()) {
		std::list<pros::Motor*> motorPtrs;
		for (auto const& motorName : groupMotors) {
			motorPtrs.push_back(motors[motorName]);
		}
		motorGroups[motorGroupName] = new MotorGroup(motorPtrs);
	}
}

MotorGroup* Device::getMotorGroup(motorGroup motorGroupName) {
	return motorGroups[motorGroupName];
}

void Device::initPiston(piston pistonName, std::uint8_t port, bool initState) {
	if (pistons.find(pistonName) == pistons.end()) {
		pistons[pistonName] = new pros::ADIDigitalOut(port, initState);
	}
}

void Device::initPiston(piston pistonName, std::uint8_t smartPort, std::uint8_t ADIPort, bool initState ) {
	if (pistons.find(pistonName) == pistons.end()) {
		pistons[pistonName] = new pros::ADIDigitalOut(std::make_pair(smartPort, ADIPort), initState);
	}
}

pros::ADIDigitalOut* Device::getPiston(piston pistonName) {
	return pistons[pistonName];
}

void Device::initButton(sensor buttonName, std::uint8_t port) {
	if (buttons.find(buttonName) == buttons.end()) {
		buttons[buttonName] = new pros::ADIButton(port);
	}
}

void Device::initButton(sensor buttonName, std::uint8_t smartPort, std::uint8_t ADIPort) {
	if (buttons.find(buttonName) == buttons.end()) {
		buttons[buttonName] = new pros::ADIButton(std::make_pair(smartPort, ADIPort));
	}
}

pros::ADIButton* Device::getButton(sensor buttonName) {
	return buttons[buttonName];
}

void Device::initLine(sensor lineName, std::uint8_t port) {
	if (lines.find(lineName) == lines.end()) {
		lines[lineName] = new pros::ADILineSensor(port);
	}
}

void Device::initLine(sensor lineName, std::uint8_t smartPort, std::uint8_t ADIPort) {
	if (lines.find(lineName) == lines.end()) {
		lines[lineName] = new pros::ADILineSensor(std::make_pair(smartPort, ADIPort));
	}
}

pros::ADILineSensor* Device::getLine(sensor lineName) {
	return lines[lineName];
}

void Device::initPotentiometer(sensor potName, std::uint8_t port) {
	if (potentiometers.find(potName) == potentiometers.end()) {
		potentiometers[potName] = new pros::ADIPotentiometer(port);
	}
}

void Device::initPotentiometer(sensor potName, std::uint8_t smartPort, std::uint8_t ADIPort) {
	if (potentiometers.find(potName) == potentiometers.end()) {
		potentiometers[potName] = new pros::ADIPotentiometer(std::make_pair(smartPort, ADIPort));
	}
}

pros::ADIPotentiometer* Device::getPotentiometer(sensor potName) {
	return potentiometers[potName];
}

void Device::initUltrasonic(sensor ultName, std::uint8_t port) {
	if (ultrasonics.find(ultName) == ultrasonics.end()) {
		ultrasonics[ultName] = new pros::ADIUltrasonic(port, port + 1);
	}
}

void Device::initUltrasonic(sensor ultName, std::uint8_t smartPort, std::uint8_t ADIPort) {
	if (ultrasonics.find(ultName) == ultrasonics.end()) {
		ultrasonics[ultName] = new pros::ADIUltrasonic(std::make_tuple(smartPort, ADIPort, ADIPort + 1));
	}
}

pros::ADIUltrasonic* Device::getUltrasonic(sensor ultName) {
	return ultrasonics[ultName];
}

void Device::initEncoder(sensor encName, std::uint8_t port, bool reverse) {
	if (encoders.find(encName) == encoders.end()) {
		encoders[encName] = new pros::ADIEncoder(port, port + 1, reverse);
	}
}

void Device::initEncoder(sensor encName, std::uint8_t smartPort, std::uint8_t ADIPort, bool reverse) {
	if (encoders.find(encName) == encoders.end()) {
		encoders[encName] = new pros::ADIEncoder(std::make_tuple(smartPort, ADIPort, ADIPort + 1), reverse);
	}
}

pros::ADIEncoder* Device::getEncoder(sensor encName) {
	return encoders[encName];
}

void Device::initRotation(sensor rotName, std::uint8_t port) {
	if (rotations.find(rotName) == rotations.end()) {
		rotations[rotName] = new pros::Rotation(port);
	}
}

pros::Rotation* Device::getRotation(sensor rotName) {
	return rotations[rotName];
}

void Device::initInertial(sensor IMUName, std::uint8_t port) {
	if (inertials.find(IMUName) == inertials.end()) {
		inertials[IMUName] = new pros::IMU(port);
	}
}

pros::IMU* Device::getInertial(sensor IMUName) {
	return inertials[IMUName];
}

void Device::initVision(sensor visionName, std::uint8_t port) {
	if (visions.find(visionName) == visions.end()) {
		visions[visionName] = new pros::Vision(port);
	}
}

pros::Vision* Device::getVision(sensor visionName) {
	return visions[visionName];
}

void Device::initDistance(sensor distanceName, std::uint8_t port) {
	if (distances.find(distanceName) == distances.end()) {
		distances[distanceName] = new pros::Distance(port);
	}
}

pros::Distance* Device::getDistance(sensor distanceName) {
	return distances[distanceName];
}

void Device::initController(controller ctrlName) {
	if (controllers.find(ctrlName) == controllers.end()) {
		if (ctrlName == controller::Master) {
			controllers[ctrlName] = new pros::Controller(pros::E_CONTROLLER_MASTER);
		}
	}
}

pros::Controller* Device::getController(controller ctrlName) {
	return controllers[ctrlName];
}