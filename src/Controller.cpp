#include "Controller.hpp"

std::map<pros::controller_digital_e_t, bool> Controller::buttonStatus;
std::map<pros::controller_digital_e_t, bool> Controller::buttonNewPressStatus;

std::map<pros::controller_digital_e_t, std::function<void(void)>> Controller::buttonActions;
std::map<pros::controller_digital_e_t, std::function<void(void)>> Controller::buttonDefaults;
std::map<pros::controller_digital_e_t, std::function<void(void)>> Controller::buttonNewPressActions;

Controller::Controller() {}

void Controller::update(void* params) {
    while(true) {
        for (int i = pros::E_CONTROLLER_DIGITAL_L1; i <= pros::E_CONTROLLER_DIGITAL_A; i++) {
            buttonStatus[(pros::controller_digital_e_t)i] = Devices::get<controllers::Master>().get_digital((pros::controller_digital_e_t)i);
        }

        for (int i = pros::E_CONTROLLER_DIGITAL_L1; i <= pros::E_CONTROLLER_DIGITAL_A; i++) {
            buttonNewPressStatus[(pros::controller_digital_e_t)i] = Devices::get<controllers::Master>().get_digital_new_press((pros::controller_digital_e_t)i);
        } 

        pros::delay(20);
    }
}

void Controller::act() {
    for (auto const& [button, status] : buttonNewPressStatus) {
        if(status) {
            if(buttonNewPressActions.find(button) != buttonNewPressActions.end()) {
                buttonNewPressActions.at(button)();
            }
        }
    }
    
    for (auto const& [button, status] : buttonStatus) {
        if(status) {
            if(buttonActions.find(button) != buttonActions.end()) {
                buttonActions.at(button)();
            }
        } else if (!status) {
            if(buttonDefaults.find(button) != buttonDefaults.end()) {
                buttonDefaults.at(button)();
            }
        }
    }
}

void Controller::registerButton(pros::controller_digital_e_t button, std::function<void(void)> action, std::function<void(void)> defaultAction) {
    buttonActions[button] = action;
    buttonDefaults[button] = defaultAction;
}

void Controller::registerButtonNewPress(pros::controller_digital_e_t button, std::function<void(void)> action) {
    buttonNewPressActions[button] = action;
}