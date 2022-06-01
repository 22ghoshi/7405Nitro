#include "Robot.hpp"

BackClaw Robot::backClaw{BackClaw()};
Drive Robot::drive{Drive()};
FrontClaw Robot::frontClaw{FrontClaw()};
Intake Robot::intake{Intake()};
Lift Robot::lift{Lift()};

Point Robot::targetPos({Point()});
PID Robot::mPID{PID(0, 0, 0)};
PID Robot::tPID{PID(0, 0, 0)};
double Robot::moveErr;
double Robot::turnErr;
double Robot::macc = 20.0;
double Robot::tacc = 3;
bool Robot::turning = false;
bool Robot::turningBack = false;
bool Robot::turningDeg = false;
int Robot::moven = 0;
bool Robot::odomMove = true;
int Robot::driveSpeed = 0;

Robot::Robot() {}

void Robot::move(void* params) {
    pros::delay(20);
    int i = 0;
    while (true) {
        i++;
        if (pros::Task::notify_take(true, 20)) {
            odomMove = !odomMove;
        }
        if (odomMove) {
            moveErr = turning ? 0 : FPS::currentPos.distanceTo(targetPos);
            
            if ((turning && !turningDeg) || moveErr > 200.0) {
                targetPos.h = FPS::currentPos.angleTo(targetPos);
            }
            turnErr = targetPos.h - FPS::currentPos.h;
            turnErr = turnErr < 180 ? turnErr : turnErr - 360;
            double direction = cos(FPS::toRadians(turnErr)) > 0 ? 1.0 : -1.0;
            if ((!turning && direction < 0) || turningBack) {
                turnErr = turnErr > 0 ? turnErr - 180 : turnErr + 180;
            }

            if (fabs(turnErr) > tacc) {
                double turnSpeed = tPID.getPID(turnErr);
                Drive::arcade(0, turnSpeed);
                if (i % 3 == 0) {
                    printf("\ncurrentPos = (%f, %f, %f), targetPos = (%f, %f, %f), move = %d, turnErr = %f, turnSpeed = %f", 
                            FPS::currentPos.x, FPS::currentPos.y, FPS::currentPos.h, targetPos.x, targetPos.y, targetPos.h, 
                            moven, turnErr, turnSpeed);
                }
            }
            else if (moveErr > macc) {
                double turnSpeed = tPID.getPID(turnErr);
                double moveSpeed = mPID.getPID(moveErr);
                double speedSum = moveSpeed + fabs(turnSpeed);
                double maxMoveSpeed = moveSpeed * (127.0 / speedSum);
                double maxTurnSpeed = turnSpeed * (127.0 / speedSum);
                moveSpeed = moveSpeed < maxMoveSpeed ? moveSpeed : maxMoveSpeed;
                turnSpeed = fabs(turnSpeed) < fabs(maxTurnSpeed) ? turnSpeed : maxTurnSpeed;
                Drive::arcade(moveSpeed * direction, turnSpeed);
                if (i % 3 == 0) {
                    printf("\ncurrentPos = (%f, %f, %f), targetPos = (%f, %f, %f), move = %d, moveErr = %f, moveSpeed = %f, turnErr = %f, turnSpeed = %f", FPS::currentPos.x, FPS::currentPos.y, FPS::currentPos.h, targetPos.x, targetPos.y, targetPos.h, moven, moveErr, moveSpeed, turnErr, turnSpeed);
                }
            }
            else {
                Drive::stop();
            }
        }
        else {
            if (driveSpeed == 0) {
                Drive::stop();
            }
            else {
                double moveSpeed = driveSpeed;
                double turnErr = targetPos.h - FPS::currentPos.h;
                double turnSpeed = tPID.getPID(turnErr);
                double speedSum = fabs(moveSpeed) + fabs(turnSpeed);
                double maxMoveSpeed = moveSpeed * (127.0 / speedSum);
                double maxTurnSpeed = turnSpeed * (127.0 / speedSum);
                moveSpeed = fabs(moveSpeed) < fabs(maxMoveSpeed) ? moveSpeed : maxMoveSpeed;
                turnSpeed = fabs(turnSpeed) < fabs(maxTurnSpeed) ? turnSpeed : maxTurnSpeed;
                Drive::arcade(moveSpeed, turnSpeed);
                if (i % 3 == 0) {
                    printf("\nmove = %d, driveSpeed = %f, turnErr = %f, turnSpeed = %f", moven, driveSpeed, turnErr, turnSpeed);
                }
            }
        }
    }
}

