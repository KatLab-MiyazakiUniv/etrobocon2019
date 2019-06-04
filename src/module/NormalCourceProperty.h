/**
 *  @file RobotProperty.h
 *  @brief ノーマルコースを走るために必要な情報
 *  @author Tatsumi0000
 */
#ifndef NORMAL_COURCE_PROPERTY_H
#define NORMAL_COURCE_PROPERTY_H
struct Pid {
  // p値
  double kp;
  // k値
  double ki;
  // d値
  double kd;
};
struct NormalCourceProperty {
  // 目標距離
  int targetDistance;
  // 目標スピード
  int targetSpeed;
  // speedPid
  Pid speedPid;
  // turnPid
  Pid turnPid;
};

#endif
