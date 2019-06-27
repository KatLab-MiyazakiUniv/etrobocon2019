/**
 * @file   Rotation.h
 * @brief  自転（走行体が両輪の中間を軸として回転）したときの角度を求めるクラス
 * @author T.Miyaji
 */
#ifndef ROTATION_H
#define ROTATION_H
#include "Distance.h"
#include <cmath>

class Rotation {
 private:
  const double Radius;  //  走行体の車輪の半径 [mm]
  const double Tread;   // 走行体のトレッド幅（両輪の間の距離） [mm]
  Distance distance;

 public:
  Rotation();
  /**
   * @brief 自転したときの角度を求める
   * @param leftAngle [左車輪の回転角度 [deg]]
   * @param rightAngle [右車輪の回転角度 [deg]]
   * @return 自転角度（時計回り、反時計回りにかかわらず必ず正の数）
   */
  double calculate(int leftAngle, int rightAngle);
};

#endif
