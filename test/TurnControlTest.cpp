/**
 *  @file   TurnControlTest.cpp
 *  @brief  旋回値制御クラスのテストファイル
 *  @author K.Arima
 */
#include "TurnControl.h"
#include <gtest/gtest.h>

namespace etrobocon2019_test {
  TEST(TurnControl, TurnControl_init)
  {
    int targetBrightness = 50;
    double Kp = 0.6;
    double Ki = 0.05;
    double Kd = 0.04;
    TurnControl turnCtrl(targetBrightness, Kp, Ki, Kd);
  }

  TEST(TurnControl, calculateTurn)
  {
    int forword = 100;
    int currentBrightness = 40;
    int targetBrightness = 50;
    double Kp = 0.6;
    double Ki = 0.05;
    double Kd = 0.04;

    // 期待値を計算
    Pid pid(static_cast<double>(targetBrightness), Kp, Ki, Kd);
    Filter<> filter;
    double filteredBrightness = filter.lowPassFilter(currentBrightness);
    double expectedTurnValue = pid.control(filteredBrightness);

    TurnControl turnCtrl(targetBrightness, Kp, Ki, Kd);

    ASSERT_DOUBLE_EQ(expectedTurnValue, turnCtrl.calculateTurn(forword, currentBrightness,
                                                               targetBrightness, Kp, Ki, Kd));
  }

  TEST(TurnControl, limitCalculateTurn)
  {
    int forword = 50;
    int currentBrightness = 40;
    int targetBrightness = 50;
    double Kp = 0.6;
    double Ki = 0.05;
    double Kd = 0.04;

    // 期待値の計算
    Pid pid(static_cast<double>(targetBrightness), Kp, Ki, Kd);
    Filter<> filter;
    double filteredBrightness = filter.lowPassFilter(currentBrightness);
    double expectedTurnValue = pid.control(filteredBrightness) * forword / 100;

    TurnControl turnCtrl(targetBrightness, Kp, Ki, Kd);

    ASSERT_DOUBLE_EQ(expectedTurnValue, turnCtrl.calculateTurn(forword, currentBrightness,
                                                               targetBrightness, Kp, Ki, Kd));
  }
}  // namespace etrobocon2019_test

// namespace etrobocon2019_test