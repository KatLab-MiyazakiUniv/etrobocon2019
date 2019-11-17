/**
 *  @file   Curvature.cpp
 *  @brief  曲率を計算するクラス
 *  @author Oiwane
 **/
#include "Curvature.h"

Curvature::Curvature(double targetCurvature_, double Kp_, double Ki_, double Kd_)
 : pid(targetCurvature_, Kp_, Ki_, Kd_),
   targetCurvature(targetCurvature_),
   pidGain(Kp_, Ki_, Kd_),
   preDistance(0.0),
   preTheta(0.0),
   Tread(128.0)
{
}

double Curvature::control(int leftAngle, int rightAngle, int velocity)
{
  Distance distance;

  double leftDistance = distance.calculate(leftAngle);
  double rightDistance = distance.calculate(rightAngle);

  // 旋回角度を求める
  double currentTheta = (rightDistance - leftDistance) / Tread;
  double errorTheta = currentTheta - preTheta;

  // 曲率を求める
  double currentDistance = distance.getDistance(leftAngle, rightAngle);
  double errorDistance = currentDistance - preDistance;

  double kappa = (errorDistance) != 0.0 ? (sin(errorTheta) / errorDistance) : 0.0;

  // PID制御をする
  auto pidValue = pid.control(kappa) * velocity;

  preDistance = currentDistance;
  preTheta = currentTheta;

  return pidValue;
}