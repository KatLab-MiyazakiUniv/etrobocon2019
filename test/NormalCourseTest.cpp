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
    bool selectedEdgeExpected = false;
    // カラーセンサーの目標値
    int targetBrightnessExpected = 90;
    NormalCourse normalCourse(controller, targetBrightness);
    ASSERT_EQ(selectedEdgeExpected, normalCourse.getSelectedEdge());
    ASSERT_EQ(targetBrightnessExpected, normalCourse.getTargetBrightness());
  }

  //エッジの切替メソッドのテスト
  TEST(NormalCourse, selectedEdgeLR)
  {
    Controller controller;
    // カラーセンサーの目標値
    int targetBrightness = 100;
    NormalCourse normalCourse(controller, targetBrightness);
    normalCourse.selectedEdgeLR(true);
    ASSERT_TRUE(normalCourse.getSelectedEdge());
  }

  // セットしたエッジを返すゲッター
  TEST(NormalCourse, getSelectedEdge)
  {
    Controller controller;
    // カラーセンサーの目標値
    int targetBrightness = 100;
    NormalCourse normalCourse(controller, targetBrightness);
    // 初期化する際に，falseで初期化するため
    ASSERT_FALSE(normalCourse.getSelectedEdge());
  }

  // セットした目標のカラーセンサ値を返すゲッター
  TEST(NormalCourse, getTargetBrightness)
  {
    Controller controller;
    // カラーセンサーの目標値
    int targetBrightness = 600;
    // 期待される出力
    int expected = 600;
    NormalCourse normalCourse(controller, targetBrightness);
    ASSERT_EQ(expected, normalCourse.getTargetBrightness());
  }
}  // namespace etrobocon2019_test
