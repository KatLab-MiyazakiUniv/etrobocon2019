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
    ASSERT_EQ(static_cast<double>(sensor), filter.lowPassFilter(sensor));
  }

  TEST(Filter, lowPassFilterTest_filter)
  {
    Filter<> filter;
    int preSensor = 24;

    // フィルターを初期化する
    filter.lowPassFilter(preSensor);

    // 期待出力の計算
    int sensor = 77;
    double expected = preSensor * 0.9 + sensor * 0.1;
    // フィルターをかける
    ASSERT_EQ(expected, filter.lowPassFilter(sensor));
  }

  TEST(Filter, lowPassFilterTest_float)
  {
    Filter<float> filter;
    float preSensor = 2.3;

    // フィルターの初期化
    ASSERT_DOUBLE_EQ(preSensor, filter.lowPassFilter(preSensor));

    // 期待出力の計算
    float sensor = 4.4;
    double expected = preSensor * 0.9 + sensor * 0.1;
    // フィルターをかける
    ASSERT_DOUBLE_EQ(expected, filter.lowPassFilter(sensor));
  }

  TEST(Filter, lowPassFilterTest_double)
  {
    Filter<double> filter;
    double preSensor = 2.3;

    // フィルターの初期化
    ASSERT_DOUBLE_EQ(preSensor, filter.lowPassFilter(preSensor));

    // 期待出力の計算
    double sensor = 4.4;
    double expected = preSensor * 0.9 + sensor * 0.1;
    // フィルターをかける
    ASSERT_DOUBLE_EQ(expected, filter.lowPassFilter(sensor));
  }

  TEST(Filter, lowPassFilter_update)
  {
    Filter<> filter;
    int init = 10;

    // フィルターの初期化
    ASSERT_DOUBLE_EQ(init, filter.lowPassFilter(init));

    // 期待出力の計算
    int preSensor = 20;
    double expected = init * 0.9 + preSensor * 0.1;
    // フィルターをかける
    ASSERT_DOUBLE_EQ(expected, filter.lowPassFilter(preSensor));

    // 期待出力の計算
    int sensor = 30;
    double expected2 = preSensor * 0.9 + sensor * 0.1;
    // フィルターをかける(前回値の更新あり)
    ASSERT_DOUBLE_EQ(expected2, filter.lowPassFilter(sensor));
  }
}  // namespace etrobocon2019_test
