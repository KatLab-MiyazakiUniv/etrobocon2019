/**
 *  @file  SpeedControl.cpp
 *  @brief  前進値制御クラス
 *  @author M.Matsuura
 */

#include "SpeedControl.h"

SpeedControl::SpeedControl() : dist(), controller(), C(7.2), radius(50) {

  // 左右のモータの角位置を取得
  int leftAngle = controller.getLeftMotorCount();
  int rightAngle = controller.getRightMotorCount();

  // 走行距離の取得[mm]
  prevDistance = dist.getDistance(leftAngle, rightAngle);
}

/**
 *  [SpeedControl::calculateSpeed]
 *  @param  targetSpeed [目標の速度] [mm/s]
 *  @param  Kp          [Pゲイン]
 *  @param  Ki          [Iゲイン]
 *  @param  Kd          [Dゲイン]
 *  @return             [PWM値]
 */

double SpeedControl::calculateSpeed(int targetSpeed, double Kp, double Ki,
                                    double Kd) {
  Pid pid(static_cast<double>(targetSpeed), Kp, Ki, Kd);

  Distance dist;

  Controller controller;

  // 4ms後の左右のモータの角位置を取得
  int leftAngle = controller.getLeftMotorCount();
  int rightAngle = controller.getRightMotorCount();

  // 4ms後の走行距離の取得[mm]
  double nextDistance = dist.getDistance(leftAngle, rightAngle);

  //現在の速度を求める
  double currentSpeed = (nextDistance - prevDistance) / 0.004;

  // pid値を求める
  double pidValue = pid.control(currentSpeed);

  // PWM値 = pid値 * 360度 / (円周率 * タイヤの半径[mm] * 定数C)
  double pwmValue = pidValue * 360 / (M_PI * radius * C);

  // PWM値を返す
  return pwmValue;
}
