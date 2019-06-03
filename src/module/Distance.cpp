/**
 *  @file   Distance.cpp
 *  @brief  走行距離を計算するクラス
 *  @author Oiwane
 **/
#define _USE_MATH_DEFINES
#include "Distance.h"
#include <cmath>

Distance::Distance()
    : radius(50) {}

/**
 * @brief 走行距離を計算して戻り値として返す
 * @param controller[Controllerオブジェクトの参照]
 * @return 走行距離
 */
double Distance::getDistance(int leftAngle, int rightAngle){
  // 左タイヤと右タイヤの角位置の平均を求める
  double angle = static_cast<double>(leftAngle + rightAngle) / 2.0;

  return 2.0 * M_PI * radius * angle / 360.0;
}
