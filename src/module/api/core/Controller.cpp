
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
  if(status.value <= 17.059) {
    if(status.saturation <= 79.398) {
      if(status.value <= 11.765)
        return Color::black;
      else if(status.saturation <= 54.688)
        return Color::blue;
      else
        return Color::black;
    } else
      return Color::blue;
  } else if(status.saturation <= 18.792) {
    if(status.hue <= 76.528)
      return Color::yellow;
    else if(status.saturation <= 13.469)
      return Color::white;
    else if(status.saturation <= 13.513) {
      if(status.hue <= 170.625)
        return Color::white;
      else
        return Color::green;
    } else if(status.hue <= 157.368) {
      if(status.hue <= 151.215)
        return Color::white;
      else
        return Color::green;
    } else
      return Color::white;
  } else if(status.hue <= 71.434) {
    if(status.hue <= 38.097)
      return Color::red;
    else if(status.hue <= 44.112) {
      if(status.hue <= 42.224)
        return Color::yellow;
      else
        return Color::red;
    } else
      return Color::yellow;
  } else if(status.hue <= 210.738) {
    if(status.value <= 64.51) {
      if(status.hue <= 91.903)
        return Color::black;
      else if(status.hue <= 169.465)
        return Color::green;
      else if(status.saturation <= 35.261)
        return Color::green;
      else
        return Color::blue;
    } else
      return Color::white;
  } else if(status.hue <= 292.5) {
    if(status.saturation <= 42.325) {
      if(status.hue <= 228.833)
        return Color::blue;
      else
        return Color::black;
    } else
      return Color::blue;
  } else
    return Color::red;
}

// 5(determine)回色検出を行い、最も検出された回数が多い色(白以外)を返す関数である
Color Controller::determineColor(int determineNum, int colorNum)
{
  int counter[colorNum] = { 0 };
  int r = 0;
  int g = 0;
  int b = 0;
  for(int i = 0; i < determineNum; i++) {
    this->getRawColor(r, g, b);
    this->convertHsv(r, g, b);
    Color color = this->hsvToColor(this->getHsv());
    counter[static_cast<int>(color)]++;
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