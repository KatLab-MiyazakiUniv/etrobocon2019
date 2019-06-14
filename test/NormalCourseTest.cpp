/**
 *  @file   NormalCourseTest.cpp
 *  @brief  NormalCourseクラスのテストファイル
 *  @author Tatsumi0000
 */

#include "NormalCourse.h"
#include <gtest/gtest.h>
#include <array>

namespace etrobocon2019_test {
  TEST(NormalCourse, NormalCourse_init)
  {
    Controller controller;
    // カラーセンサーの目標値
    int targetBrightness = 90;
    // Leftコースである場合True
    bool isLeftCourse = true;
    // カラーセンサーの目標値
    int targetBrightnessExpected = 90;
    NormalCourse normalCourse(controller, isLeftCourse, targetBrightness);
    ASSERT_TRUE(normalCourse.getIsLeftCourse());
    ASSERT_EQ(targetBrightnessExpected, normalCourse.getTargetBrightness());
  }

  //エッジの切替メソッドのテスト
  TEST(NormalCourse, setIsLeftCourse)
  {
    Controller controller;
    // カラーセンサーの目標値
    int targetBrightness = 100;
    // Leftコースである場合True
    bool isLeftCourse = false;
    NormalCourse normalCourse(controller, isLeftCourse, targetBrightness);
    normalCourse.setIsLeftCourse(true);
    ASSERT_TRUE(normalCourse.getIsLeftCourse());
  }

  // セットしたエッジを返すゲッター
  TEST(NormalCourse, getIsLeftCourse)
  {
    Controller controller;
    // カラーセンサーの目標値
    int targetBrightness = 100;
    // Leftコースである場合True
    bool isLeftCourse = false;
    NormalCourse normalCourse(controller, isLeftCourse, targetBrightness);
    ASSERT_FALSE(normalCourse.getIsLeftCourse());
  }

  // セットした目標のカラーセンサ値を返すゲッター
  TEST(NormalCourse, getTargetBrightness)
  {
    Controller controller;
    // カラーセンサーの目標値
    int targetBrightness = 600;
    // Leftコースである場合True
    bool isLeftCourse = true;
    // 期待される出力
    int expected = 600;
    NormalCourse normalCourse(controller, isLeftCourse, targetBrightness);
    ASSERT_EQ(expected, normalCourse.getTargetBrightness());
  }
}  // namespace etrobocon2019_test
