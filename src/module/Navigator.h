/**
 *  @file   Navigator.h
 *  @brief 直進と後進できるクラス
 *  @author Harada,Oiwane
 */

#ifndef Navigator_H
#define Navigator_H

#include "Controller.h"
#include "Distance.h"

class Navigator
{
public:
   Navigator();
   Navigator(Controller &_controller);
   void move(int specifiedValue, int pwm = 30);

private:
   Distance distance;
   Controller controller;
   void forward(int specifiedValue, int pwm);
   void back(int specifiedValue, int pwm);
};

#endif