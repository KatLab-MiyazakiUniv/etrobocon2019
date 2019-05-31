/**
 *  @file   Pid.cpp
 *  @brief  PID制御クラス
 *  @author T.Miyaji
 */
#include "Pid.h"

PidGain::PidGain(float Kp, float Ki, float Kd) : Kp_(Kp), Ki_(Ki), Kd_(Kd) {}

Pid::Pid(float target, float Kp, float Ki, float Kd) : target_(target), gain_(Kp, Ki, Kd) {}
