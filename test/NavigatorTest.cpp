/**
 *  @file   NavigatorTest.cpp
 *  @brief  Navigatorクラスのテストファイル
 *  @author Oiwane,Harada
 */
#include <gtest/gtest.h>
#include "Navigator.h"

namespace etrobocon2019_test
{
  TEST(Navigator, NavigatorTest_init)
  {
    Controller controller;
    Navigator navigator(controller);
  }

  TEST(Navigator, moveForwardTest)
  {
    Controller controller;
    Distance dist;
    Navigator navigator(controller);

    int expected = 1000;
    double start = dist.getDistance(controller.leftWheel.getCount(), controller.rightWheel.getCount());
    
    navigator.move(expected);

    double end = dist.getDistance(controller.leftWheel.getCount(), controller.rightWheel.getCount());
    ASSERT_DOUBLE_EQ(static_cast<double>(expected), end - start);
  }

  TEST(Navigator, moveForwardTestExistPwm)
  {
    Controller controller;
    Navigator navigator(controller);

    int expected = 1000;
    double start = dist.getDistance(controller.leftWheel.getCount(), controller.rightWheel.getCount());

    navigator.move(1000, 50);
  
    double end = dist.getDistance(controller.leftWheel.getCount(), controller.rightWheel.getCount());
    ASSERT_DOUBLE_EQ(static_cast<double>(expected), end - start);
  }

  TEST(Navigator, moveBackwardTest)
  {
    Controller controller;
    Navigator navigator(controller);

    int expected = 1000;
    double start = dist.getDistance(controller.leftWheel.getCount(), controller.rightWheel.getCount());

    navigator.move(-1000);

    double end = dist.getDistance(controller.leftWheel.getCount(), controller.rightWheel.getCount());
    ASSERT_DOUBLE_EQ(static_cast<double>(expected), end - start);
  }

  TEST(Navigator, moveBackwardTestExistPwm)
  {
    Controller controller;
    Navigator navigator(controller);

    int expected = 1000;
    double start = dist.getDistance(controller.leftWheel.getCount(), controller.rightWheel.getCount());
    
    navigator.move(-1000, 50);

    double end = dist.getDistance(controller.leftWheel.getCount(), controller.rightWheel.getCount());
    ASSERT_DOUBLE_EQ(static_cast<double>(expected), end - start);
  }
}  // namespace etrobocon2019_test
