#include "EtRobocon2019.h"
#include "Controller.h"
#include "Display.h"

void EtRobocon2019::start() {
  Controller controller;
  const int pwm = (Controller::MOTOR_PWM_MAX) / 6;
  const int duration = 2000;

  Display::init();
  while (1) {
    Display::print(1, "Forwarding...");
    controller.leftWheel.setPWM(pwm);
    controller.rightWheel.setPWM(pwm);
    controller.clock.sleep(duration);
    // end::main_task_1[]
    // tag::main_task_2[]
    Display::print(1, "Backwarding...");
    controller.leftWheel.setPWM(-pwm);
    controller.rightWheel.setPWM(-pwm);
    controller.clock.sleep(duration);

    // 左ボタンを長押し、それを捕捉する
    if (controller.buttonIsPressedLeft()) {
      break;
    }
  }

  Display::print(1, "Stopped...");
  controller.leftWheel.stop();
  controller.rightWheel.stop();
  while (controller.buttonIsPressedLeft()) {
    ;
  }
}