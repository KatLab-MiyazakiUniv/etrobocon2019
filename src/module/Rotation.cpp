/**
 * @file   Rotation.cpp
 * @brief  自転（走行体が両輪の中間を軸として回転）したときの角度を求めるクラス
 * @author T.Miyaji
 */
#include "Rotation.h"

Rotation::Rotation() : Radius(50.0), Tread(148.0) {}

double Rotation::calculate(int leftAngle, int rightAngle)
{
  // 車輪の回転角度を自転角度に変換する係数
  //! @see docs/odometry/odometry.pdf
  const double transform = 2.0 * Radius / Tread;
  double arc = distance.getDistance(std::abs(leftAngle), std::abs(rightAngle));

  return transform * arc;
}
