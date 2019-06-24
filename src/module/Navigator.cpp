/**
 *  @file   Navigator.cpp
 *  @brief 直進と後進できるクラス
 *  @author Harada,Oiwane
 *  updated by T.Miyaji
 */

#include "Navigator.h"

Navigator::Navigator(Controller& controller_, SpeedControl& speedControl_) : distance(), controller(controller_), speedControl(speedControl_) {}

void Navigator::move(double specifiedDistance, int pwm)
{
  int leftAngle = controller.getLeftMotorCount();
  int rightAngle = controller.getRightMotorCount();
  double goalDistance = specifiedDistance + distance.getDistance(leftAngle, rightAngle);

  if(specifiedDistance < 0) {
    while(hasArrived(goalDistance, false)) {
      setPwmValue(-std::abs(pwm));
    }
  } else {
    while(hasArrived(goalDistance, true)) {
      setPwmValue(std::abs(pwm));
    }
  }

  controller.setRightMotorPwm(0);
  controller.setLeftMotorPwm(0);
}

void Navigator::moveBySpeed(double specifiedDistance, int specifiedSpeed)
{
  int leftAngle = controller.getLeftMotorCount();
  int rightAngle = controller.getRightMotorCount();
  double goalDistance = specifiedDistance + distance.getDistance(leftAngle, rightAngle);

  if(specifiedDistance < 0){
    while(hasArrived(goalDistance, false)){
      double pwm = speedControl.calculateSpeed(specifiedSpeed, 0.60, 0.05, 0.04);
      setPwmValue(-std::abs(static_cast<int>(pwm)));
    }
  } else {
    while(hasArrived(goalDistance, true)){
      double pwm = speedControl.calculateSpeed(specifiedSpeed, 0.60, 0.05, 0.04);
      setPwmValue(std::abs(static_cast<int>(pwm)));
    }
  }
  controller.setRightMotorPwm(0);
  controller.setLeftMotorPwm(0);
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
      setPwmValue(-std::abs(pwm), alpha);
    }
  } else {
    while(hasArrived(goalDistance, true)) {
      setPwmValue(std::abs(pwm), alpha);
    }
  }

  controller.setRightMotorPwm(0);
  controller.setLeftMotorPwm(0);
}

void Navigator::moveByPidAndSpeed(double specifiedDistance, int specifiedSpeed, const double pGain, const double iGain,
                          const double dGain)
{
  int leftAngle = controller.getLeftMotorCount();
  int rightAngle = controller.getRightMotorCount();
  double goalDistance = specifiedDistance + distance.getDistance(leftAngle, rightAngle);

  // 右車輪の回転量 - 左車輪の回転量
  // 右車輪の方が多く回転していれば、alphaは正となり左車輪にPWM + alphaの操作量が加えられる
  Pid pid(pGain, iGain, dGain);
  double alpha = pid.control(rightAngle - leftAngle);

  if(specifiedDistance < 0){
    while(hasArrived(goalDistance, false)){
      double pwm = speedControl.calculateSpeed(specifiedSpeed, 0.60, 0.05, 0.04);
      setPwmValue(-std::abs(static_cast<int>(pwm)), alpha);
    }
  } else {
    while(hasArrived(goalDistance, true)){
      double pwm = speedControl.calculateSpeed(specifiedSpeed, 0.60, 0.05, 0.04);
      setPwmValue(std::abs(static_cast<int>(pwm)), alpha);
    }
  }

  controller.setRightMotorPwm(0);
  controller.setLeftMotorPwm(0);
}

// void Navigator::forward(double specifiedDistance, double goalDistance, int pwm, double alpha)
// {
//   Logger logger;
//   while(hasArrived(goalDistance, true)) {
//     logger.write("%d\n", pwm);
//     controller.setRightMotorPwm(pwm + alpha);
//     controller.setLeftMotorPwm(pwm - alpha);
//     controller.tslpTsk(4);
//   }
//   logger.write("\n");
// }

// void Navigator::backward(double specifiedDistance, double goalDistance, int pwm, double alpha)
// {
//   while(hasArrived(goalDistance, false)) {
//     controller.setRightMotorPwm(pwm + alpha);
//     controller.setLeftMotorPwm(pwm - alpha);
//     controller.tslpTsk(4);
//   }
// }

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