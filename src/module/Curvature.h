/**
 *  @file   Curvature.h
 *  @brief  曲率を計算するクラス
 *  @author Oiwane
 **/
#ifndef CURVATURE_H
#define CURVATURE_H

#include <cmath>
#include "Distance.h"
#include "Pid.h"

class Curvature
{
 private:
  Pid pid;
  double targetCurvature;
  PidGain pidGain;
  static constexpr double Tread = 140.0;

 public:
	Curvature(double targetCurvature, double Kp, double Ki, double Kd);
	double control(int leftAngle, int rightAngle);

};

#endif