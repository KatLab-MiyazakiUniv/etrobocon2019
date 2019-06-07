/**
 * @file    SpeedControlTest.cpp
 * @brief   前進値制御クラスのテストファイル
 * @author  M.matsuura
 */
#include"SpeedControl.h"
#include <gtest/gtest.h>

namespace etrobocon2019_test
{
TEST(SpeedControl,SpeedControl_inti)
{
    SpeedControl SpeedCtrl;
}

TEST(SpeedControl,calulateSpeed)
{
    SpeedControl SpeedCtrl;

    Pid pid(50.0, 0.6, 0.05, 0.04);

    double expectedSpeedValue = pid.control(70.0);

    ASSERT_DOUBLE_EQ(expectedSpeedValue, SpeedCtrl.calculateSpeed(70, 50, 0.6, 0.05, 0.04));
}

}//namespace etrobocon2019_test