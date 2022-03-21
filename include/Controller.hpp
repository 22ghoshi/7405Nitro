#pragma once
#include "main.h"

#include "Devices.hpp"

#include <map>
#include <memory>
#include <string>
#include <functional>

class Controller {
    private:
    Controller();

    static std::map<pros::controller_digital_e_t, bool> buttonStatus;
    static std::map<pros::controller_digital_e_t, bool> buttonNewPressStatus;

    static std::map<pros::controller_digital_e_t, std::function<void(void)>> buttonActions;
    static std::map<pros::controller_digital_e_t, std::function<void(void)>> buttonDefaults;
    static std::map<pros::controller_digital_e_t, std::function<void(void)>> buttonNewPressActions;

    public:
    static void update();
    static void act();
    static void registerButton(pros::controller_digital_e_t button, std::function<void(void)> action, std::function<void(void)> defaultAction);
    static void registerButtonNewPress(pros::controller_digital_e_t button, std::function<void(void)> action);
};