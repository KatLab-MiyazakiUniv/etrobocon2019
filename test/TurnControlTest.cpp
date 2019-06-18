/**
 *  @file   TurnControlTest.cpp
 *  @brief  旋回値制御クラスのテストファイル
 *  @author K.Arima
 */
#include "TurnControl.h"
#include <gtest/gtest.h>

namespace etrobocon2019_test {
  TEST(TurnControl, TurnControl_init_target) { TurnControl turnCtrl(50); }

  TEST(TurnControl, TurnControl_init_target_pid) { TurnControl turnCtrl(50, 0.6, 0.05, 0.04); }

  TEST(TurnControl, calculateTurn_target)
  {
    TurnControl turnCtrl(0);

    Pid pid(50.0, 0.6, 0.05, 0.04);

    double expectedTurnValue = pid.control(70.0);

    ASSERT_DOUBLE_EQ(expectedTurnValue, turnCtrl.calculateTurn(70, 50, 0.6, 0.05, 0.04));
  }

  TEST(TurnControl, calculateTurn_target_pid)
  {
    TurnControl turnCtrl(50, 0.6, 0.05, 0.04);

    Pid pid(50.0, 0.6, 0.05, 0.04);

    double expectedTurnValue = pid.control(70.0);

    ASSERT_DOUBLE_EQ(expectedTurnValue, turnCtrl.calculateTurn(70, 50, 0.6, 0.05, 0.04));
  }
}  // namespace etrobocon2019_test