void Robot::moveTo(double x, double y, std::initializer_list<double> newmPID, double newmacc, std::initializer_list<double> newtPID, double newtacc) {
    if (!odomMove) {
        Thread::notifyTask("move");
    }
    waitUntilStop();
    moven++;
    turning = false;
    turningBack = false;
    turningDeg = false;
    mPID.reset = true;
    tPID.reset = true;
    targetPos.x = x;
    targetPos.y = y;
    targetPos.h = FPS::currentPos.angleTo(targetPos);
    mPID.kP = newmPID.begin()[0];
    mPID.kI = newmPID.begin()[1];
    mPID.kD = newmPID.begin()[2];
    macc = newmacc;
    tPID.kP = newtPID.begin()[0];
    tPID.kI = newtPID.begin()[1];
    tPID.kD = newtPID.begin()[2];
    tacc = newtacc;
}

void Robot::moveToNow(double x, double y, std::initializer_list<double> newmPID, double newmacc, std::initializer_list<double> newtPID, double newtacc) {
    if (!odomMove) {
        Thread::notifyTask("move");
    }
    moven++;
    turning = false;
    turningBack = false;
    turningDeg = false;
    mPID.reset = true;
    tPID.reset = true;
    targetPos.x = x;
    targetPos.y = y;
    targetPos.h = FPS::currentPos.angleTo(targetPos);
    mPID.kP = newmPID.begin()[0];
    mPID.kI = newmPID.begin()[1];
    mPID.kD = newmPID.begin()[2];
    macc = newmacc;
    tPID.kP = newtPID.begin()[0];
    tPID.kI = newtPID.begin()[1];
    tPID.kD = newtPID.begin()[2];
    tacc = newtacc;
}

void Robot::turnTo(double x, double y, std::initializer_list<double> newtPID, double newtacc) {
    if (!odomMove) {
        Thread::notifyTask("move");
    }
    waitUntilStop();
    moven++;
    turning = true;
    turningBack = false;
    turningDeg = false;
    tPID.reset = true;
    targetPos.x = x;
    targetPos.y = y;
    targetPos.h = FPS::currentPos.angleTo(targetPos);
    tPID.kP = newtPID.begin()[0];
    tPID.kI = newtPID.begin()[1];
    tPID.kD = newtPID.begin()[2];
    tacc = newtacc;
}

void Robot::turnToNow(double x, double y, std::initializer_list<double> newtPID, double newtacc) {
    if (!odomMove) {
        Thread::notifyTask("move");
    }
    moven++;
    turning = true;
    turningBack = false;
    turningDeg = false;
    tPID.reset = true;
    targetPos.x = x;
    targetPos.y = y;
    targetPos.h = FPS::currentPos.angleTo(targetPos);
    tPID.kP = newtPID.begin()[0];
    tPID.kI = newtPID.begin()[1];
    tPID.kD = newtPID.begin()[2];
    tacc = newtacc;
}

void Robot::turnTo(double deg, std::initializer_list<double> newtPID, double newtacc) {
    if (!odomMove) {
        Thread::notifyTask("move");
    }
    waitUntilStop();
    moven++;
    turning = true;
    turningBack = false;
    turningDeg = true;
    tPID.reset = true;
    targetPos.h = deg;
    tPID.kP = newtPID.begin()[0];
    tPID.kI = newtPID.begin()[1];
    tPID.kD = newtPID.begin()[2];
    tacc = newtacc;
}

void Robot::turnToNow(double deg, std::initializer_list<double> newtPID, double newtacc) {
    if (!odomMove) {
        Thread::notifyTask("move");
    }
    moven++;
    turning = true;
    turningBack = false;
    turningDeg = true;
    tPID.reset = true;
    targetPos.h = deg;
    tPID.kP = newtPID.begin()[0];
    tPID.kI = newtPID.begin()[1];
    tPID.kD = newtPID.begin()[2];
    tacc = newtacc;
}

