#include "Distance.h"
#include <gtest/gtest.h>

namespace {
  TEST(DistanceTest, testgetAngle1)
  {
    current_angle = 10;
    pre_angle = 5;
  }
  TEST(DistanceTest, testgetAngle2)
  {
    current_angle = -10;
    pre_angle = 5;
  }
}