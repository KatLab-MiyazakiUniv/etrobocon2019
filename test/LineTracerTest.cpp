/**
 *  @file   LineTracerTest.cpp
 *  @brief  ライントレーサークラスのテストファイル
 *  @author Takahiro55555
 */
#include "LineTracer.h"
#include "Controller.h"
#include <gtest/gtest.h>

namespace etrobocon2019_test {
  TEST(LineTracer, LineTracer_init)
  {
    Controller controller;
    int targetBrightness = 50;  //カラーセンサーの目標値
    bool isLeft = true;         // Left コースであるか、否か

    LineTracer lineTracer(controller, targetBrightness, isLeft);
  }

  TEST(LineTracer, run)
  {
    Controller controller;
    int targetBrightness = 50;  //カラーセンサーの目標値
    bool isLeft = true;         // Left コースであるか、否か

    LineTracer lineTracer(controller, targetBrightness, isLeft);

    // 走行用の設定
    NormalCourseProperty settings = { 100, 100, 0.0, { 0.6, 0.001, 0.0 } };

    // 走行する
    lineTracer.run(settings);
  }

  TEST(LineTracer, setTargetBrightness)
  {
    Controller controller;
    int targetBrightness = 50;  //カラーセンサーの目標値
    bool isLeft = true;         // Left コースであるか、否か

    LineTracer lineTracer(controller, targetBrightness, isLeft);

    // カラーセンサーの目標値を変更
    lineTracer.setTargetBrightness(100);
  }

  TEST(LineTracer, calculateTurnValueTest)
  {
    Controller controller;
    int targetBrightness = 50;  //カラーセンサーの目標値
    bool isLeft = true;         // Left コースであるか、否か

    LineTracer lineTracer(controller, targetBrightness, isLeft);

    int actual = lineTracer.calculateTurnValue(10, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    int expected = 0;

    ASSERT_EQ(expected, actual);
  }

}  // namespace etrobocon2019_test
