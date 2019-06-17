
#include "Controller.h"

Controller::Controller()
    : touchSensor(PORT_1),
      colorSensor(PORT_3),
      liftMotor(PORT_A),
      rightWheel(PORT_B),
      leftWheel(PORT_C),
      tailMotor(PORT_D) {
  colorSensor.getRawColor(rgb);
}

void Controller::speakerSetVolume(int volume) {
  ev3_speaker_set_volume(volume);
}

void Controller::speakerPlayToneFS6(int duration) {
  ev3_speaker_play_tone(NOTE_FS6, duration);
}

void Controller::ledSetColorOrange() { ev3_led_set_color(LED_ORANGE); }

void Controller::ledSetColorGreen() { ev3_led_set_color(LED_GREEN); }

bool Controller::buttonIsPressedBack() {
  return ev3_button_is_pressed(BACK_BUTTON);
}

bool Controller::buttonIsPressedEnter() {
  return ev3_button_is_pressed(ENTER_BUTTON);
}

bool Controller::buttonIsPressedUp() {
  return ev3_button_is_pressed(UP_BUTTON);
}

bool Controller::buttonIsPressedDown() {
  return ev3_button_is_pressed(DOWN_BUTTON);
}

bool Controller::buttonIsPressedRight() {
  return ev3_button_is_pressed(RIGHT_BUTTON);
}

bool Controller::buttonIsPressedLeft() {
  return ev3_button_is_pressed(LEFT_BUTTON);
}

float Controller::getBatteryVoltage() { return ev3_battery_voltage_mV(); }

int Controller::getBrightness() {
  colorSensor.getRawColor(rgb);
  int luminance = 0.298912 * rgb.r + 0.586611 * rgb.g + 0.114478 * rgb.b;
  return luminance;
}

void Controller::getRawColor(int& r, int& g, int& b) {
  colorSensor.getRawColor(rgb);
  r = rgb.r;
  g = rgb.g;
  b = rgb.b;
}

void Controller::tslpTsk(int time) { tslp_tsk(time); }

void Controller::lcdFillRect(int x, int y, int h) {
  ev3_lcd_fill_rect(x, y, EV3_LCD_WIDTH, h, EV3_LCD_WHITE);
}

void Controller::lcdDrawString(const char* str, int x, int y) {
  ev3_lcd_draw_string(str, x, y);
}

void Controller::lcdSetFont() { ev3_lcd_set_font(EV3_FONT_SMALL); }

int Controller::getLeftMotorCount(){
  return leftWheel.getCount();
}

int Controller::getRightMotorCount(){
  return rightWheel.getCount();
}

int Controller::suppressPwmValue(const int value){
  if(value > MOTOR_PWM_MAX){
    return MOTOR_PWM_MAX;
  }else if(value < MOTOR_PWM_MIN){
    return MOTOR_PWM_MIN;
  }
  return value;
}

void Controller::setLeftMotorPwm(const int pwm){
  leftWheel.setPWM(suppressPwmValue(pwm));
}

void Controller::setRightMotorPwm(const int pwm){
  rightWheel.setPWM(suppressPwmValue(pwm));
}
