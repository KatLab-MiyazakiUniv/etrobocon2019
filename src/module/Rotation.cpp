/**
 * @file   Rotation.cpp
 * @brief  自転（yawing）したときの角度を求めるクラス
 * @author T.Miyaji
 */
#include "Rotation.h"

Rotation::Rotation() : Radius(50.0), Tread(130.0) {}

double Rotation::calculate(const int leftAngle, const int rightAngle)
{
  // 車輪の回転角度を自転角度に変換する係数
  //! @see docs/odometry/odometry.pdf
  const double transform = 2.0 * Radius / Tread;
  double arc = distance.getDistance(std::abs(leftAngle), std::abs(rightAngle));

  return transform * arc;
}
