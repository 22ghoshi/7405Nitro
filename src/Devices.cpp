#include "Devices.hpp"

std::map<std::string, std::unique_ptr<pros::Motor>> motors;
std::map<std::string, std::unique_ptr<pros::ADIDigitalOut>> pistons;

std::map<std::string, std::unique_ptr<pros::ADIButton>> buttons;
std::map<std::string, std::unique_ptr<pros::ADILightSensor>> lines;
std::map<std::string, std::unique_ptr<pros::ADIPotentiometer>> potentiometers;
std::map<std::string, std::unique_ptr<pros::ADIUltrasonic>> ultrasonics;
std::map<std::string, std::unique_ptr<pros::ADIEncoder>> encoders;

std::map<std::string, std::unique_ptr<pros::Rotation>> rotations;
std::map<std::string, std::unique_ptr<pros::IMU>> inertials;
std::map<std::string, std::unique_ptr<pros::Vision>> visions;
std::map<std::string, std::unique_ptr<pros::Distance>> distances;

std::map<std::string, std::unique_ptr<pros::Controller>> controllers;

pros::Motor* Device::getMotor(std::string name, int port, motorGearset gearset, bool reversed) {
	if (motors.find(name) == motors.end()) {
		switch (gearset) {
			case motorGearset::GS100:
				motors[name] = std::make_unique<pros::Motor>(port, pros::E_MOTOR_GEARSET_36, reversed);
				break;
			case motorGearset::GS200:
				motors[name] = std::make_unique<pros::Motor>(port, pros::E_MOTOR_GEARSET_18, reversed);
				break;
			case motorGearset::GS600:
				motors[name] = std::make_unique<pros::Motor>(port, pros::E_MOTOR_GEARSET_06, reversed);
				break;
		}
	}
	return motors[name].get();
}

pros::ADIDigitalOut* Device::getPiston(std::string name, int port, bool start) {
	if (pistons.find(name) == pistons.end()) {
		pistons[name] = std::make_unique<pros::ADIDigitalOut>(port, start);
	}
	return pistons[name].get();
}

pros::ADIButton* Device::getButton(std::string name, int port) {
	if (buttons.find(name) == buttons.end()) {
		buttons[name] = std::make_unique<pros::ADIButton>(port);
	}
	return buttons[name].get();
}

pros::ADILineSensor* Device::getLine(std::string name, int port) {
	if (lines.find(name) == lines.end()) {
		lines[name] = std::make_unique<pros::ADILineSensor>(port);
	}
	return lines[name].get();
}

pros::ADIPotentiometer* Device::getPotentiometer(std::string name, int port) {
	if (potentiometers.find(name) == potentiometers.end()) {
		potentiometers[name] = std::make_unique<pros::ADIPotentiometer>(port);
	}
	return potentiometers[name].get();
}

pros::ADIUltrasonic* Device::getUltrasonic(std::string name, int port) {
	if (ultrasonics.find(name) == ultrasonics.end()) {
		ultrasonics[name] = std::make_unique<pros::ADIUltrasonic>(port, port + 1);
	}
	return ultrasonics[name].get();
}

pros::ADIEncoder* Device::getEncoder(std::string name, int port, bool reversed) {
	if (encoders.find(name) == encoders.end()) {
		encoders[name] = std::make_unique<pros::ADIEncoder>(port, port + 1, reversed);
	}
	return encoders[name].get();
}

pros::Rotation* Device::getRotation(std::string name, int port) {
	if (rotations.find(name) == rotations.end()) {
		rotations[name] = std::make_unique<pros::Rotation>(port);
	}
	return rotations[name].get();
}

pros::IMU* Device::getInertial(std::string name, int port) {
	if (inertials.find(name) == inertials.end()) {
		inertials[name] = std::make_unique<pros::IMU>(port);
	}
	return inertials[name].get();
}

pros::Vision* Device::getVision(std::string name, int port) {
	if (visions.find(name) == visions.end()) {
		visions[name] = std::make_unique<pros::Vision>(port);
	}
	return visions[name].get();
}

pros::Distance* Device::getDistance(std::string name, int port) {
	if (distances.find(name) == distances.end()) {
		distances[name] = std::make_unique<pros::Distance>(port);
	}
	return distances[name].get();
}

pros::Controller* Device::getController(std::string name) {
	if (controllers.find(name) == controllers.end()) {
		if (name == "Master") {
			controllers[name] = std::make_unique<pros::Controller>(pros::E_CONTROLLER_MASTER);
		}
	}
	return controllers[name].get();
}