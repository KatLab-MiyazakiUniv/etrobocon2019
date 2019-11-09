/**
 *  @file   Curvature.cpp
 *  @brief  曲率を計算するクラス
 *  @author Oiwane
 **/
#include "Curvature.h"

Curvature::Curvature(double targetCurvature_, double Kp_, double Ki_, double Kd_)
 : pid(targetCurvature_, Kp_, Ki_, Kd_), targetCurvature(targetCurvature_), pidGain(Kp_, Ki_, Kd_)
{
}

double Curvature::control(int leftAngle, int rightAngle)
{
  Distance distance;

  double leftDistance = distance.calculate(leftAngle);
  double rightDistance = distance.calculate(rightAngle);

  // 旋回角度を求める
  double theta = (rightDistance - leftDistance) / Tread;

	// 曲率を求める
  double d = distance.getDistance(leftAngle, rightAngle);
  double kappa = d != 0.0 ? (sin(theta) / d) : 0.0;

  pid.setParameter(targetCurvature, pidGain.Kp, pidGain.Ki, pidGain.Kd);

  // PID制御をする
  auto pidValue = pid.control(kappa) * 600.0;

  return pidValue;
}