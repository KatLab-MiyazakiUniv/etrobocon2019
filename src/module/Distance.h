/**
 *  @file   Distance.h
 *  @brief  走行距離を計算するクラス
 *  @author Oiwane
 **/
#ifndef DISTANCE_H
#define DISTANCE_H

#define _USE_MATH_DEFINES
#include "Controller.h"
#include <cmath>

class Distance {
 public:
  /**
   * コンストラクタ
   * @brief Distanceクラスのコンストラクタ
   */
  Distance();
  /**
   * 走行距離を取得する
   *
   * @brief 走行距離を計算して戻り値として返す
   * @param leftAngle 左側のタイヤの回転角度[deg]
   * @param rightAngle 右側のタイヤの回転角度[deg]
   * @return 走行距離[mm]。走行体が前へ進んでいたら正、後ろへ進んでいたら負になる
   */
  double getDistance(int leftAngle, int rightAngle);

 private:
  const int radius;  //タイヤの半径[mm]
};

#endif
