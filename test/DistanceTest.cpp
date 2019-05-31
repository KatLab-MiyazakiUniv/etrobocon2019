/**
 *  @file   DistanceTest.cpp
 *  @brief  Distanceクラスのテストファイル
 *  @author Oiwane
 **/
#include "Distance.h"
#include <gtest/gtest.h>

namespace etrobocon2019_test{
  TEST(Distance, getDistanceTest)
  {
    Distance dist;
    Controller controller;
    ASSERT_EQ(0, dist.getDistance(controller));
  }
}