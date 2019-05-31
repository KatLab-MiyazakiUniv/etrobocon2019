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
 * @param angle[タイヤのモーター角位置]
 * @return 走行距離
 */
double Distance::getDistance(int angle){
  return 2.0 * M_PI * radius * angle / 360.0;
}
