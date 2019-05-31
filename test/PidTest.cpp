/**
 *  @file   PidTest.cpp
 *  @brief  PID制御クラスのテストファイル
 *  @author T.Miyaji
 */
#include "Pid.h"
#include <gtest/gtest.h>

namespace etrobocon2019_test {
  TEST(Pid, Pid_init)
  {
    // P制御を行なうオブジェクトの作成
    Pid p(80, 0.6);

    // PI制御を行なうオブジェクトの作成
    Pid pi(80, 0.6, 0.05);

    // PID制御を行なうオブジェクトの作成
    Pid pid(80, 0.6, 0.05, 0.04);
  }

  TEST(Pid, pControl)
  {
    // P制御を行なうオブジェクトの作成
    Pid p(80, 0.6);
    float sensor = 60;
    float expected = (80 - sensor) * 0.6;
    ASSERT_FLOAT_EQ(expected, p.control(sensor));
  }

  TEST(Pid, piControl)
  {
    // PI制御を行なうオブジェクトの作成
    Pid pi(80, 0.6, 0.05);
    float sensor = 60;
    float expected = (80 - sensor) * 0.6 + (80 - sensor) * 0.05 * 0.004;
    ASSERT_FLOAT_EQ(expected, pi.control(sensor));
  }
}  // namespace etrobocon2019_test
