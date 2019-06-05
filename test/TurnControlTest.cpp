/**
 *  @file   TurnControlTest.cpp
 *  @brief  旋回値制御クラスのテストファイル
 *  @author K.Arima
 */
#include "TurnControl.h"
#include <gtest/gtest.h>

namespace etrobocon2019_test
{
TEST(TurnControl, TurnControl_init)
{
    TurnControl turnCtrl;
}

TEST(TurnControl, calculateTurn)
{
    TurnControl turnCtrl;

    Pid pid(50.0, 0.6, 0.05, 0.04);
    Controller ctrl;

    int currentBrightness = ctrl.getBrightness();
    double expectedTurnValue = pid.control(static_cast<double>(currentBrightness));

    ASSERT_DOUBLE_EQ(expectedTurnValue, turnCtrl.calculateTurn(50, 0.6, 0.05, 0.04));
}
} // namespace etrobocon2019_test