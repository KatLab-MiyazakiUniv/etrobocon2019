/**
 *  @file   Navigator.cpp
 *  @brief 直進と後進できるクラス
 *  @author Harada,Oiwane
 */

#include "Navigator.h"

Navigator::Navigator()
    : distance(), controller()
{
}

Navigator::Navigator(Controller &_controller)
    : distance(), controller(_controller)
{
}

void Navigator::move(int specifiedValue, int pwm)
{
  if (specifiedValue < 0)
  {
    back(specifiedValue, -pwm);
  }else{
    forward(specifiedValue, pwm);
  }
}

void Navigator::forward(int specifiedValue, int pwm)
{
  controller.rightWheel.setPWM(pwm);
  controller.leftWheel.setPWM(pwm);
  int leftAngle = controller.leftWheel.getCount();
  int rightAngle = controller.rightWheel.getCount();
  int goalDistance = specifiedValue + distance.getDistance(leftAngle, rightAngle);

  while (distance.getDistance(leftAngle, rightAngle) < goalDistance)
  {
    controller.rightWheel.setPWM(pwm);
    controller.leftWheel.setPWM(pwm);
    leftAngle = controller.leftWheel.getCount();
    rightAngle = controller.rightWheel.getCount();
  }
  controller.rightWheel.setPWM(0);
  controller.leftWheel.setPWM(0);
}

void Navigator::back(int specifiedValue, int pwm)
{
  controller.rightWheel.setPWM(pwm);
  controller.leftWheel.setPWM(pwm);
  int leftAngle = controller.leftWheel.getCount();
  int rightAngle = controller.rightWheel.getCount();
  int goalDistance = specifiedValue + distance.getDistance(leftAngle, rightAngle);

  while (distance.getDistance(leftAngle, rightAngle) > goalDistance)
  {
    controller.rightWheel.setPWM(pwm);
    controller.leftWheel.setPWM(pwm);
    leftAngle = controller.leftWheel.getCount();
    rightAngle = controller.rightWheel.getCount();
  }
  controller.rightWheel.setPWM(0);
  controller.leftWheel.setPWM(0);
}