/**
 *  @file   RotationTest.cpp
 *  @brief  Rotationクラスのテストファイル
 *  @author T.Miyaji
 */
#include "Rotation.h"
#include <cmath>
#include <gtest/gtest.h>

namespace etrobocon2019_test {
  TEST(Rotation, construct) { Rotation rotation; }

  TEST(Rotation, rotationTest)
  {
    Rotation rotation;
    const double Radius = 50.0;
    static constexpr double Tread = 128.0;

    // 時計回りに車輪を30度動かす
    double arc = M_PI * Radius * 30.0 / 180.0;
    double expected = 2.0 * Radius * arc / Tread;

    ASSERT_DOUBLE_EQ(expected, rotation.calculate(30, -30));
    // 反時計回りでも同じ結果であることを確認する
    ASSERT_DOUBLE_EQ(expected, rotation.calculate(-30, 30));
  }

}  // namespace etrobocon2019_test
