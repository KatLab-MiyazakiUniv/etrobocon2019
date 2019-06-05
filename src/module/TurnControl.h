/**
 *  @file   TurnControl.h
 *  @brief  旋回値制御クラス
 *  @author K.Arima
 */
#ifndef TURN_CONTROL_H
#define TURN_CONTROL_H

#include "Pid.h"

class TurnControl
{
private:
public:
  TurnControl();
  double calculateTurn(int currentBrightness, int targetBrightness, double Kp, double Ki, double Kd);
};

#endif
