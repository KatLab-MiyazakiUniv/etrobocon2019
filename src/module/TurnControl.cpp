/**
 *  @file   TurnControl.cpp
 *  @brief  旋回値制御クラス
 *  @author K.Arima
 */
#include "TurnControl.h"

TurnControl::TurnControl()
{
}

/**
 *  [TurnControl::calculateTurn]
 *  @param  currentBrightness [現在の光センサー値]  
 *  @param  tragetBrightness  [目標の光センサー値]
 *  @param  Kp                [Pゲイン]
 *  @param  Ki                [Iゲイン]
 *  @param  Kd                [Dゲイン]
 *  @return                   [旋回値]
 */
double TurnControl::calculateTurn(int currentBrightness, int targetBrightness, double Kp, double Ki, double Kd)
{
  Pid pid(static_cast<double>(targetBrightness), Kp, Ki, Kd);

  double turnValue = pid.control(static_cast<double>(currentBrightness));

  return turnValue;
}