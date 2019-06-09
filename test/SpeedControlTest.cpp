/**
 * @file    SpeedControlTest.cpp
 * @brief   前進値制御クラスのテストファイル
 * @author  M.matsuura
 */
#include "SpeedControl.h"
#include <gtest/gtest.h>

namespace etrobocon2019_test
{
TEST(SpeedControl, SpeedControl_inti)
{
    SpeedControl SpeedCtrl;
}

TEST(SpeedControl, calculateSpeed)
{
    SpeedControl SpeedCtrl;

    Controller controller;
    Distance dist;
    double currentSpeed = 0.0;
    double delta = 0.004;

    Pid pid(50.0, 0.6, 0.05, 0.04);

    // 左右のモータの角位置を取得
    int leftAngle = controller.leftWheel.getCount();
    int rightAngle = controller.rightWheel.getCount();
    // 走行距離の取得[mm]
    double distance = dist.getDistance(leftAngle, rightAngle);
    //pid制御後のPWM値
    double pidSpeed = pid.control(currentSpeed);
    currentSpeed = distance / delta;
    //setPWMしてモ左右のモータを回す
    controller.leftWheel.setPWM(pidSpeed);
    controller.rightWheel.setPWM(pidSpeed);
    //4ms待つ
    controller.tslpTsk(4);
    //距離を求める
    distance += dist.getDistance(controller.leftWheel.getCount(), controller.rightWheel.getCount());
    //走行体の速度を求める
    double expectedSpeedValue = currentSpeed + 2.0 * distance / delta + currentSpeed;

    ASSERT_DOUBLE_EQ(expectedSpeedValue, SpeedCtrl.calculateSpeed(50, 0.6, 0.05, 0.04));
}

} //namespace etrobocon2019_test