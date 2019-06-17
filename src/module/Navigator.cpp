/**
 *  @file   Navigator.cpp
 *  @brief 直進と後進できるクラス
 *  @author Harada,Oiwane
 *  updated by T.Miyaji
 */

#include "Navigator.h"

Navigator::Navigator(Controller& controller_) : distance(), controller(controller_) {}

void Navigator::move(double specifiedValue, int pwm)
{
  int leftAngle = controller.getLeftMotorCount();
  int rightAngle = controller.getRightMotorCount();
  double goalDistance = specifiedValue + distance.getDistance(leftAngle, rightAngle);

  if(specifiedValue < 0) {
    backward(specifiedValue, goalDistance, -std::abs(pwm));
  } else {
    forward(specifiedValue, goalDistance, std::abs(pwm));
  }

  controller.setRightMotorPwm(0);
  controller.setLeftMotorPwm(0);
}

void Navigator::moveByPid(double specifiedValue, int pwm, const double pGain, const double iGain,
                          const double dGain)
{
  int leftAngle = controller.getLeftMotorCount();
  int rightAngle = controller.getRightMotorCount();
  double goalDistance = specifiedValue + distance.getDistance(leftAngle, rightAngle);

  // 右車輪の回転量 - 左車輪の回転量
  // 右車輪の方が多く回転していれば、alphaは正となり左車輪にPWM + alphaの操作量が加えられる
  Pid pid(pGain, iGain, dGain);
  double alpha = pid.control(rightAngle - leftAngle);

  if(specifiedValue < 0) {
    backward(specifiedValue, goalDistance, -std::abs(pwm), alpha);
  } else {
    forward(specifiedValue, goalDistance, std::abs(pwm), alpha);
  }

  controller.setRightMotorPwm(0);
  controller.setLeftMotorPwm(0);
}

void Navigator::forward(double specifiedValue, double goalDistance, int pwm, double alpha)
{
  while(hasArrived(goalDistance, true)) {
    controller.setRightMotorPwm(pwm + alpha);
    controller.setLeftMotorPwm(pwm - alpha);
    controller.tslpTsk(4);
  }
}

void Navigator::backward(double specifiedValue, double goalDistance, int pwm, double alpha)
{
  while(hasArrived(goalDistance, false)) {
    controller.setRightMotorPwm(pwm + alpha);
    controller.setLeftMotorPwm(pwm - alpha);
    controller.tslpTsk(4);
  }
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
