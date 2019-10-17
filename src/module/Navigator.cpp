/**
 *  @file   Navigator.cpp
 *  @brief 直進と後進できるクラス
 *  @author Harada,Oiwane
 *  updated by T.Miyaji
 */

#include "Navigator.h"

Navigator::Navigator(Controller& controller_, int targetBrightness_, double Kp_, double Ki_,
                     double Kd_)
  : distance(),
    controller(controller_),
    pidForSpeed(Kp_, Ki_, Kd_),
    targetBrightness(targetBrightness_)
{
}

void Navigator::setPidGain(double Kp, double Ki, double Kd)
{
  pidForSpeed.setPidGain(Kp, Ki, Kd);
}

void Navigator::move(double specifiedDistance, int pwm, const double pGain)
{
  controller.resetMotorCount();

  // 左車輪の回転量 - 右車輪の回転量
  // 左車輪の方が多く回転していれば、alphaは正となり右車輪にPWM + alphaの操作量が加えられる
  Pid pid(0, pGain);

  if(specifiedDistance < 0) {
    while(hasArrived(specifiedDistance, false)) {
      double alpha = pid.control(controller.getLeftMotorCount() - controller.getRightMotorCount());
      setPwmValue(-std::abs(pwm), -alpha);
      controller.tslpTsk(4);
    }
  } else {
    while(hasArrived(specifiedDistance, true)) {
      double alpha = pid.control(controller.getLeftMotorCount() - controller.getRightMotorCount());
      setPwmValue(std::abs(pwm), -alpha);
      controller.tslpTsk(4);
    }
  }

  controller.stopMotor();
}

void Navigator::moveAtSpecifiedSpeed(double specifiedDistance, int specifiedSpeed)
{
  controller.resetMotorCount();

  SpeedControl speedControl(controller, specifiedSpeed, pidForSpeed.Kp, pidForSpeed.Ki,
                            pidForSpeed.Kd);

  if(specifiedDistance < 0) {
    while(hasArrived(specifiedDistance, false)) {
      double pwm = speedControl.calculateSpeed(specifiedSpeed, pidForSpeed.Kp, pidForSpeed.Ki,
                                               pidForSpeed.Kd);
      setPwmValue(static_cast<int>(-std::abs(pwm)));
      controller.tslpTsk(4);
    }
  } else {
    while(hasArrived(specifiedDistance, true)) {
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
  if(specifiedColor == Color::black || specifiedColor == Color::white) {
    while(specifiedColor != recognizeBlack(controller.getBrightness())) {
      setPwmValue(pwm);
      controller.tslpTsk(4);
    }
  } else {
    // 特定の色まで移動する
    while(controller.determineColor() != specifiedColor) {
      setPwmValue(pwm);
      controller.tslpTsk(4);
    }
  }
  controller.stopMotor();
}

void Navigator::spin(double angle, bool clockwise, int pwm)
{
  // angleの絶対値を取る
  angle = std::abs(angle);
  Rotation rotation;

  controller.resetMotorCount();

  while(rotation.calculate(controller.getLeftMotorCount(), controller.getRightMotorCount())
        < angle) {
    controller.setLeftMotorPwm(clockwise ? pwm : -pwm);
    controller.setRightMotorPwm(clockwise ? -pwm : pwm);
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

Color Navigator::recognizeBlack(int brightness)
{
  return brightness < targetBrightness ? Color::black : Color::white;
}

void Navigator::traceBlackLineToSpecifiedColor(Color specifiedColor, int pwm, double pGain,
                                               bool isLeft)
{
  Pid pid(targetBrightness, pGain);

  // 特定の色まで移動する
  while(controller.determineColor() != specifiedColor) {
    double pidValue = pid.control(controller.getBrightness());
    this->setPwmValue(pwm, (isLeft ? pidValue : -pidValue));
    controller.tslpTsk(4);
  }
  controller.stopMotor();
}