#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <array>

unsigned struct HsvStatus {
  //色相 範囲(0~360)
  double hue;
  //彩度 範囲(0~100)
  double saturation;
  //明度 範囲(0~100)
  double value;
};

struct rgb_raw_t {
  unsigned int r;
  unsigned int g;
  unsigned int b;
  rgb_raw_t() : r(0), g(0), b(0) {}
};

enum class Color { black, red, green, blue, yellow, white, none };

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
  void getRawColor(rgb_raw_t& rgb)
  {
    rgb.r = 1;
    rgb.g = 1;
    rgb.b = 1;
  }
  int brightness = 0;
};

class GyroSensor {
 public:
  int getAngle() { return angle; }
  void reset(){};
  int angle = 0;
};

class Controller {
 private:
  Motor rightWheel;
  Motor leftWheel;
  Motor liftMotor;

 public:
  HsvStatus hsv;
  Clock clock;
  TouchSensor touchSensor;
  ColorSensor colorSensor;
  GyroSensor gyroSensor;

  // モータ入力電圧の最大値
  static constexpr int MOTOR_PWM_MAX = 100;
  // モータ入力電圧の最小値
  static constexpr int MOTOR_PWM_MIN = -100;
  static constexpr int colorBufferSize = 10;
  static std::array<Color, colorBufferSize> colorBuffer;
  static int colorBufferCounter;

  int noteFs6 = 0;
  int noteFs4 = 0;
  Controller() { mock_r = mock_g = mock_b = 0; }
  void speakerSetVolume(int volume){};
  void ledSetColorOrange(){};
  void ledSetColorGreen(){};
  int getBrightness() { return brightness; };
  void speakerPlayToneFS6(int duration){};
  bool buttonIsPressedBack()
  {
    counter++;
    if(counter >= countLimit) {
      return true;
    }
    return false;
  };
  void getRawColor(int& r, int& g, int& b)
  {
    r = mock_r;
    g = mock_g;
    b = mock_b;

    return;
  };

  void convertHsv(int& r, int& g, int& b)
  {
    // r,g,bの最大値を求める
    double max = r;
    if(max < g) max = g;
    if(max < b) max = b;

    // 明度(value)を求める
    hsv.value = max / 255 * 100;

    if(hsv.value == 0) {
      hsv.hue = 0;
      hsv.saturation = 0;
      return;
    }

    // r,g,bの最小値を求める
    double min = r;
    if(min > g) min = g;
    if(min > b) min = b;

    double diff = max - min;

    // 彩度(saturation)を求める
    hsv.saturation = diff / max * 100.0;

    // 色相(hue)を求める
    if(r == g && r == b)
      hsv.hue = 0;
    else if(max == r)
      hsv.hue = 60.0 * ((g - b) / diff);
    else if(max == g)
      hsv.hue = 60.0 * ((b - r) / diff) + 120.0;
    else if(max == b)
      hsv.hue = 60.0 * ((r - g) / diff) + 240.0;

    if(hsv.hue < 0.0) hsv.hue += 360.0;
  }

  HsvStatus getHsv() { return hsv; }  // hsv値を返す

  Color hsvToColor(const HsvStatus& status)
  {
    if(status.saturation <= 25.388) {
      if(status.value <= 69.841) {
        return Color::black;
      } else {
        return Color::white;
      }
    } else {
      if(status.value <= 29.037) {
        return Color::black;
      } else {
        if(status.hue <= 125.776) {
          if(status.hue <= 63.737) {
            if(status.hue <= 49.617) {
              if(status.hue <= 22.134) {
                return Color::red;
              } else {
                return Color::yellow;
              }
            } else {
              return Color::yellow;
            }
          } else {
            return Color::green;
          }
        } else {
          if(status.hue <= 312.573) {
            if(status.saturation <= 79.553) {
              if(status.value <= 57.333) {
                return Color::green;
              } else {
                return Color::blue;
              }
            } else {
              return Color::blue;
            }
          } else {
            return Color::red;
          }
        }
      }
    }
  }

  bool buttonIsPressedUp() { return false; };
  bool buttonIsPressedDown() { return false; };

  bool pushRight = false;
  bool buttonIsPressedRight()
  {
    if(pushRight) {
      pushRight = false;
      return true;
    }
    return false;
  };

  bool pushLeft = false;
  bool buttonIsPressedLeft()
  {
    if(pushLeft) {
      pushLeft = false;
      return true;
    }
    return false;
  };

  bool buttonIsPressedEnter()
  {
    static int counter = 0;
    counter++;
    if(counter >= 10) {
      counter = 0;
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
  static void lcdSetFont() {}
  static void lcdFillRect(int, int, int) {}
  static void lcdDrawString(char* msg, int, int)
  {
    // std::cout << "[          ] " << msg << std::endl;
  }

  int getLeftMotorCount() { return leftWheel.getCount(); };
  int getRightMotorCount() { return rightWheel.getCount(); };
  int getArmMotorCount() { return liftMotor.getCount(); };
  void setLeftMotorPwm(const int pwm) { leftWheel.setPWM(suppressPwmValue(pwm)); };
  void setRightMotorPwm(const int pwm) { rightWheel.setPWM(suppressPwmValue(pwm)); };
  void setArmMotorPwm(const int pwm) { liftMotor.setPWM(suppressPwmValue(pwm)); };
  void resetMotorCount()
  {
    leftWheel.reset();
    rightWheel.reset();
  }
  void stopMotor()
  {
    leftWheel.stop();
    rightWheel.stop();
  }
  static int suppressPwmValue(const int value)
  {
    if(value > MOTOR_PWM_MAX) {
      return MOTOR_PWM_MAX;
    } else if(value < MOTOR_PWM_MIN) {
      return MOTOR_PWM_MIN;
    }
    return value;
  };
  int getAngleOfRotation() { return gyroSensor.getAngle(); }
  void moveArm(int count, int pwm = 10)
  {
    this->resetArmMotorCount();

    if(count >= 0) {
      while(this->getArmMotorCount() < count) {
        this->setArmMotorPwm(pwm);
        this->tslpTsk(4);
      }
    } else {
      while(this->getArmMotorCount() > count) {
        this->setArmMotorPwm(-pwm);
        this->tslpTsk(4);
      }
    }

    this->setArmMotorPwm(0);
  }
  void resetArmMotorCount() { liftMotor.reset(); }

  Color getColor()
  {
    int r, g, b;
    r = g = b = 0;
    this->getRawColor(r, g, b);
    this->convertHsv(r, g, b);
    return this->hsvToColor(this->getHsv());
  }

  void registerColor()
  {
    colorBuffer[colorBufferCounter] = getColor();
    colorBufferCounter++;
    if(colorBufferSize <= colorBufferCounter) {
      colorBufferCounter = 0;
    }
  }

  void steer(int power = 10, int turnRatio = 10)
  {
    this->steer(int power, int turnRatio);
  }
  
  void resetGyroSensor()
  {
    // なぜかジャイロセンサーの値が訳の分からない値になることがあるので、0になるまでリセットする
    while(gyroSensor.getAngle() != 0) gyroSensor.reset();
  }

  void stopLiftMotor() { this->resetArmMotorCount(); }

  rgb_raw_t standardWhite;
  void setStandardWhite(const rgb_raw_t& rgb) { standardWhite = rgb; }

  rgb_raw_t standardBlack;
  void setStandardBlack(const rgb_raw_t& rgb) { standardBlack = rgb; }
};
#endif
