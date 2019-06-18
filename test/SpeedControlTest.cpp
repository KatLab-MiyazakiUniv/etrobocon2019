/**
 * @file    SpeedControlTest.cpp
 * @brief   前進値制御クラスのテストファイル
 * @author  M.matsuura
 */
#include "SpeedControl.h"
#include <gtest/gtest.h>

namespace etrobocon2019_test {
  TEST(SpeedControl, SpeedControl_init)
  {
    Controller controller;
    SpeedControl SpeedCtrl(controller, 60, 0.2, 0.03, 0.04);
  }

  TEST(SpeedControl, calculateSpeed)
  {
    Controller controller;
    Distance dist;
    SpeedControl SpeedCtrl(controller, 50, 0.6, 0.05, 0.04);
    Pid pid(50, 0.6, 0.05, 0.04);

    // 左右のモータの角位置を取得
    int leftAngle = controller.leftWheel.getCount();
    int rightAngle = controller.rightWheel.getCount();
    // 走行距離の取得[mm]
    double prevDistance = dist.getDistance(leftAngle, rightAngle);

    // 4ms待つ
    controller.tslpTsk(4);

    // 4ms後の左右のモータの角位置を取得
    leftAngle = controller.leftWheel.getCount();
    rightAngle = controller.rightWheel.getCount();

    // 4ms後の走行距離の取得[mm]
    double nextDistance = dist.getDistance(leftAngle, rightAngle);

    //現在の速度を求める
    double currentSpeed = (nextDistance - prevDistance) / 0.004;

    //prevDistanceの更新
     prevDistance = dist.getDistance(leftAngle, rightAngle);

    // pid値を求める
    double pidValue = pid.control(currentSpeed);

    // PWM値 = pid値
    double expectedPWMValue = pidValue;

    ASSERT_DOUBLE_EQ(expectedPWMValue, SpeedCtrl.calculateSpeed(50, 0.6, 0.05, 0.04));
  }

}  // namespace etrobocon2019_test
