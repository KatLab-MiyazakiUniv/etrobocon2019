#include "app.h"

#include "Motor.h"
#include "Clock.h"
#include "Display.h"

using namespace ev3api;

// 演習用のユーティリティ

/**
 * メインタスク
 */
// tag::main_task_1[]
void main_task(intptr_t unused) {

  Motor leftWheel(PORT_C);
  Motor rightWheel(PORT_B);
  Clock clock;

  const int8_t pwm = (Motor::PWM_MAX) / 6;
  const uint32_t duration = 2000;

  Display::init();
  while(1) {
    Display::print(1, "Forwarding...");
    leftWheel.setPWM(pwm);
    rightWheel.setPWM(pwm);
    clock.sleep(duration);
// end::main_task_1[]
// tag::main_task_2[]
    Display::print(1, "Backwarding...");
    leftWheel.setPWM(-pwm);
    rightWheel.setPWM(-pwm);
    clock.sleep(duration);

    // 左ボタンを長押し、それを捕捉する
    if (ev3_button_is_pressed(LEFT_BUTTON)) {
      break;
    }
  }

  Display::print(1, "Stopped...");
  leftWheel.stop();
  rightWheel.stop();
  while(ev3_button_is_pressed(LEFT_BUTTON)) {
    ;
  }

  ext_tsk();
}
// end::main_task_2[]



