
#include "Controller.h"

Controller::Controller()
  : touchSensor(PORT_1),
    colorSensor(PORT_3),
    gyroSensor(PORT_4),
    liftMotor(PORT_A),
    rightWheel(PORT_B),
    leftWheel(PORT_C),
    tailMotor(PORT_D)
{
  colorSensor.getRawColor(rgb);
}

void Controller::speakerSetVolume(int volume)
{
  ev3_speaker_set_volume(volume);
}

void Controller::speakerPlayToneFS6(int duration)
{
  ev3_speaker_play_tone(NOTE_FS6, duration);
}

void Controller::ledSetColorOrange()
{
  ev3_led_set_color(LED_ORANGE);
}

void Controller::ledSetColorGreen()
{
  ev3_led_set_color(LED_GREEN);
}

bool Controller::buttonIsPressedBack()
{
  return ev3_button_is_pressed(BACK_BUTTON);
}

bool Controller::buttonIsPressedEnter()
{
  return ev3_button_is_pressed(ENTER_BUTTON);
}

bool Controller::buttonIsPressedUp()
{
  return ev3_button_is_pressed(UP_BUTTON);
}

bool Controller::buttonIsPressedDown()
{
  return ev3_button_is_pressed(DOWN_BUTTON);
}

bool Controller::buttonIsPressedRight()
{
  return ev3_button_is_pressed(RIGHT_BUTTON);
}

bool Controller::buttonIsPressedLeft()
{
  return ev3_button_is_pressed(LEFT_BUTTON);
}

float Controller::getBatteryVoltage()
{
  return ev3_battery_voltage_mV();
}

int Controller::getBrightness()
{
  int r, g, b;
  getRawColor(r, g, b);
  int luminance = 0.298912 * r + 0.586611 * g + 0.114478 * b;
  return luminance;
}

int limitRgbValue(const int value)
{
  constexpr int max = 255;
  constexpr int min = 0;
  if(value >= max) {
    return max;
  } else if(value <= min) {
    return min;
  }
  return value;
}

void Controller::getRawColor(int& r, int& g, int& b)
{
  constexpr int R_MIN = 9;
  constexpr int G_MIN = 6;
  constexpr int B_MIN = 5;
  constexpr int R_MAX = 92;
  constexpr int G_MAX = 100;
  constexpr int B_MAX = 72;

  colorSensor.getRawColor(rgb);
  r = limitRgbValue(static_cast<double>((rgb.r - R_MIN)) * 255 / (R_MAX - R_MIN));
  g = limitRgbValue(static_cast<double>((rgb.g - G_MIN)) * 255 / (G_MAX - G_MIN));
  b = limitRgbValue(static_cast<double>((rgb.b - B_MIN)) * 255 / (B_MAX - B_MIN));
}

Color Controller::hsvToColor(const HsvStatus& status)
{
  if(status.hue <= 87.2984) {
    if(status.value <= 22.9412) {
      return Color::black;
    } else {
      if(status.hue <= 44.0) {
        return Color::red;
      } else {
        if(status.saturation <= 46.6505) {
          return Color::white;
        } else {
          if(status.hue <= 80.6818) {
            return Color::yellow;
          } else {
            return Color::black;
          }
        }
      }
    }
  } else {
    if(status.hue <= 127.9044) {
      if(status.hue <= 104.1311) {
        if(status.saturation <= 52.2948) {
          if(status.value <= 28.8235) {
            return Color::black;
          } else {
            if(status.value <= 64.7059) {
              return Color::white;
            } else {
              if(status.hue <= 99.8571) {
                return Color::white;
              } else {
                return Color::blue;
              }
            }
          }
        } else {
          if(status.hue <= 95.8667) {
            return Color::black;
          } else {
            return Color::green;
          }
        }
      } else {
        if(status.value <= 43.5294) {
          if(status.saturation <= 44.7262) {
            if(status.hue <= 123.5839) {
              return Color::green;
            } else {
              if(status.hue <= 126.2567) {
                return Color::blue;
              } else {
                return Color::green;
              }
            }
          } else {
            return Color::green;
          }
        } else {
          if(status.saturation <= 40.9765) {
            return Color::white;
          } else {
            return Color::blue;
          }
        }
      }
    } else {
      if(status.hue <= 226.8605) {
        if(status.hue <= 130.5115) {
          if(status.hue <= 129.5924) {
            return Color::blue;
          } else {
            return Color::green;
          }
        } else {
          return Color::blue;
        }
      } else {
        return Color::black;
      }
    }
  }
}

Color Controller::getColor()
{
  int r, g, b;
  r = g = b = 0;
  this->getRawColor(r, g, b);
  this->convertHsv(r, g, b);
  return this->hsvToColor(this->getHsv());
}

