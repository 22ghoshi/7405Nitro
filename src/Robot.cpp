#include "Robot.hpp"

BackClaw Robot::backClaw{BackClaw(true, false, true, true)};
Drive Robot::drive{Drive()};
FPS Robot::fps{FPS()};
FrontClaw Robot::frontClaw{FrontClaw(true, false)};
Intake Robot::intake{Intake()};
Lift Robot::lift{Lift(0.3, 0.001, 0.1, 40)};

Robot::Robot() {}