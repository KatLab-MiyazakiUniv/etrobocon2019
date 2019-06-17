/**
 *  @file  SpeedControl.h
 *  @brief  前進値制御クラス
 *  @author M.Matsuura
 */
#ifndef SPEEDCONTROL_H
#define SPEEDCONTROL_H

#include "Distance.h"
#include "Pid.h"
#include <cmath>

class SpeedControl {
 private:
  Controller& controller;
  Distance dist;
  Pid pid;
  const double C;    //定数C
  const int radius;  //タイヤの半径[mm]
  double prevDistance;

 public:
  SpeedControl(Controller& controller_, int targetSpeed, double Kp, double Ki, double Kd);
  double calculateSpeed(int targetSpeed, double Kp, double Ki, double Kd);
};

#endif
