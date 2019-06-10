/**
 *  @file   Navigator.cpp
 *  @brief 直進と後進できるクラス
 *  @author Harada,Oiwane
 */

#include"Navigator.h"

Navigator::Navigator()
    : distance(), controller()
{
}

Navigator::Navigator(Controller& _controller)
    : distance(), controller(_controller)
{
}

void Navigator::move(int specifiedValue, int pwm){
  if(specifiedValue < 0){
    pwm *= -1;
  }
  controller.rightWheel.setPWM(pwm);
  controller.leftWheel.setPWM(pwm);
  while(std::abs(distance.getDistance()) > std::abs(specifiedValue) )
}