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
  colorSensor.getRawColor(standardWhite);
  colorSensor.getRawColor(standardBlack);
}

int Controller::getVolt()
{
  return ev3_battery_voltage_mV();
}

int Controller::getAmp()
{
  return ev3_battery_current_mA();
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
  rgb_raw_t rgb;
  colorSensor.getRawColor(rgb);
  r = limitRgbValue(static_cast<double>((rgb.r - standardBlack.r)) * 255
                    / (standardWhite.r - standardBlack.r));
  g = limitRgbValue(static_cast<double>((rgb.g - standardBlack.g)) * 255
                    / (standardWhite.g - standardBlack.g));
  b = limitRgbValue(static_cast<double>((rgb.b - standardBlack.b)) * 255
                    / (standardWhite.b - standardBlack.b));
}

Color Controller::hsvToColor(const HsvStatus& status)
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

Color Controller::getColor()
{
  int r, g, b;
  r = g = b = 0;
  this->getRawColor(r, g, b);
  this->convertHsv(r, g, b);
  return this->hsvToColor(this->getHsv());
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

void Controller::setStandardWhite(const rgb_raw_t& rgb)
{
  standardWhite = rgb;
}

void Controller::setStandardBlack(const rgb_raw_t& rgb)
{
  standardBlack = rgb;
}

void Controller::convertHsv(int& r, int& g, int& b)
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

void Controller::steer(int power, int turnRatio)
{
  ev3_motor_steer(EV3_PORT_C, EV3_PORT_B, power, turnRatio);
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
