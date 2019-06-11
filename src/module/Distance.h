/**
 *  @file   Distance.h
 *  @brief  走行距離を計算するクラス
 *  @author Oiwane
 **/
#ifndef DISTANCE_H
#define DISTANCE_H

#include "Controller.h"

class Distance {
 public:
  Distance();
  double getDistance(int leftAngle, int rightAngle);

private:
  const int radius;  //タイヤの半径[mm]
};

#endif