void Robot::turnBackTo(double x, double y, std::initializer_list<double> newtPID, double newtacc) {
    if (!odomMove) {
        Thread::notifyTask("move");
    }
    waitUntilStop();
    moven++;
    turning = true;
    turningBack = true;
    turningDeg = false;
    tPID.reset = true;
    targetPos.x = x;
    targetPos.y = y;
    targetPos.h = FPS::currentPos.angleTo(targetPos);
    tPID.kP = newtPID.begin()[0];
    tPID.kI = newtPID.begin()[1];
    tPID.kD = newtPID.begin()[2];
    tacc = newtacc;
}

void Robot::turnBackToNow(double x, double y, std::initializer_list<double> newtPID, double newtacc) {
    if (!odomMove) {
        Thread::notifyTask("move");
    }
    moven++;
    turning = true;
    turningBack = true;
    turningDeg = false;
    tPID.reset = true;
    targetPos.x = x;
    targetPos.y = y;
    targetPos.h = FPS::currentPos.angleTo(targetPos);
    tPID.kP = newtPID.begin()[0];
    tPID.kI = newtPID.begin()[1];
    tPID.kD = newtPID.begin()[2];
    tacc = newtacc;
}

void Robot::setSpeed(double speed, std::initializer_list<double> newtPID) {
    if (odomMove) {
        Thread::notifyTask("move");
    }
    moven++;
    driveSpeed = speed;
    targetPos.h = FPS::currentPos.h;
    tPID.kP = newtPID.begin()[0];
    tPID.kI = newtPID.begin()[1];
    tPID.kD = newtPID.begin()[2];
}

void Robot::waitUntilStop() {
    if (moven == 0) {
        return;
    }
    std::deque<double> distances;
    distances.clear();
    std::deque<double> turns;
    turns.clear();
    double time = 0;
    while(distances.size() < 25 || turns.size() < 25) {
        distances.push_front(moveErr);
        turns.push_front(turnErr);
        pros::delay(20);
        time += 20;
    }
    while (moveErr > macc || fabs(turnErr) > tacc) {
        if (fabs(distances.back() - distances.front()) < 15.0 && fabs(turns.back() - turns.front()) < 0.75) {
            printf("\nbroke");
            break;
        }
        distances.pop_back();
        distances.push_front(moveErr);
        turns.pop_back();
        turns.push_front(turnErr);
        pros::delay(20);
        time += 20;
    }
}

void Robot::brainDisplay(void* params) {
    while (true) {
        if (Device::get<sensor::Inertial>()->is_calibrating()) {
            pros::lcd::set_text(1, "calibrating...");
        }
        else {
            pros::lcd::set_text(1, "X: " + std::to_string(FPS::currentPos.x));
            pros::lcd::set_text(2, "Y: " + std::to_string(FPS::currentPos.y));
            pros::lcd::set_text(3, "H: " + std::to_string(FPS::currentPos.h));
            // pros::lcd::set_text(4, "leftrot: " + std::to_string(Device::get<sensor::LeftRotation>().get_position()));
            // pros::lcd::set_text(5, "rightrot: " + std::to_string(Device::get<sensor::RightRotation>().get_position()));
        }
        // pros::lcd::set_text(6, "intaking: " + std::to_string(Intake::intaking) + ", outtaking: " + std::to_string(Intake::outtaking));
        pros::lcd::set_text(5, "liftpot: " + std::to_string(Device::get<sensor::LiftPotentiometer>()->get_angle()));
        pros::delay(20);
    }
}

void Robot::controllerDisplay(void* params) {
    Device::get<controller::Master>()->clear();
    pros::delay(50);
    while (true) {
        Device::get<controller::Master>()->print(0, 16, "bat: %g %", pros::battery::get_capacity());
        pros::delay(50);
        if (Device::get<sensor::Inertial>()->is_calibrating()) {
            Device::get<controller::Master>()->print(0, 0, "calibrating...");
            pros::delay(50);
        }
        else {
            Device::get<controller::Master>()->print(0, 0, ("X: " + std::to_string(FPS::currentPos.x)).c_str());
            pros::delay(50);
            Device::get<controller::Master>()->print(1, 0, ("Y: " + std::to_string(FPS::currentPos.y)).c_str());
            pros::delay(50);
            Device::get<controller::Master>()->print(2, 0, ("H: " + std::to_string(FPS::currentPos.h)).c_str());
            pros::delay(50);
        }
    }
}

