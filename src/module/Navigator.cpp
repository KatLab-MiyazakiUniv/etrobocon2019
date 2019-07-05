/**
 *  @file   Navigator.cpp
 *  @brief 直進と後進できるクラス
 *  @author Harada,Oiwane
 *  updated by T.Miyaji
 */

#include "Navigator.h"

Navigator::Navigator(Controller& controller_, double Kp_, double Ki_, double Kd_)
  : distance(), controller(controller_), pidForSpeed(Kp_, Ki_, Kd_)
{
}

void Navigator::setPidGain(double Kp, double Ki, double Kd)
{
  pidForSpeed.setPidGain(Kp, Ki, Kd);
}

void Navigator::move(double specifiedDistance, int pwm, const double pGain)
{
  int leftAngle = controller.getLeftMotorCount();
  int rightAngle = controller.getRightMotorCount();
  double goalDistance = specifiedDistance + distance.getDistance(leftAngle, rightAngle);

  // 左車輪の回転量 - 右車輪の回転量
  // 左車輪の方が多く回転していれば、alphaは正となり右車輪にPWM + alphaの操作量が加えられる
  Pid pid(0, pGain);

  if(specifiedDistance < 0) {
    while(hasArrived(goalDistance, false)) {
      double alpha = pid.control(controller.getLeftMotorCount() - controller.getRightMotorCount());
      setPwmValue(-std::abs(pwm), -alpha);
      controller.tslpTsk(4);
    }
  } else {
    while(hasArrived(goalDistance, true)) {
      double alpha = pid.control(controller.getLeftMotorCount() - controller.getRightMotorCount());
      setPwmValue(std::abs(pwm), -alpha);
      controller.tslpTsk(4);
    }
  }

  controller.stopMotor();
}

void Navigator::moveAtSpecifiedSpeed(double specifiedDistance, int specifiedSpeed)
{
  int leftAngle = controller.getLeftMotorCount();
  int rightAngle = controller.getRightMotorCount();
  double goalDistance = specifiedDistance + distance.getDistance(leftAngle, rightAngle);

  SpeedControl speedControl(controller, specifiedSpeed, pidForSpeed.Kp, pidForSpeed.Ki,
                            pidForSpeed.Kd);

  if(specifiedDistance < 0) {
    while(hasArrived(goalDistance, false)) {
      double pwm = speedControl.calculateSpeed(specifiedSpeed, pidForSpeed.Kp, pidForSpeed.Ki,
                                               pidForSpeed.Kd);
      setPwmValue(static_cast<int>(-std::abs(pwm)));
      controller.tslpTsk(4);
    }
  } else {
    while(hasArrived(goalDistance, true)) {
      double pwm = speedControl.calculateSpeed(specifiedSpeed, pidForSpeed.Kp, pidForSpeed.Ki,
                                               pidForSpeed.Kd);
      setPwmValue(static_cast<int>(std::abs(pwm)));
      controller.tslpTsk(4);
    }
  }
  controller.stopMotor();
}

void Navigator::moveToSpecifiedColor(Color specifiedColor, int pwm)
{
  int r = 0;
  int g = 0;
  int b = 0;

  // カラーセンサからrgb値を取得
  controller.getRawColor(r, g, b);
  // rgb値をhsv値に変換
  controller.convertHsv(r, g, b);

  // 特定の色まで移動する
  while(controller.hsvToColor(controller.getHsv()) != specifiedColor) {
    setPwmValue(pwm);
    // カラーセンサからrgb値を取得
    controller.getRawColor(r, g, b);
    // rgb値をhsv値に変換
    controller.convertHsv(r, g, b);
    controller.tslpTsk(4);
  }
  controller.stopMotor();
}

bool Navigator::hasArrived(double goalDistance, bool isForward)
{
  int leftAngle = controller.getLeftMotorCount();
  int rightAngle = controller.getRightMotorCount();

  // スタート地点からみた現在の距離
  int currentDistance = distance.getDistance(leftAngle, rightAngle);

  if(isForward) {
    return currentDistance <= goalDistance;
  } else {
    return currentDistance >= goalDistance;
  }
}

void Navigator::setPwmValue(int pwm, double alpha)
{
  controller.setRightMotorPwm(pwm + alpha);
  controller.setLeftMotorPwm(pwm - alpha);
}