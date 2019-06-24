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
  double prevDistance;

 public:
  /**
   *  コンストラクタ
   *  @param  controller_       [Controller]
   *  @param  targetSpeed       [目標速度]
   *  @param  Kp                [Pゲイン]
   *  @param  Ki                [Iゲイン]
   *  @param  Kd                [Dゲイン]
   */
  SpeedControl(Controller& controller_, int targetSpeed, double Kp, double Ki, double Kd);

  /**
   *  [SpeedControl::calculateSpeed]
   *  @param  targetSpeed [目標の速度] [mm/s]
   *  @param  Kp          [Pゲイン]
   *  @param  Ki          [Iゲイン]
   *  @param  Kd          [Dゲイン]
   *  @return             [PWM値]
   */
  double calculateSpeed(int targetSpeed, double Kp, double Ki, double Kd);
};

#endif
