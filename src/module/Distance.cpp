/**
 *  @file   Distance.cpp
 *  @brief  走行距離を計算するクラス
 *  @author Oiwane
 **/
#include "Distance.h"

Distance::Distance() : radius(50) {}

double Distance::calculate(int angle)
{
  return 2.0 * M_PI * radius * static_cast<double>(angle) / 360.0;
}

double Distance::getDistance(int leftAngle, int rightAngle)
{
  double leftDistance = this->calculate(leftAngle);
  double rightDistance = this->calculate(rightAngle);

  return (leftDistance + rightDistance) / 2.0;
}