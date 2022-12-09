#include "app.h"
#include "util.h"

#include "Motor.h"
#include "Clock.h"

using namespace ev3api;

/**
 * メインタスク
 */
// tag::main_task_1[]
void main_task(intptr_t unused) {

  Motor leftWheel(PORT_C);
  Motor rightWheel(PORT_B);
  Clock clock;

#ifndef MAKE_RASPIKE
  const int8_t pwm = (Motor::PWM_MAX) / 6;
#else
  const int8_t pwm = 60;
#endif

  const uint32_t duration = 2000*1000;

  init_f(__FILE__);
  while(1) {
    msg_f("Forwarding...", 1);
    leftWheel.setPWM(pwm);
    rightWheel.setPWM(pwm);
    clock.sleep(duration);
// end::main_task_1[]
// tag::main_task_2[]
    msg_f("Backwarding...", 1);
    leftWheel.setPWM(-pwm);
    rightWheel.setPWM(-pwm);
    clock.sleep(duration);

    // 左ボタンを長押し、それを捕捉する
    if (ev3_button_is_pressed(LEFT_BUTTON)) {
      break;
    }
  }

  msg_f("Stopped.", 1);
  leftWheel.stop();
  rightWheel.stop();
  while(ev3_button_is_pressed(LEFT_BUTTON)) {
    ;
  }

  ext_tsk();
}
// end::main_task_2[]
