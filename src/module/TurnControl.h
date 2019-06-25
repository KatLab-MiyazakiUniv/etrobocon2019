/**
 *  @file   TurnControl.h
 *  @brief  旋回値制御クラス
 *  @author K.Arima
 */
#ifndef TURN_CONTROL_H
#define TURN_CONTROL_H

#include "Pid.h"

class TurnControl {
 private:
  Pid pid;

 public:
  TurnControl(int targetBrightness, double Kp, double Ki, double Kd);
  double calculateTurn(int forward, int currentBrightness, int targetBrightness, double Kp,
                       double Ki, double Kd);
};

#endif
