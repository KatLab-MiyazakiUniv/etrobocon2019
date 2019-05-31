/**
 *  @file   FilterTest.cpp
 *  @brief  フィルタークラスのテストファイル
 *  @author T.Miyaji
 */
#include "Filter.h"
#include <gtest/gtest.h>

namespace etrobocon2019_test {

  TEST(Filter, lowPassFilterTest_init)
  {
    Filter<> filter;
    int sensor = 24;

    // 前回のセンサー値がない場合は、入力値をそのまま返す
    ASSERT_EQ(static_cast<float>(sensor), filter.lowPassFilter(sensor));
  }

  TEST(Filter, lowPassFilterTest_filter)
  {
    Filter<> filter;
    int preSensor = 24;

    // フィルターを初期化する
    filter.lowPassFilter(preSensor);

    // 期待出力の計算
    int sensor = 77;
    float expected = preSensor * 0.9 + sensor * 0.1;
    // フィルターをかける
    ASSERT_EQ(expected, filter.lowPassFilter(sensor));
  }

  TEST(Filter, lowPassFilterTest_float)
  {
    Filter<float> filter;
    float preSensor = 2.3;

    // フィルターの初期化
    ASSERT_FLOAT_EQ(preSensor, filter.lowPassFilter(preSensor));

    // 期待出力の計算
    float sensor = 4.4;
    float expected = preSensor * 0.9 + sensor * 0.1;
    // フィルターをかける
    ASSERT_FLOAT_EQ(expected, filter.lowPassFilter(sensor));
  }

  TEST(Filter, lowPassFilterTest_double)
  {
    Filter<double> filter;
    double preSensor = 2.3;

    // フィルターの初期化
    ASSERT_DOUBLE_EQ(static_cast<float>(preSensor), filter.lowPassFilter(preSensor));

    // 期待出力の計算
    double sensor = 4.4;
    float expected = preSensor * 0.9 + sensor * 0.1;
    // フィルターをかける
    ASSERT_DOUBLE_EQ(expected, filter.lowPassFilter(sensor));
  }
}