void Controller::registerColor()
{
  colorBuffer[colorBufferCounter] = getColor();
  colorBufferCounter++;
  if(colorBufferSize <= colorBufferCounter) {
    colorBufferCounter = 0;
  }
}

// 循環バッファ内の色を集計し、もっとも多い色を返す。
Color Controller::determineColor(int colorNum)
{
  int counter[colorNum] = { 0 };
  for(int i = 0; i < colorBufferSize; i++) {
    counter[static_cast<int>(colorBuffer[i])]++;
    this->tslpTsk(4);
  }
  int max = 0;
  for(int i = 1; i < colorNum; i++) {
    if(counter[max] < counter[i]) max = i;
  }

  return static_cast<Color>(max);
}

void Controller::tslpTsk(int time)
{
  tslp_tsk(time);
}

void Controller::lcdFillRect(int x, int y, int h)
{
  ev3_lcd_fill_rect(x, y, EV3_LCD_WIDTH, h, EV3_LCD_WHITE);
}

void Controller::lcdDrawString(const char* str, int x, int y)
{
  ev3_lcd_draw_string(str, x, y);
}

void Controller::lcdSetFont()
{
  ev3_lcd_set_font(EV3_FONT_SMALL);
}

int Controller::getLeftMotorCount()
{
  return leftWheel.getCount();
}

int Controller::getRightMotorCount()
{
  return rightWheel.getCount();
}

int Controller::getArmMotorCount()
{
  return liftMotor.getCount();
}

int Controller::suppressPwmValue(const int value)
{
  if(value > MOTOR_PWM_MAX) {
    return MOTOR_PWM_MAX;
  } else if(value < MOTOR_PWM_MIN) {
    return MOTOR_PWM_MIN;
  }
  return value;
}

void Controller::setLeftMotorPwm(const int pwm)
{
  leftWheel.setPWM(suppressPwmValue(pwm));
}

void Controller::setRightMotorPwm(const int pwm)
{
  rightWheel.setPWM(suppressPwmValue(pwm));
}

void Controller::setArmMotorPwm(const int pwm)
{
  liftMotor.setPWM(suppressPwmValue(pwm));
}

void Controller::convertHsv(int& r, int& g, int& b)
{
  // r,g,bの最大値を求める
  double max = r;
  if(max < g) max = g;
  if(max < b) max = b;

  // r,g,bの最小値を求める
  double min = r;
  if(min > g) min = g;
  if(min > b) min = b;

  // 色相(hue)を求める

  // 3つが同値の時は色相(hue)は０
  if(r == g && r == b) hsv.hue = 0;

  // rが最大値の場合
  else if(max == r) {
    // 0除算を防ぐ処理
    if(max - min != 0) max += 1;
    hsv.hue = 60 * ((g - b) / (max - min));
  }
  // gが最大値の場合
  else if(max == g) {
    // 0除算を防ぐ処理
    if(max - min != 0) max += 1;
    hsv.hue = 60 * ((b - r) / (max - min)) + 120;
  }
  // bが最大値の場合
  else if(max == b) {
    // 0除算を防ぐ処理
    if(max - min != 0) max += 1;
    hsv.hue = 60 * ((r - g) / (max - min)) + 240;
  }
  //求められた色彩(hue)がマイナス値だった場合は360を加算して0～360の範囲に収める
  if(hsv.hue < 0) hsv.hue += 360;

  // 0除算を防ぐ処理
  if(max - min != 0) max += 1;

  // 彩度(saturation)を求める
  hsv.saturation = (max - min) / max * 100;

  // 明度(value)を求める
  hsv.value = max / 255 * 100;
}

HsvStatus Controller::getHsv() const
{
  return hsv;
}  // hsv値を返す

void Controller::resetMotorCount()
{
  leftWheel.reset();
  rightWheel.reset();
}

void Controller::stopMotor()
{
  leftWheel.stop();
  rightWheel.stop();
}

int Controller::getAngleOfRotation()
{
  return gyroSensor.getAngle();
}

void Controller::moveArm(int count, int pwm)
{
  this->resetArmMotorCount();

  if(count >= 0) {
    this->setArmMotorPwm(pwm);
    while(this->getArmMotorCount() < count) {
      this->tslpTsk(4);
    }
  } else {
    this->setArmMotorPwm(-pwm);
    while(this->getArmMotorCount() > count) {
      this->tslpTsk(4);
    }
  }

  this->setArmMotorPwm(0);
}

void Controller::resetArmMotorCount()
{
  liftMotor.reset();
}

void Controller::resetGyroSensor()
{
  // なぜかジャイロセンサーの値が訳の分からない値になることがあるので、0になるまでリセットする
  while(gyroSensor.getAngle() != 0) gyroSensor.reset();
}

void Controller::stopLiftMotor()
{
  this->resetArmMotorCount();
  this->tslpTsk(1500);
}
