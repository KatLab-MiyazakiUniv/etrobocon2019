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
    Filter filter;
    int sensor = 24;

    // 前回のセンサ値がない場合は、入力値をそのまま返す
    ASSERT_EQ(static_cast<float>(sensor), filter.lowPassFilter(sensor));
  }



}
