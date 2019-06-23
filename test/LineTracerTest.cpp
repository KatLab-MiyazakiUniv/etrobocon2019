/**
 *  @file   LineTracerTest.cpp
 *  @brief  ライントレーサークラスのテストファイル
 *  @author Takahiro55555
 */
#include "LineTracer.h"
#include <gtest/gtest.h>

namespace etrobocon2019_test
{
TEST(LineTracer, LineTracer_init)
{
    int targetBrightness = 50; //カラーセンサーの目標値
    bool isRight = true;       //Right コースであるか、否か

    LineTracer lineTracer(targetBrightness, isRight);
}

TEST(LineTracer, run)
{
    int targetBrightness = 50; //カラーセンサーの目標値
    bool isRight = true;       //Right コースであるか、否か

    LineTracer lineTracer(targetBrightness, isRight);

    // 走行用の設定
    NormalCourseProperty settings =
        {100, 100, {0.1, 0.001, 0.0}, {0.6, 0.001, 0.0}};

    // 走行する
    lineTracer.run(settings);
}

TEST(LineTracer, setTargetBrightness)
{
    int targetBrightness = 50; //カラーセンサーの目標値
    bool isRight = true;       //Right コースであるか、否か

    LineTracer lineTracer(targetBrightness, isRight);

    // カラーセンサーの目標値を変更
    lineTracer.setTargetBrightness(100);
}

} // namespace etrobocon2019_test
