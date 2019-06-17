/**
 *  @file   Navigator.h
 *  @brief 直進と後進できるクラス
 *  @author Harada,Oiwane
 *  updated by
 */

#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "Controller.h"
#include "Distance.h"
#include "Pid.h"
#include <cmath>

class Navigator {
 public:
  explicit Navigator(Controller& controller_);
  void move(double specifiedValue, int pwm = 30);
  void moveByPid(double specifiedValue, int pwm = 10, const double pGain = 0.6,
                 const double iGain = 0.0, const double dGain = 0.0);

 private:
  Distance distance;
  Controller& controller;
  void forward(double specifiedValue, double goalDistance, int pwm, double alpha = 0.0);
  void backward(double specifiedValue, double goalDistance, int pwm, double alpha = 0.0);
  bool hasArrived(double goalDistance, bool isForward);
};

#endif
