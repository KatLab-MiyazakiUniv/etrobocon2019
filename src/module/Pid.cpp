/**
 *  @file   Pid.cpp
 *  @brief  PID制御クラス
 *  @author T.Miyaji
 */
#include "Pid.h"

PidGain::PidGain(float Kp, float Ki, float Kd) : Kp_(Kp), Ki_(Ki), Kd_(Kd) {}

Pid::Pid(float target, float Kp, float Ki, float Kd)
  : target_(target), gain_(Kp, Ki, Kd), integral_(0.0f), preError_(0.0f)
{
}

/**
 *  [Pid::control]
 *  @param  value [現在値]
 *  @param  delta [タスク周期]
 *  @return       [PID制御後の操作量]
 */
float Pid::control(float value, float delta)
{
  // 目標値と現在値との偏差を求める
  float error = target_ - value;
  // 偏差の積分処理
  integral_ += error * delta;
  // 偏差の微分処理
  float diff = (error - preError_) / delta;

  // 前回偏差の更新
  preError_ = error;

  return gain_.Kp_ * error + gain_.Ki_ * integral_ + gain_.Kd_ * diff;
}
