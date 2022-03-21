#include "Drive.hpp"

Drive::Drive() {}

void Drive::arcade(double power, double turn) {
    Devices::get<motorGroups::LeftDrive>() = power + turn;
    Devices::get<motorGroups::RightDrive>() = power - turn;
}

void Drive::tank(double left, double right) {
    Devices::get<motorGroups::LeftDrive>() = left;
    Devices::get<motorGroups::RightDrive>() = right;
}

void Drive::mecanum(double power, double strafe, double turn) {
    Devices::get<motors::BackLeft>() = power - strafe + turn;
	Devices::get<motors::BackRight>() = power + strafe - turn;
	Devices::get<motors::FrontLeft>() = power + strafe + turn;
	Devices::get<motors::FrontRight>() = power - strafe - turn;
}

void Drive::stop(brakeType brake) {
    Devices::get<motorGroups::Drive>().stop(brake);
}

int Drive::dampen(int input) {
    double s = 80;
    double a = .64;
    double v = (127*a-127)/(-s*s+254*s-16129);
    double c = a - 2*v*s;
    double output;
    if (abs(input) < abs(s)) {
        output = a * input;
    }
    else {
        double x = abs(input);
        double y = -(s - x) * (c + v * (s + x)) + a * s;
        output = y * input / abs(input);
    }

    return (int)std::round(output);
}

void Drive::drive(int deadzone) {
    int power = Devices::get<controllers::Master>().get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    power = fabs(power) < deadzone ? 0 : power;
    int turn = Devices::get<controllers::Master>().get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    turn = fabs(turn) < deadzone ? 0 : turn;
    if (fabs(power) < deadzone && fabs(turn) < deadzone) {
        stop();
    }
    else {
        arcade(dampen(power), dampen(turn));
    }
}