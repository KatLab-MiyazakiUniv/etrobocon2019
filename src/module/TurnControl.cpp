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
 *  @param  tragetBrightness [目標の光センサー値]
 *  @param  Kp               [Pゲイン]
 *  @param  Ki               [Iゲイン]
 *  @param  Kd               [Dゲイン]
 *  @return                  [旋回値]
 */
double TurnControl::calculateTurn(int targetBrightness, double Kp, double Ki, double Kd)
{
  Pid pid(static_cast<double>(targetBrightness), Kp, Ki, Kd);
  Controller ctrl;

  int currentBrightness = ctrl.getBrightness();
  const double delta = 0.004;
  double turnValue = pid.control(static_cast<double>(currentBrightness), delta);

  return turnValue;
}