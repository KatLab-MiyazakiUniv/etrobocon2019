/**
 *  @file   Distance.h
 *  @brief  走行距離を計算するクラス
 *  @author Oiwane
 **/
#ifndef DISTANCE_H
#define DISTANCE_H

class Distance{
 public:
  Distance();
  int32_t getAngle();
  double getDistance();

 private:
  const int radius;  //タイヤの半径[cm]
  int32_t current_angle;
  int32_t pre_angle;
};

#endif