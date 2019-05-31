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

float Pid::control(float value, float delta)
{
  // 目標値と現在値との偏差を求める
  float error = target_ - value;
  // 偏差の積分処理
  integral_ += error * delta;

  return gain_.Kp_ * error + gain_.Ki_ * integral_;
}
