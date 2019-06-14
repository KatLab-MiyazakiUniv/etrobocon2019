/**
 *  @file   Navigator.h
 *  @brief 直進と後進できるクラス
 *  @author Harada,Oiwane
 */

#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "Controller.h"
#include "Distance.h"
#include <cmath>

class Navigator {
 public:
  explicit Navigator(Controller& controller_);
  void move(int specifiedValue, int pwm = 30);

 private:
  Distance distance;
  Controller& controller;
  void forward(int specifiedValue, int pwm, int goalDistance);
  void backward(int specifiedValue, int pwm, int goalDistance);
  bool hasArrived(int goalDistance, bool isForward);
};

#endif