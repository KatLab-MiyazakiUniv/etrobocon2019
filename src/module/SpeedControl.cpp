/**
 *  @file  SpeedControl.cpp
 *  @brief  前進値制御クラス
 *  @author M.Matsuura
 */

#include "SpeedControl.h"

/**
 *  コンストラクタ
 *  @param  tragetSpeed       [目標速度]
 *  @param  Kp                [Pゲイン]
 *  @param  Ki                [Iゲイン]
 *  @param  Kd                [Dゲイン]
 */

SpeedControl::SpeedControl(Controller& controller_, int targetSpeed, double Kp, double Ki,
                           double Kd)
  : controller(controller_), dist(), pid(targetSpeed, Kp, Ki, Kd)
{
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

double SpeedControl::calculateSpeed(int targetSpeed, double Kp, double Ki, double Kd)
{
  // pidの値を更新(パラメータに変更がなくても更新する)
  pid.setParameter(targetSpeed, Kp, Ki, Kd);

  // 4ms後の左右のモータの角位置を取得
  int leftAngle = controller.getLeftMotorCount();
  int rightAngle = controller.getRightMotorCount();

  // 4ms後の走行距離の取得[mm]
  double nextDistance = dist.getDistance(leftAngle, rightAngle);

  //現在の速度を求める
  double currentSpeed = nextDistance - prevDistance;

  //prevDistanceの更新
  prevDistance = dist.getDistance(leftAngle, rightAngle);

  // pid値を求める
  double pidValue = pid.control(currentSpeed);

  // PWM値 = pid値
  double pwmValue = pidValue;

  // PWM値を返す
  return pwmValue;
}
