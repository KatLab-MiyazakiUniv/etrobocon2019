
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
  colorSensor.getRawColor(rgb);
  int luminance = 0.298912 * rgb.r + 0.586611 * rgb.g + 0.114478 * rgb.b;
  return luminance;
}

void Controller::getRawColor(int& r, int& g, int& b)
{
  colorSensor.getRawColor(rgb);
  r = rgb.r;
  g = rgb.g;
  b = rgb.b;
}

Color Controller::hsvToColor(const HsvStatus& status)
{
  if(status.value <= 33.5294){
    if(status.value <= 18.4314){
      return Color::black;
    }else {
      if(status.hue <= 159.5357){
        if(status.hue <= 83.739){
          if(status.hue <= 40.8904){
            return Color::black;
          }else {
            return Color::yellow;
          }
        }else {
          return Color::green;
        }
      }else {
        if(status.value <= 32.9412){
          return Color::blue;
        }else {
          if(status.hue <= 299.6104){
            return Color::black;
          }else {
            return Color::red;
          }
        }
      }
    }
  }else {
    if(status.value <= 45.2941){
      if(status.hue <= 263.0811){
        if(status.hue <= 32.8235){
          return Color::red;
        }else {
          if(status.hue <= 76.7547){
            if(status.hue <= 44.8367){
              if(status.hue <= 40.5263){
                return Color::yellow;
              }else {
                return Color::red;
              }
            }else {
              return Color::yellow;
            }
          }else {
            if(status.value <= 40.1961){
              if(status.value <= 35.4902){
                return Color::green;
              }else {
                return Color::blue;
              }
            }else {
              return Color::white;
            }
          }
        }
      }else {
        return Color::red;
      }
    }else {
      if(status.hue <= 283.6016){
        if(status.hue <= 99.2199){
          if(status.value <= 51.1765){
            return Color::yellow;
          }else {
            return Color::red;
          }
        }else {
          return Color::white;
        }
      }else {
        return Color::red;
      }
    }
  }
}

Color Controller::determineColor(const HsvStatus& status)
{
  int white = 0, black = 0, red = 0, green = 0, blue = 0, yellow = 0;
  int determinNum = 3;
  while (1) {
    Color color = this->hsvToColor(status);
    if (color == Color::white) {
      if(white<determinNum){
        white += 1;
      }else{
        return Color::white;
      }
    }
    else if (color == Color::black) {
      if(black<determinNum){
        black += 1;
      }else{
        return Color::black;
      }
    }
    else if (color == Color::red) {
      if(red<determinNum){
        red += 1;
      }else{
        return Color::red;
      }
    }
    else if (color == Color::green) {
      if(green<determinNum){
        green += 1;
      }else{
        return Color::green;
      }
    }
    else if (color == Color::blue) {
      if(blue<determinNum){
        blue += 1;
      }else{
        return Color::blue;
      }
    }
    else if (color == Color::yellow) {
      if(yellow<determinNum){
        yellow += 1;
      }else{
        return Color::yellow;
      }
    }
  }
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
  int angle = gyroSensor.getAngle();
  //角度を[0-360]の範囲で表す,
  //右手系(反時計回り)が正である
  return Controller::limitAngle(angle);
}

int Controller::limitAngle(int angle)
{
  angle = angle % 360;
  if(angle < 0) {
    angle = 360 + angle;
    angle = limitAngle(angle);
  }
  return angle;
}