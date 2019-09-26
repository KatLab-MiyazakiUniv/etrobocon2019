#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

unsigned struct HsvStatus {
  //色相 範囲(0~360)
  double hue;
  //彩度 範囲(0~100)
  double saturation;
  //明度 範囲(0~100)
  double value;
};

enum class Color { black, red, green, blue, yellow, white };

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

class GyroSensor {
 public:
  int getAngle() { return angle; }
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
    double max = r;
    if(max < g) {
      max = g;
    }
    if(max < b) {
      max = b;
    }
    double min = r;
    if(min > g) {
      min = g;
    }
    if(min > b) {
      min = b;
    }

    // 色相(hue)を求める
    if(r == g && r == b) {
      hsv.hue = 0;
    }

    else if(max == r) {
      hsv.hue = 60 * ((g - b) / (max - min));
    }

    else if(max == g) {
      hsv.hue = 60 * ((b - r) / (max - min)) + 120;
    }

    else if(max == b) {
      hsv.hue = 60 * ((r - g) / (max - min)) + 240;
    }

    if(hsv.hue < 0) {
      hsv.hue += 360;
    }

    // 彩度(saturation)を求める
    hsv.saturation = (max - min) / max * 100;

    // 明度(value)を求める
    hsv.value = max / 255 * 100;
  }

  HsvStatus getHsv() { return hsv; }  // hsv値を返す

  Color hsvToColor(HsvStatus hsv)
  {
    // 白黒の識別
    if(hsv.value < 13.0) {
      return Color::black;
    } else if(hsv.value > 50.0) {
      return Color::white;
    }

    // 赤緑青黃の識別
    if(hsv.hue < 30) {
      return Color::red;
    } else if(hsv.hue < 80.0) {
      return Color::yellow;
    } else if(hsv.hue < 160.0) {
      return Color::green;
    } else if(hsv.hue < 300.0) {
      return Color::blue;
    } else {
      return Color::red;
    }
  }

  Color ditermineColor(HsvStatus hsv) { return this->hsvToColor(hsv); }

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
  int getAngleOfRotation()
  {
    int angle = gyroSensor.getAngle();

    return limitAngle(angle);
  }
  int limitAngle(int angle)
  {
    angle = angle % 360;
    if(angle < 0) {
      angle = 360 + angle;
      angle = limitAngle(angle);
    }
    return angle;
  }
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
};
#endif
