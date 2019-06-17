/**
 *  @file   Pid.cpp
 *  @brief  PID制御クラス
 *  @author T.Miyaji
 */
#include "Pid.h"

PidGain::PidGain(double Kp_, double Ki_, double Kd_) : Kp(Kp_), Ki(Ki_), Kd(Kd_) {}

Pid::Pid(double target_, double Kp_, double Ki_, double Kd_)
  : target(target_), gain(Kp_, Ki_, Kd_), integral(0.0f), preError(0.0f)
{
}

void PidGain::setPidGain(double Kp_, double Ki_, double Kd_)
{
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
}

/**
 *  [Pid::control]
 *  @param  value [現在値]
 *  @param  delta [タスク周期]
 *  @return       [PID制御後の操作量]
 */
double Pid::control(double value, double delta)
{
  // 目標値と現在値との偏差を求める
  double error = target - value;
  // 偏差の積分処理
  integral += error * delta;
  // 偏差の微分処理
  double diff = (error - preError) / delta;

  // 前回偏差の更新
  preError = error;

  // P制御の計算(Pゲイン * 偏差)
  double p = gain.Kp * error;
  // I制御の計算(Iゲイン * 偏差の積分値)
  double i = gain.Ki * integral;
  // D制御の計算(Dゲイン * 偏差の微分値)
  double d = gain.Kd * diff;

  return limit(p + i + d);
}

/**
 * @brief 目標値とPIDゲインの設定をする関数
 * @param target_ [設定する目標値]
 * @param Kp_ [Pゲイン]
 * @param Ki_ [Iゲイン]
 * @param Kd_ [Dゲイン]
 * @param 設定した目標値
 */
const double Pid::setParameter(double target_, double Kp_, double Ki_, double Kd_)
{
  target = target_;
  setPidGain(Kp_, Ki_, Kd_);

  return target;
}

/**
 * @brief PIDゲインの設定をする関数
 * @param Kp_ [Pゲイン]
 * @param Ki_ [Iゲイン]
 * @param Kd_ [Dゲイン]
 * @param PidGain構造体の参照
 */
const PidGain& Pid::setPidGain(double Kp_, double Ki_, double Kd_)
{
  gain.setPidGain(Kp_, Ki_, Kd_);
  return gain;
}

/**
 *  [Pid::limit 操作量を[-100, 100]の間に設定する]
 *  @param  value [操作量]
 *  @return       [制限をかけた後の操作量]
 */
double Pid::limit(double value)
{
  if(value > 100.0) return 100.0;
  if(value < -100.0) return -100.0;

  return value;
}
