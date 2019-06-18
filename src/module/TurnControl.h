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
  TurnControl(int targetBrightness, double Kp = 0.0, double Ki = 0.0, double Kd = 0.0);
  double calculateTurn(int currentBrightness, int targetBrightness, double Kp, double Ki,
                       double Kd);
};

#endif
