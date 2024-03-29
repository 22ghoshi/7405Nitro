#include "includes.hpp"

std::vector<std::string> autonNames{"left", "middle", "right", "skills", "test", "extra1", "extra2", "extra3"};
autons auton = autons::right;

lv_obj_t * myButton;
lv_obj_t * myButtonLabel;
lv_obj_t * myLabel;

lv_style_t myButtonStyleREL;
lv_style_t myButtonStylePR;
lv_style_t myButtonStyleREL2;
lv_style_t myButtonStylePR2;

// Following eight functions change the 'autonSelected' variable depending on which button was pressed
static lv_res_t btn_click_action3(lv_obj_t * btn) {
  uint8_t id = lv_obj_get_free_num(btn);
  if (id == 0) {
    auton = (autons)0;
  }
  return LV_RES_OK;
}

static lv_res_t btn_click_action4(lv_obj_t * btn) {
  uint8_t id = lv_obj_get_free_num(btn);
  if (id == 0) {
    auton = (autons)1;
  }
  return LV_RES_OK;
}

static lv_res_t btn_click_action5(lv_obj_t * btn) {
  uint8_t id = lv_obj_get_free_num(btn);
  if (id == 0) {
    auton = (autons)2;
  }
  return LV_RES_OK;
}

static lv_res_t btn_click_action6(lv_obj_t * btn) {
  uint8_t id = lv_obj_get_free_num(btn);
  if (id == 0) {
    auton = (autons)3;
  }
  return LV_RES_OK;
}

static lv_res_t btn_click_action7(lv_obj_t * btn) {
  uint8_t id = lv_obj_get_free_num(btn);
  if (id == 0) {
    auton = (autons)4;
  }
  return LV_RES_OK;
}

static lv_res_t btn_click_action8(lv_obj_t * btn) {
  uint8_t id = lv_obj_get_free_num(btn);
  if (id == 0) {
    auton = (autons)5;
  }
  return LV_RES_OK;
}

static lv_res_t btn_click_action9(lv_obj_t * btn) {
  uint8_t id = lv_obj_get_free_num(btn);
  if (id == 0) {
    auton = (autons)6;
  }
  return LV_RES_OK;
}

static lv_res_t btn_click_action10(lv_obj_t * btn) {
  uint8_t id = lv_obj_get_free_num(btn);
  if (id == 0) {
    auton = (autons)7;
  }
  return LV_RES_OK;
}

static lv_res_t btn_click_action(lv_obj_t * btn)
{
    uint8_t id = lv_obj_get_free_num(btn);

    if(id == 0)
    {
        lv_obj_clean(lv_scr_act());
        myButton = lv_btn_create(lv_scr_act(), NULL); 
        lv_obj_set_free_num(myButton, 0); 
        lv_btn_set_action(myButton, LV_BTN_ACTION_CLICK, btn_click_action3); 
        lv_btn_set_style(myButton, LV_BTN_STYLE_REL, &myButtonStyleREL); 
        lv_btn_set_style(myButton, LV_BTN_STYLE_PR, &myButtonStylePR); 
        lv_obj_set_size(myButton, 225, 105); 
        lv_obj_align(myButton, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10); 

        myButtonLabel = lv_label_create(myButton, NULL); 
        lv_label_set_text(myButtonLabel, autonNames[0].c_str()); 

        myButton = lv_btn_create(lv_scr_act(), NULL); 
        lv_obj_set_free_num(myButton, 0); 
        lv_btn_set_action(myButton, LV_BTN_ACTION_CLICK, btn_click_action4); 
        lv_btn_set_style(myButton, LV_BTN_STYLE_REL, &myButtonStyleREL); 
        lv_btn_set_style(myButton, LV_BTN_STYLE_PR, &myButtonStylePR); 
        lv_obj_set_size(myButton, 225, 105); 
        lv_obj_align(myButton, NULL, LV_ALIGN_IN_TOP_RIGHT, -10, 10); 

        myButtonLabel = lv_label_create(myButton, NULL); 
        lv_label_set_text(myButtonLabel, autonNames[1].c_str()); 

        myButton = lv_btn_create(lv_scr_act(), NULL); 
        lv_obj_set_free_num(myButton, 0); 
        lv_btn_set_action(myButton, LV_BTN_ACTION_CLICK, btn_click_action5); 
        lv_btn_set_style(myButton, LV_BTN_STYLE_REL, &myButtonStyleREL); 
        lv_btn_set_style(myButton, LV_BTN_STYLE_PR, &myButtonStylePR); 
        lv_obj_set_size(myButton, 225, 105); 
        lv_obj_align(myButton, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 10, -10); 

        myButtonLabel = lv_label_create(myButton, NULL); 
        lv_label_set_text(myButtonLabel, autonNames[2].c_str()); 

        myButton = lv_btn_create(lv_scr_act(), NULL); 
        lv_obj_set_free_num(myButton, 0); 
        lv_btn_set_action(myButton, LV_BTN_ACTION_CLICK, btn_click_action6); 
        lv_btn_set_style(myButton, LV_BTN_STYLE_REL, &myButtonStyleREL); 
        lv_btn_set_style(myButton, LV_BTN_STYLE_PR, &myButtonStylePR); 
        lv_obj_set_size(myButton, 225, 105); 
        lv_obj_align(myButton, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -10); 

        myButtonLabel = lv_label_create(myButton, NULL); 
        lv_label_set_text(myButtonLabel, autonNames[3].c_str()); 
    }

    return LV_RES_OK;
}

