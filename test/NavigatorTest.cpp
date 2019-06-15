/**
 *  @file   NavigatorTest.cpp
 *  @brief  Navigatorクラスのテストファイル
 *  @author Oiwane,Harada
 */
#include <gtest/gtest.h>
#include "Navigator.h"

namespace etrobocon2019_test {
  TEST(Navigator, NavigatorTest_init)
  {
    Controller controller;
    Navigator navigator(controller);
  }

  TEST(Navigator, moveForwardTest)
  {
    Controller controller;
    Distance distance;
    Navigator navigator(controller);

    double expected = 1000.0;
    double start
        = distance.getDistance(controller.leftWheel.getCount(), controller.rightWheel.getCount());

    navigator.move(expected);

    double end
        = distance.getDistance(controller.leftWheel.getCount(), controller.rightWheel.getCount());
    double mileage = end - start;

    ASSERT_LE(expected, mileage);
    ASSERT_LE(mileage, expected + 5.0);
  }

  TEST(Navigator, moveForwardTestExistPwm)
  {
    Controller controller;
    Distance distance;
    Navigator navigator(controller);

    double expected = 1000.0;
    double start
        = distance.getDistance(controller.leftWheel.getCount(), controller.rightWheel.getCount());

    navigator.move(expected, 50);

    double end
        = distance.getDistance(controller.leftWheel.getCount(), controller.rightWheel.getCount());
    double mileage = end - start;

    ASSERT_LE(expected, mileage);
    ASSERT_LE(mileage, expected + 5.0);
  }

  TEST(Navigator, moveBackwardTest)
  {
    Controller controller;
    Distance distance;
    Navigator navigator(controller);

    double expected = -1000.0;
    double start
        = distance.getDistance(controller.leftWheel.getCount(), controller.rightWheel.getCount());

    navigator.move(expected);

    double end
        = distance.getDistance(controller.leftWheel.getCount(), controller.rightWheel.getCount());
    double mileage = end - start;

    ASSERT_LE(expected - 5.0, mileage);
    ASSERT_LE(mileage, expected);
  }

  TEST(Navigator, moveBackwardTestExistPwm)
  {
    Controller controller;
    Distance distance;
    Navigator navigator(controller);

    double expected = -1000.0;
    double start
        = distance.getDistance(controller.leftWheel.getCount(), controller.rightWheel.getCount());

    navigator.move(expected, 50);

    double end
        = distance.getDistance(controller.leftWheel.getCount(), controller.rightWheel.getCount());
    double mileage = end - start;

    ASSERT_LE(expected - 5.0, mileage);
    ASSERT_LE(mileage, expected);
  }
}  // namespace etrobocon2019_test
