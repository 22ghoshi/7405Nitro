#include "Drive.hpp"

Drive::Drive() {}

void Drive::arcade(double power, double turn) {
    Device::get<motorGroup::LeftDrive>() = power + turn;
    Device::get<motorGroup::RightDrive>() = power - turn;
}

void Drive::tank(double left, double right) {
    Device::get<motorGroup::LeftDrive>() = left;
    Device::get<motorGroup::RightDrive>() = right;
}

void Drive::mecanum(double power, double strafe, double turn) {
    Device::get<motor::BackLeft>() = power - strafe + turn;
	Device::get<motor::BackRight>() = power + strafe - turn;
	Device::get<motor::FrontLeft>() = power + strafe + turn;
	Device::get<motor::FrontRight>() = power - strafe - turn;
}

void Drive::stop(brakeType brake) {
    Device::get<motorGroup::Drive>().stop(brake);
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
    int power = Device::get<controller::Master>().get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    power = fabs(power) < deadzone ? 0 : power;
    int turn = Device::get<controller::Master>().get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    turn = fabs(turn) < deadzone ? 0 : turn;
    if (fabs(power) < deadzone && fabs(turn) < deadzone) {
        stop();
    }
    else {
        arcade(dampen(power), dampen(turn));
    }
}