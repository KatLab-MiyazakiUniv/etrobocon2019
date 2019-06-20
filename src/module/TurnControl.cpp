/**
 *  @file   TurnControl.cpp
 *  @brief  旋回値制御クラス
 *  @author K.Arima
 */
#include "TurnControl.h"

/**
 *  コンストラクタ
 *  @param  tragetBrightness  [目標の光センサー値]
 *  @param  Kp                [Pゲイン]
 *  @param  Ki                [Iゲイン]
 *  @param  Kd                [Dゲイン]
 */
TurnControl::TurnControl(int targetBrightness, double Kp, double Ki, double Kd)
  : pid(static_cast<double>(targetBrightness), Kp, Ki, Kd)
{
}

/**
 *  [TurnControl::calculateTurn]
 *  @brief  旋回値を計算する関数
 *  @param  currentBrightness [現在の光センサー値]
 *  @param  tragetBrightness  [目標の光センサー値]
 *  @param  Kp                [Pゲイン]
 *  @param  Ki                [Iゲイン]
 *  @param  Kd                [Dゲイン]
 *  @return                   [旋回値]
 */
double TurnControl::calculateTurn(int currentBrightness, int targetBrightness, double Kp, double Ki,
                                  double Kd)
{
  // pidの値を更新(パラメータに変更がなくても更新する)
  pid.setParameter(static_cast<double>(targetBrightness), Kp, Ki, Kd);

  return pid.control(static_cast<double>(currentBrightness));
}