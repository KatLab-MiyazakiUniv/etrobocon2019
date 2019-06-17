/**
 *  @file   PidTest.cpp
 *  @brief  PID制御クラスのテストファイル
 *  @author T.Miyaji
 */
#include "Pid.h"
#include <gtest/gtest.h>

namespace etrobocon2019_test {
  TEST(PidGain, construct) { PidGain gain(0.6, 0.2, 0.3); }

  TEST(PidGain, setPidGain)
  {
    PidGain gain(0.6, 0.2, 0.3);
    gain.setPidGain(0.8, 0.01, 0.2);

    ASSERT_DOUBLE_EQ(0.8, gain.Kp);
    ASSERT_DOUBLE_EQ(0.01, gain.Ki);
    ASSERT_DOUBLE_EQ(0.2, gain.Kd);
  }

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

  TEST(Pid, pidControl)
  {
    // PID制御を行なうオブジェクトの作成
    Pid pid(80, 0.6, 0.05, 0.004);
    float sensor = 60;
    float error = 80 - 60;

    float p = error * 0.6;
    float i = error * 0.004 * 0.05;
    float d = error / 0.004 * 0.004;
    float expected = p + i + d;

    ASSERT_FLOAT_EQ(expected, pid.control(sensor));
  }

  TEST(Pid, limit_over)
  {
    Pid pid(80, 0.6);
    ASSERT_FLOAT_EQ(100.0, pid.limit(120.3));
  }

  TEST(Pid, limit_below)
  {
    Pid pid(80, 0.6);
    ASSERT_FLOAT_EQ(-100.0, pid.limit(-120.3));
  }

  TEST(Pid, limit_inner)
  {
    Pid pid(80, 0.6);
    ASSERT_FLOAT_EQ(12.3, pid.limit(12.3));
  }

  TEST(Pid, setParameter)
  {
    Pid pid(80, 0.2);
    const double target = pid.setParameter(60, 0.3, 0.4, 0.6);
    ASSERT_DOUBLE_EQ(60.0, target);
  }

  TEST(Pid, setPidGain)
  {
    Pid pid(80, 0.2);
    const PidGain& gain = pid.setPidGain(0.6, 0.3, 0.5);
    ASSERT_DOUBLE_EQ(0.6, gain.Kp);
    ASSERT_DOUBLE_EQ(0.3, gain.Ki);
    ASSERT_DOUBLE_EQ(0.5, gain.Kd);
  }
}  // namespace etrobocon2019_test
