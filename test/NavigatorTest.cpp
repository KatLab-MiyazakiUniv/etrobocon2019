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
    SpeedControl speedControl(controller, 50, 0.6, 0.05, 0.04);
    Navigator navigator(controller, speedControl);
  }

  TEST(Navigator, moveForwardTest)
  {
    Controller controller;
    Distance distance;
    SpeedControl speedControl(controller, 50, 0.6, 0.05, 0.04);
    Navigator navigator(controller, speedControl);

    double expected = 1000.0;
    double start
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    navigator.move(expected);

    double end
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
    double mileage = end - start;

    ASSERT_LE(expected, mileage);
    ASSERT_LE(mileage, expected + 5.0);
  }

  TEST(Navigator, moveForwardTestExistPwm)
  {
    Controller controller;
    Distance distance;
    SpeedControl speedControl(controller, 50, 0.6, 0.05, 0.04);
    Navigator navigator(controller, speedControl);

    double expected = 1000.0;
    double start
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    navigator.move(expected, 50);

    double end
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
    double mileage = end - start;

    ASSERT_LE(expected, mileage);
    ASSERT_LE(mileage, expected + 5.0);
  }

  TEST(Navigator, moveBySpeedTestForward)
  {
    Controller controller;
    Distance distance;
    SpeedControl speedControl(controller, 50, 0.6, 0.05, 0.04);
    Navigator navigator(controller, speedControl);

    double expected = 1000.0;
    double start
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    navigator.moveBySpeed(expected, 50);

    double end
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
    double mileage = end - start;

    ASSERT_LE(expected, mileage);
    ASSERT_LE(mileage, expected + 5.0);
  }

  TEST(Navigator, moveByPidAndSpeedTestForward)
  {
    Controller controller;
    Distance distance;
    SpeedControl speedControl(controller, 50, 0.6, 0.05, 0.04);
    Navigator navigator(controller, speedControl);

    double expected = 1000.0;
    double start
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    navigator.moveByPidAndSpeed(expected, 50);

    double end
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
    double mileage = end - start;

    ASSERT_LE(expected, mileage);
    ASSERT_LE(mileage, expected + 5.0);
  }

  TEST(Navigator, moveBackwardTest)
  {
    Controller controller;
    Distance distance;
    SpeedControl speedControl(controller, 50, 0.6, 0.05, 0.04);
    Navigator navigator(controller, speedControl);

    double expected = -1000.0;
    double start
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    navigator.move(expected);

    double end
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
    double mileage = end - start;

    ASSERT_LE(expected - 5.0, mileage);
    ASSERT_LE(mileage, expected);
  }

  TEST(Navigator, moveBackwardTestExistPwm)
  {
    Controller controller;
    Distance distance;
    SpeedControl speedControl(controller, 50, 0.6, 0.05, 0.04);
    Navigator navigator(controller, speedControl);

    double expected = -1000.0;
    double start
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    navigator.move(expected, 50);

    double end
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
    double mileage = end - start;

    ASSERT_LE(expected - 5.0, mileage);
    ASSERT_LE(mileage, expected);
  }

  TEST(Navigator, moveBySpeedTestBackward)
  {
    Controller controller;
    Distance distance;
    SpeedControl speedControl(controller, 50, 0.6, 0.05, 0.04);
    Navigator navigator(controller, speedControl);

    double expected = -1000.0;
    double start
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    navigator.moveBySpeed(expected, 50);

    double end
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
    double mileage = end - start;

    ASSERT_LE(expected - 5.0, mileage);
    ASSERT_LE(mileage, expected);
  }

  TEST(Navigator, moveByPidAndSpeedTestBackward)
  {
    Controller controller;
    Distance distance;
    SpeedControl speedControl(controller, 50, 0.6, 0.05, 0.04);
    Navigator navigator(controller, speedControl);

    double expected = -1000.0;
    double start
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    navigator.moveByPidAndSpeed(expected, 50);

    double end
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
    double mileage = end - start;

    ASSERT_LE(expected - 5.0, mileage);
    ASSERT_LE(mileage, expected);
  }

  TEST(Navigator, moveByPidForward)
  {
    Controller controller;
    Distance distance;
    SpeedControl speedControl(controller, 50, 0.6, 0.05, 0.04);
    Navigator navigator(controller, speedControl);

    double expected = 1000.0;
    double start
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    navigator.moveByPid(expected, 30);

    double end
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
    ASSERT_LE(expected, end - start);
  }

  TEST(Navigator, moveByPidBackward)
  {
    Controller controller;
    Distance distance;
    SpeedControl speedControl(controller, 50, 0.6, 0.05, 0.04);
    Navigator navigator(controller, speedControl);

    double expected = -1000.0;
    double start
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    navigator.moveByPid(expected, 30);

    double end
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
    ASSERT_LE(end - start, expected);
  }
}  // namespace etrobocon2019_test
