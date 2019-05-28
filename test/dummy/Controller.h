#ifndef __CONTROLLER__
#define __CONTROLLER__

#include <cstdint>
#include <cstdlib>
#include <iostream>

class Motor {
 public:
  double count = 0.0;
  int getCount() { return static_cast<int>(count); };
  void setPWM(int pwm)
  {
    count += pwm * 0.05;
    // std::cout << count << std::endl;
  };
  void stop(){};
  void reset(){};
  void setBrake(bool isBrake){};
};

class Clock {
 public:
  void sleep(int time){};
};

class TouchSensor {
 public:
  bool isPressed() { return false; }
};

class ColorSensor {
 public:
  int getBrightness() { return brightness; }
  int brightness = 0;
};

class Controller {
 public:
  Clock clock;
  Motor rightWheel;
  Motor leftWheel;
  Motor liftMotor;
  TouchSensor touchSensor;
  ColorSensor colorSensor;

  // モータ入力電圧の最大値
  static constexpr int MOTOR_PWM_MAX = 100;
  // モータ入力電圧の最小値
  static constexpr int MOTOR_PWM_MIN = -100;

  int noteFs6 = 0;
  int noteFs4 = 0;
  Controller() { mock_r = mock_g = mock_b = 0; }
  void speakerSetVolume(int volume){};
  void ledSetColorOrange(){};
  void ledSetColorGreen(){};
  int getBrightness() { return brightness; };
  void speakerPlayTone(int frequency, int duration){};
  bool buttonIsPressedBack()
  {
    counter++;
    if(counter >= countLimit) {
      return true;
    }
    return false;
  };
  void getRawColor(std::uint16_t& r, std::uint16_t& g, std::uint16_t& b)
  {
    r = mock_r;
    g = mock_g;
    b = mock_b;

    return;
  };
  bool buttonIsPressedUp() { return false; };
  bool buttonIsPressedDown() { return false; };
  bool buttonIsPressedRight() { return false; };
  bool buttonIsPressedLeft() { return false; };
  bool buttonIsPressedEnter()
  {
    static int counter = 0;
    counter++;
    if(counter >= 10) {
      return true;
    }
    return false;
  };
  void tslpTsk(int time)
  {
    exitCounter++;
    if(exitCounter > exitCountLimit) std::exit(1);
  };  // 4msec周期起動
  void printDisplay(int row, const char* format, ...){};
  int countLimit = 100;
  int counter = 0;
  int exitCounter = 0;
  int exitCountLimit = 1000;
  int brightness = 0;
  std::uint16_t mock_r, mock_g, mock_b;
  void setMockRgb(std::uint16_t r, std::uint16_t g, std::uint16_t b)
  {
    mock_r = r;
    mock_g = g;
    mock_b = b;
  }
  static void lcdSetFont(){}
  static void lcdFillRect(int, int, int){}
  static void lcdDrawString(char*, int, int){}
};
#endif