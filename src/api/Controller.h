#ifndef __CONTROLLER__
#define __CONTROLLER__

#include "ev3api.h"

#include "Clock.h"
#include "ColorSensor.h"
#include "Motor.h"
#include "TouchSensor.h"

/*
 * touch_sensor = EV3_PORT_1;
 * sonar_sensor = EV3_PORT_2;
 * color_sensor = EV3_PORT_3;
 * gyro_sensor  = EV3_PORT_4;
 *
 * left_motor   = EV3_PORT_C;
 * right_motor  = EV3_PORT_B;
 * lift_motor   = EV3_PORT_A;
 * tail_motor   = EV3_PORT_D;
 */

using namespace ev3api;

class Controller {
 public:
  Controller()
      : touchSensor(PORT_1),
        colorSensor(PORT_3),
        liftMotor(PORT_A),
        rightWheel(PORT_B),
        leftWheel(PORT_C),
        tailMotor(PORT_D) {}
  int noteFs6 = NOTE_FS6;
  int noteFs4 = NOTE_FS4;
  TouchSensor touchSensor;
  ColorSensor colorSensor;
  Motor liftMotor;
  Motor rightWheel;
  Motor leftWheel;
  Motor tailMotor;
  Clock clock;
  void speakerSetVolume(int volume);
  void ledSetColorOrange();
  void ledSetColorGreen();
  int getBrightness();
  static void speakerPlayTone(int frequency, int duration);
  bool buttonIsPressedBack();
  bool buttonIsPressedUp();
  bool buttonIsPressedDown();
  bool buttonIsPressedRight();
  bool buttonIsPressedLeft();
  bool buttonIsPressedEnter();
  static float measureBatteryVoltage();
  static void tslpTsk(int time);  // 4msec周期起動
  void getRawColor(int& r, int& g, int& b);
  static void lcdFillRect(int x, int y, int h);
  static void lcdDrawString(const char* str, int x, int y);
  static void lcdSetFont();

 private:
  rgb_raw_t rgb;
};
#endif