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
    Navigator navigator(controller);

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

  TEST(Navigator, moveAtSpecifiedSpeedTestForward)
  {
    Controller controller;
    Distance distance;
    Navigator navigator(controller);

    navigator.setPidGain(0.60, 0.05, 0.04);

    double expected = 1000.0;
    double start
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    navigator.moveAtSpecifiedSpeed(expected, 50);

    double end
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
    double mileage = end - start;

    ASSERT_LE(expected, mileage);
    ASSERT_LE(mileage, expected + 5.0);
  }

  TEST(Navigator, moveAtSpecifiedSpeedByPidTestForward)
  {
    Controller controller;
    Distance distance;
    Navigator navigator(controller);

    navigator.setPidGain(0.60, 0.05, 0.04);

    double expected = 1000.0;
    double start
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    navigator.moveAtSpecifiedSpeedByPid(expected, 50);

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
    Navigator navigator(controller);

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
    Navigator navigator(controller);

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

  TEST(Navigator, moveAtSpecifiedSpeedTestBackward)
  {
    Controller controller;
    Distance distance;
    Navigator navigator(controller);

    navigator.setPidGain(0.60, 0.05, 0.04);

    double expected = -1000.0;
    double start
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    navigator.moveAtSpecifiedSpeed(expected, 50);

    double end
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
    double mileage = end - start;

    ASSERT_LE(expected - 5.0, mileage);
    ASSERT_LE(mileage, expected);
  }

  TEST(Navigator, moveAtSpecifiedSpeedByPidTestBackward)
  {
    Controller controller;
    Distance distance;
    Navigator navigator(controller);

    navigator.setPidGain(0.60, 0.05, 0.04);

    double expected = -1000.0;
    double start
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    navigator.moveAtSpecifiedSpeedByPid(expected, 50);

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
    Navigator navigator(controller);

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
    Navigator navigator(controller);

    double expected = -1000.0;
    double start
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    navigator.moveByPid(expected, 30);

    double end
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
    ASSERT_LE(end - start, expected);
  }
}  // namespace etrobocon2019_test
