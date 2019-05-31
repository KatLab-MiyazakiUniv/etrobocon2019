/**
 *  @file   DistanceTest.cpp
 *  @brief  Distanceクラスのテストファイル
 *  @author Oiwane
 **/
#include "Distance.h"
#include <gtest/gtest.h>

namespace etrobocon2019_test{
  TEST(Distance, getAngleTest)
  {
    Distance dist;
    Controller controller;
    ASSERT_EQ(0, dist.getAngle(controller.rightWheel));
    ASSERT_EQ(0, dist.getAngle(controller.leftWheel));
  }

  TEST(Distance, getDistanceTest)
  {
    Distance dist;
    Controller controller;
    ASSERT_EQ(0, dist.getDistance(controller.rightWheel));
    ASSERT_EQ(0, dist.getDistance(controller.leftWheel));
  }
}