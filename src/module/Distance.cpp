/**
 *  @file   Distance.cpp
 *  @brief  走行距離を計算するクラス
 *  @author Oiwane
 **/
#define _USE_MATH_DEFINES
#include "Distance.h"
#include <cmath>

Distance::Distance()
    : radius(5), currentAngle(0), preAngle(0) {}

/**
 * @brief タイヤの回転角度を取得する
 * @param wheel [タイヤのオブジェクト]
 * @return モータの前回と現在の角位置の差（単位は度）、マイナスの値は逆方向に回転されたことを指す
 */
int32_t Distance::getAngle(Motor wheel){
  preAngle = currentAngle;
  currentAngle = wheel.getCount();

  return currentAngle - preAngle;
}

/**
 * @brief 走行距離を計算して戻り値として返す
 * @param wheel [タイヤのオブジェクト]
 * @return 走行距離
 */
double Distance::getDistance(Motor wheel){
  double angle = static_cast<double>(getAngle(wheel));
  return 2.0 * M_PI * radius * angle / 360.0;
}
