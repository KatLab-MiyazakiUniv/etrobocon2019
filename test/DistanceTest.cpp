/**
 *  @file   DistanceTest.cpp
 *  @brief  Distanceクラスのテストファイル
 *  @author Oiwane
 **/
#define _USE_MATH_DEFINES
#include "Distance.h"
#include <gtest/gtest.h>
#include <cmath>

namespace etrobocon2019_test{
  TEST(Distance, getDistanceTest1)
  {
    Distance dist;
    Controller controller;
    const int radius = 50;

    int leftAngle = 10;
    int rightAngle = 11;
    double angle = static_cast<double>(leftAngle + rightAngle) / 2.0;
    double expected = 2.0 * M_PI * radius * angle / 360.0;
  
    ASSERT_EQ(expected, dist.getDistance(leftAngle, rightAngle));
  }
  TEST(Distance, getDistanceTest2)
  {
    Distance dist;
    Controller controller;
    const int radius = 50;

    int leftAngle = 10;
    int rightAngle = 11;
    double angle = static_cast<double>(leftAngle + rightAngle) / 2.0;
    double expected = 2.0 * M_PI * radius * angle / 360.0;
  
    ASSERT_EQ(expected, dist.getDistance(leftAngle, rightAngle));
  }
}
