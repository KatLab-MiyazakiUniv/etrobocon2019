/**
 *  @file   Distance.cpp
 *  @brief  走行距離を計算するクラス
 *  @author Oiwane
 **/
#define _USE_MATH_DEFINES
#include "Distance.h"
#include <cmath>

Distance::Distance() : radius(50) {}

/**
 * @brief 走行距離を計算して戻り値として返す
 * @param leftAngle 左側のタイヤの回転角度[deg]
 * @param rightAngle 右側のタイヤの回転角度[deg]
 * @return 走行距離[mm]
 */
double Distance::getDistance(int leftAngle, int rightAngle) {
  // 左タイヤと右タイヤの角位置の平均を求める
  double angle = static_cast<double>(leftAngle + rightAngle) / 2.0;

  return 2.0 * M_PI * radius * angle / 360.0;
}
