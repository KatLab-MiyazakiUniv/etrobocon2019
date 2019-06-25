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

void Navigator::setPidGain(double Kp_, double Ki_, double Kd_)
{
  pidForSpeed.Kp = Kp_;
  pidForSpeed.Ki = Ki_;
  pidForSpeed.Kd = Kd_;
}

void Navigator::move(double specifiedDistance, int pwm)
{
  int leftAngle = controller.getLeftMotorCount();
  int rightAngle = controller.getRightMotorCount();
  double goalDistance = specifiedDistance + distance.getDistance(leftAngle, rightAngle);

  if(specifiedDistance < 0) {
    while(hasArrived(goalDistance, false)) {
      setPwmValue(static_cast<int>(-std::abs(pwm)));
    }
  } else {
    while(hasArrived(goalDistance, true)) {
      setPwmValue(static_cast<int>(std::abs(pwm)));
    }
  }

  controller.stopMotor();
}

void Navigator::moveAtSpecifiedSpeed(double specifiedDistance, int specifiedSpeed)
{
  int leftAngle = controller.getLeftMotorCount();
  int rightAngle = controller.getRightMotorCount();
  double goalDistance = specifiedDistance + distance.getDistance(leftAngle, rightAngle);

  SpeedControl speedControl(controller, specifiedSpeed, pidForSpeed.Kp, pidForSpeed.Ki, pidForSpeed.Kd);

  if(specifiedDistance < 0) {
    while(hasArrived(goalDistance, false)) {
      double pwm = speedControl.calculateSpeed(specifiedSpeed, pidForSpeed.Kp, pidForSpeed.Ki, pidForSpeed.Kd);
      setPwmValue(static_cast<int>(-std::abs(pwm)));
    }
  } else {
    while(hasArrived(goalDistance, true)) {
      double pwm = speedControl.calculateSpeed(specifiedSpeed, pidForSpeed.Kp, pidForSpeed.Ki, pidForSpeed.Kd);
      setPwmValue(static_cast<int>(std::abs(pwm)));
    }
  }
  controller.stopMotor();
}

void Navigator::moveByPid(double specifiedDistance, int pwm, const double pGain, const double iGain,
                          const double dGain)
{
  int leftAngle = controller.getLeftMotorCount();
  int rightAngle = controller.getRightMotorCount();
  double goalDistance = specifiedDistance + distance.getDistance(leftAngle, rightAngle);

  // 右車輪の回転量 - 左車輪の回転量
  // 右車輪の方が多く回転していれば、alphaは正となり左車輪にPWM + alphaの操作量が加えられる
  Pid pid(pGain, iGain, dGain);
  double alpha = pid.control(rightAngle - leftAngle);

  if(specifiedDistance < 0) {
    while(hasArrived(goalDistance, false)) {
      setPwmValue(static_cast<int>(-std::abs(pwm)), alpha);
    }
  } else {
    while(hasArrived(goalDistance, true)) {
      setPwmValue(static_cast<int>(std::abs(pwm)), alpha);
    }
  }

  controller.stopMotor();
}

void Navigator::moveAtSpecifiedSpeedByPid(double specifiedDistance, int specifiedSpeed,
                                          const double pGain, const double iGain,
                                          const double dGain)
{
  int leftAngle = controller.getLeftMotorCount();
  int rightAngle = controller.getRightMotorCount();
  double goalDistance = specifiedDistance + distance.getDistance(leftAngle, rightAngle);

  // 右車輪の回転量 - 左車輪の回転量
  // 右車輪の方が多く回転していれば、alphaは正となり左車輪にPWM + alphaの操作量が加えられる
  Pid pid(pGain, iGain, dGain);
  double alpha = pid.control(rightAngle - leftAngle);

  SpeedControl speedControl(controller, specifiedSpeed, pidForSpeed.Kp, pidForSpeed.Ki, pidForSpeed.Kd);

  if(specifiedDistance < 0) {
    while(hasArrived(goalDistance, false)) {
      double pwm = speedControl.calculateSpeed(specifiedSpeed, pidForSpeed.Kp, pidForSpeed.Ki, pidForSpeed.Kd);
      setPwmValue(static_cast<int>(-std::abs(pwm)), alpha);
    }
  } else {
    while(hasArrived(goalDistance, true)) {
      double pwm = speedControl.calculateSpeed(specifiedSpeed, pidForSpeed.Kp, pidForSpeed.Ki, pidForSpeed.Kd);
      setPwmValue(static_cast<int>(std::abs(pwm)), alpha);
    }
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
  controller.tslpTsk(4);
}