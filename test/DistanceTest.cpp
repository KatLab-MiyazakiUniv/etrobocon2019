/**
 *  @file   DistanceTest.cpp
 *  @brief  Distanceクラスのテストファイル
 *  @author Oiwane
 **/
#include "Distance.h"
#include <gtest/gtest.h>

namespace etrobocon2019_test {
  TEST(Distance, Distance_init) { Distance distance(); }

  TEST(Distance, getDistanceTestForward)
  {
    Distance distance;
    Controller controller;
    const int radius = 50;
    int pwm = 30;

    // 回転角の取得
    int leftAngle = controller.getLeftMotorCount();
    int rightAngle = controller.getRightMotorCount();

    // 走行距離の計算
    double angle = static_cast<double>(leftAngle + rightAngle) / 2.0;
    double start = 2.0 * M_PI * radius * angle / 360.0;

    // モータの回転角を更新させるためにループ
    // ループ回数自体に意味はない
    for(int i = 0; i < 30; i++) {
      // pwm値のセット
      controller.setLeftMotorPwm(pwm);
      controller.setRightMotorPwm(pwm);
    }

    // 回転角の取得
    leftAngle = controller.getLeftMotorCount();
    rightAngle = controller.getRightMotorCount();

    // 走行距離の計算
    angle = static_cast<double>(leftAngle + rightAngle) / 2.0;
    double end = 2.0 * M_PI * radius * angle / 360.0;

    // 初めの位置からどれだけ進んだか計算
    double expectedDistance = end - start;

    ASSERT_DOUBLE_EQ(expectedDistance, distance.getDistance(leftAngle, rightAngle));
  }

  TEST(Distance, getDistanceBackward)
  {
    Distance distance;
    Controller controller;
    const int radius = 50;
    int pwm = -30;

    // 回転角の取得
    int leftAngle = controller.getLeftMotorCount();
    int rightAngle = controller.getRightMotorCount();

    // 走行距離の計算
    double angle = static_cast<double>(leftAngle + rightAngle) / 2.0;
    double start = 2.0 * M_PI * radius * angle / 360.0;

    // モータの回転角を更新させるためにループ
    // ループ回数自体に意味はない
    for(int i = 0; i < 30; i++) {
      // pwm値のセット
      controller.setLeftMotorPwm(pwm);
      controller.setRightMotorPwm(pwm);
    }

    // 回転角の取得
    leftAngle = controller.getLeftMotorCount();
    rightAngle = controller.getRightMotorCount();

    // 走行距離の計算
    angle = static_cast<double>(leftAngle + rightAngle) / 2.0;
    double end = 2.0 * M_PI * radius * angle / 360.0;

    // 初めの位置からどれだけ進んだか計算
    double expectedDistance = end - start;

    ASSERT_DOUBLE_EQ(expectedDistance, distance.getDistance(leftAngle, rightAngle));
  }
}  // namespace etrobocon2019_test
