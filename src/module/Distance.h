/**
 *  @file   Distance.h
 *  @brief  走行距離を計算するクラス
 *  @author Oiwane
 **/
#ifndef DISTANCE_H
#define DISTANCE_H

#include "Controller.h"

class Distance{
 public:
  Distance();
  int32_t getAngle(Motor& wheel);
  double getDistance(Motor& wheel);

 private:
  const int radius;  //タイヤの半径[cm]
  int32_t currentAngle;
  int32_t preAngle;
};

#endif