static lv_res_t btn_click_action2(lv_obj_t * btn)
{
    uint8_t id = lv_obj_get_free_num(btn);

    if(id == 0)
    {
        lv_obj_clean(lv_scr_act());
        myButton = lv_btn_create(lv_scr_act(), NULL); 
        lv_obj_set_free_num(myButton, 0); 
        lv_btn_set_action(myButton, LV_BTN_ACTION_CLICK, btn_click_action7); 
        lv_btn_set_style(myButton, LV_BTN_STYLE_REL, &myButtonStyleREL2); 
        lv_btn_set_style(myButton, LV_BTN_STYLE_PR, &myButtonStylePR2); 
        lv_obj_set_size(myButton, 225, 105); 
        lv_obj_align(myButton, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10); 

        myButtonLabel = lv_label_create(myButton, NULL); 
        lv_label_set_text(myButtonLabel, autonNames[4].c_str()); 

        myButton = lv_btn_create(lv_scr_act(), NULL); 
        lv_obj_set_free_num(myButton, 0); 
        lv_btn_set_action(myButton, LV_BTN_ACTION_CLICK, btn_click_action8); 
        lv_btn_set_style(myButton, LV_BTN_STYLE_REL, &myButtonStyleREL2); 
        lv_btn_set_style(myButton, LV_BTN_STYLE_PR, &myButtonStylePR2); 
        lv_obj_set_size(myButton, 225, 105); 
        lv_obj_align(myButton, NULL, LV_ALIGN_IN_TOP_RIGHT, -10, 10); 

        myButtonLabel = lv_label_create(myButton, NULL); 
        lv_label_set_text(myButtonLabel, autonNames[5].c_str()); 

        myButton = lv_btn_create(lv_scr_act(), NULL); 
        lv_obj_set_free_num(myButton, 0); 
        lv_btn_set_action(myButton, LV_BTN_ACTION_CLICK, btn_click_action9); 
        lv_btn_set_style(myButton, LV_BTN_STYLE_REL, &myButtonStyleREL2); 
        lv_btn_set_style(myButton, LV_BTN_STYLE_PR, &myButtonStylePR2); 
        lv_obj_set_size(myButton, 225, 105); 
        lv_obj_align(myButton, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 10, -10); 

        myButtonLabel = lv_label_create(myButton, NULL); 
        lv_label_set_text(myButtonLabel, autonNames[6].c_str()); 

        myButton = lv_btn_create(lv_scr_act(), NULL); 
        lv_obj_set_free_num(myButton, 0); 
        lv_btn_set_action(myButton, LV_BTN_ACTION_CLICK, btn_click_action10); 
        lv_btn_set_style(myButton, LV_BTN_STYLE_REL, &myButtonStyleREL2); 
        lv_btn_set_style(myButton, LV_BTN_STYLE_PR, &myButtonStylePR2); 
        lv_obj_set_size(myButton, 225, 105); 
        lv_obj_align(myButton, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -10); 

        myButtonLabel = lv_label_create(myButton, NULL); 
        lv_label_set_text(myButtonLabel, autonNames[7].c_str()); 
    }

    return LV_RES_OK;
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	  pros::lcd::initialize();
	  pros::delay(100);

    // lv_style_copy(&myButtonStyleREL, &lv_style_plain);
    // myButtonStyleREL.body.main_color = LV_COLOR_MAKE(0, 0, 150);
    // myButtonStyleREL.body.grad_color = LV_COLOR_MAKE(200, 200, 200);
    // myButtonStyleREL.body.radius = 10;
    // myButtonStyleREL.text.color = LV_COLOR_MAKE(255, 255, 255);

    // lv_style_copy(&myButtonStylePR, &lv_style_plain);
    // myButtonStylePR.body.main_color = LV_COLOR_MAKE(0, 0, 255);
    // myButtonStylePR.body.grad_color = LV_COLOR_MAKE(255, 255, 255);
    // myButtonStylePR.body.radius = 10;
    // myButtonStylePR.text.color = LV_COLOR_MAKE(255, 255, 255);

    // myButton = lv_btn_create(lv_scr_act(), NULL);
    // lv_obj_set_free_num(myButton, 0);
    // lv_btn_set_action(myButton, LV_BTN_ACTION_CLICK, btn_click_action);
    // lv_btn_set_style(myButton, LV_BTN_STYLE_REL, &myButtonStyleREL);
    // lv_btn_set_style(myButton, LV_BTN_STYLE_PR, &myButtonStylePR);
    // lv_obj_set_size(myButton, 225, 210);
    // lv_obj_align(myButton, NULL, LV_ALIGN_IN_TOP_RIGHT, -10, 10);

    // myButtonLabel = lv_label_create(myButton, NULL);
    // lv_label_set_text(myButtonLabel, "5-8");

    // myButton = lv_btn_create(lv_scr_act(), NULL);
    // lv_obj_set_free_num(myButton, 0);
    // lv_btn_set_action(myButton, LV_BTN_ACTION_CLICK, btn_click_action2);
    // lv_btn_set_style(myButton, LV_BTN_STYLE_REL, &myButtonStyleREL);
    // lv_btn_set_style(myButton, LV_BTN_STYLE_PR, &myButtonStylePR);
    // lv_obj_set_size(myButton, 225, 210);
    // lv_obj_align(myButton, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);

    // myButtonLabel = lv_label_create(myButton, NULL);
    // lv_label_set_text(myButtonLabel, "1-4");

    // while (auton == autons::test) {
    //   pros::delay(25);
    // }

    Device::initAll();

    Thread::startTask("brain display", Robot::brainDisplay);
    Thread::startTask("controller display", Robot::controllerDisplay);

    Device::get<sensor::Inertial>()->reset();
    while (Device::get<sensor::Inertial>()->is_calibrating()) {
      pros::delay(20);
    }
    Thread::startTask("fps", FPS::run);

    pros::delay(20);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}