/**
 *  @file   Navigator.h
 *  @brief 直進と後進できるクラス
 *  @author Harada,Oiwane
 *  updated by T.Miyaji
 */

#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "Controller.h"
#include "Distance.h"
#include "Pid.h"
#include "SpeedControl.h"
#include <cmath>

class Navigator {
 public:
  /**
   * コンストラクタ
   *
   * @brief Navigatorクラスのコンストラクタ
   * @param &controller_ [Controllerインスタンスの参照]
   * @param Kp_ [SpeedControl用のPゲイン]
   * @param Ki_ [SpeedControl用のIゲイン]
   * @param Kd_ [SpeedControl用のDゲイン]
   */
  explicit Navigator(Controller& controller_, double Kp_ = 0.60, double Ki_ = 0.0,
                     double Kd_ = 0.0);
  /**
   * @brief SpeedControl用のPidゲインのセッター
   * @param Kp_ [SpeedControl用のPゲイン]
   * @param Ki_ [SpeedControl用のIゲイン]
   * @param Kd_ [SpeedControl用のDゲイン]
   * @return なし
   */
  void setPidGain(double Kp_, double Ki_, double Kd_);
  /**
   * 前進と後進をする
   *
   * @brief specifiedDistanceの値でbackwardかforwardを呼び出す。
   * @param specifiedDistance [移動したい距離(mm)。正なら前進、負なら後進。]
   * @param pwm [モータの強さ]
   * @return なし
   */
  void move(double specifiedDistance, int pwm = 30);
  /**
   * 指定した速度で前進と後進をする
   *
   * @brief specifiedDistanceとSpeedControl.calculateSpeedから戻ってきたPWMをmoveに渡す
   * @param specifiedDistance [移動したい距離(mm)]
   * @param specifiedSpeed [移動したい速度]
   * @return なし
   */
  void moveAtSpecifiedSpeed(double specifiedDistance, int specifiedSpeed);
  /**
   * @TODO move関数に統合する？ また、IおよびDゲインも指定できるようにする？
   * @brief PID制御を用いて両輪の回転量が等しくなるように前進または後進する
   * @param specifiedDistance [移動したい距離(mm)。正なら前進、負なら後進]
   * @param pwm [モータの強さ]
   * @param pGain [PID制御のPゲイン]
   * @param iGain [PID制御のIゲイン]
   * @param dGain [PID制御のDゲイン]
   * @return なし
   */
  void moveByPid(double specifiedDistance, int pwm = 10, const double pGain = 0.6,
                 const double iGain = 0.0, const double dGain = 0.0);

  /**
   * @brief PID制御を用いて両輪の回転量が等しくなるように指定された速度で前進または後進する
   * @param specifiedDistance [移動したい距離(mm)。正なら前進、負なら後進]
   * @param specifiedSpeed [移動したい速度]
   * @param pGain [PID制御のPゲイン]
   * @param iGain [PID制御のIゲイン]
   * @param dGain [PID制御のDゲイン]
   */
  void moveAtSpecifiedSpeedByPid(double specifiedDistance, int specifiedSpeed,
                                 const double pGain = 0.6, const double iGain = 0.0,
                                 const double dGain = 0.0);

 private:
  Distance distance;
  Controller& controller;
  double KpForSpeed;
  double KiForSpeed;
  double KdForSpeed;
  /**
   * 指定した距離動いたか判定する
   * @brief 現在値とgoalDistanceを比較し、resultに"true"か"false"を格納する
   * @param goalDistance [現在地から移動したい距離動いた後の値(mm)]
   * @param isForward [前進なら"true"、後進なら"false"]
   * @return result [移動したい距離動いたら"true"、動いていないなら"false"]
   */
  bool hasArrived(double goalDistance, bool isForward);
  /**
   * @brief pwmをセットする
   * @param pwm [モータの強さ]
   * @param alpha [左右のPWM値の差]
   * @return なし
   */
  void setPwmValue(int pwm, double alpha = 0.0);
};

#endif
