/**
 * @file    SpeedControlTest.cpp
 * @brief   前進値制御クラスのテストファイル
 * @author  M.matsuura
 */
#include "SpeedControl.h"
#include <gtest/gtest.h>

namespace etrobocon2019_test
{
TEST(SpeedControl, SpeedControl_init)
{
    SpeedControl SpeedCtrl;
}

TEST(SpeedControl, calculateSpeed)
{
    SpeedControl SpeedCtrl;

    Controller controller;
    Distance dist;

    Pid pid(50.0, 0.6, 0.05, 0.04);

    // 左右のモータの角位置を取得
    int leftAngle = controller.leftWheel.getCount();
    int rightAngle = controller.rightWheel.getCount();
    // 走行距離の取得[mm]
    double prevDistance = dist.getDistance(leftAngle, rightAngle);

    //4ms待つ
    controller.tslpTsk(4);

    //4ms後の左右のモータの角位置を取得
    leftAngle = controller.leftWheel.getCount();
    rightAngle = controller.rightWheel.getCount();

    //4ms後の走行距離の取得[mm]
    double nextDistance = dist.getDistance(leftAngle, rightAngle);

    //現在の速度を求める
    double currentSpeed = (nextDistance - prevDistance) / 0.004;

    //pid値を求める
    double pidValue = pid.control(currentSpeed);

    //PWM値 = pid値 * 360度 / (円周率 * タイヤの半径[mm] * 定数C)
    double expectedPWMValue = pidValue * 360 / (M_PI * 50 * 10.0);

    ASSERT_DOUBLE_EQ(expectedPWMValue, SpeedCtrl.calculateSpeed(50, 0.6, 0.05, 0.04));
}

} //namespace etrobocon2019_test