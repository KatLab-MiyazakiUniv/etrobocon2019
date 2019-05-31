#define _USE_MATH_DEFINES
#include "EtRobocon2019.h"
#include "Controller.h"
#include "Distance.h"
#include <cmath>

Distance::Distance()
    : radius(5), current_angle(0), pre_angle(0) {
}

/**
 * タイヤの回転角度を取得する
 * 
 * @param タイヤのポート番号
 * @return モータの角位置（単位は度），マイナスの値は逆方向に回転されたことを指す
 */
int32_t Distance::getAngle(motor_port_t wheelPort){
  pre_angle = current_angle;
  current_angle = ev3_motor_get_counts(wheelPort);

  return current_angle - pre_angle;
}

/**
 * 走行距離を計算して戻り値として返す
 * 
 * @param タイヤのポート番号
 * @return 走行距離
 */
double Distance::getDistance(motor_port_t wheelPort){
  return 2.0 * M_PI * radius * getAngle(wheelPort) / 360.0;
}
