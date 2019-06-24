/**
 *  @file   LineTracerTest.cpp
 *  @brief  ライントレーサークラスのテストファイル
 *  @author Takahiro55555
 */
#include "LineTracer.h"
#include "Controller.h"
#include <gtest/gtest.h>

namespace etrobocon2019_test
{
TEST(LineTracer, LineTracer_init)
{
    Controller controller;
    int targetBrightness = 50; //カラーセンサーの目標値
    bool isRight = true;       //Right コースであるか、否か

    LineTracer lineTracer(controller, targetBrightness, isRight);
}

TEST(LineTracer, run)
{
    Controller controller;
    int targetBrightness = 50; //カラーセンサーの目標値
    bool isRight = true;       //Right コースであるか、否か

    LineTracer lineTracer(controller, targetBrightness, isRight);

    // 走行用の設定
    NormalCourseProperty settings =
        {100, 100, {0.1, 0.001, 0.0}, {0.6, 0.001, 0.0}};

    // 走行する
    lineTracer.run(settings);
}

TEST(LineTracer, setTargetBrightness)
{
    Controller controller;
    int targetBrightness = 50; //カラーセンサーの目標値
    bool isRight = true;       //Right コースであるか、否か

    LineTracer lineTracer(controller, targetBrightness, isRight);

    // カラーセンサーの目標値を変更
    lineTracer.setTargetBrightness(100);
}

} // namespace etrobocon2019_test
