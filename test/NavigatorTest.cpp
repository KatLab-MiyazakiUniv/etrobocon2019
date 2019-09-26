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
    int targetBrightness = 70;
    Navigator navigator(controller, targetBrightness);
  }

  TEST(Navigator, moveForwardTest)
  {
    Controller controller;
    Distance distance;
    int targetBrightness = 70;
    Navigator navigator(controller, targetBrightness);

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
    int targetBrightness = 70;
    Navigator navigator(controller, targetBrightness);

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
    int targetBrightness = 70;
    Navigator navigator(controller, targetBrightness);

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

  TEST(Navigator, moveBackwardTest)
  {
    Controller controller;
    Distance distance;
    int targetBrightness = 70;
    Navigator navigator(controller, targetBrightness);

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
    int targetBrightness = 70;
    Navigator navigator(controller, targetBrightness);

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
    int targetBrightness = 70;
    Navigator navigator(controller, targetBrightness);

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

  TEST(Navigator, moveByPidForward)
  {
    Controller controller;
    Distance distance;
    int targetBrightness = 70;
    Navigator navigator(controller, targetBrightness);

    double expected = 1000.0;
    double start
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    navigator.move(expected, 30, 0.3);

    double end
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
    ASSERT_LE(expected, end - start);
  }

  TEST(Navigator, moveByPidBackward)
  {
    Controller controller;
    Distance distance;
    int targetBrightness = 70;
    Navigator navigator(controller, targetBrightness);

    double expected = -1000.0;
    double start
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());

    navigator.move(expected, 30, 0.3);

    double end
        = distance.getDistance(controller.getLeftMotorCount(), controller.getRightMotorCount());
    ASSERT_LE(end - start, expected);
  }

  TEST(Navigator, moveToSpecifiedColorTest)
  {
    Controller controller;
    int targetBrightness = 70;
    Navigator navigator(controller, targetBrightness);

    Color expected = Color::black;

    navigator.moveToSpecifiedColor(expected);

    int r = 0;
    int g = 0;
    int b = 0;
    controller.getRawColor(r, g, b);
    controller.convertHsv(r, g, b);
    Color actual = controller.hsvToColor(controller.getHsv());

    ASSERT_EQ(expected, actual);
  }

  TEST(Navigator, spin)
  {
    Controller controller;
    Rotation rotation;
    int targetBrightness = 70;
    Navigator navigator(controller, targetBrightness);

    double expected = 90;
    navigator.spin(expected);

    double actual
        = rotation.calculate(controller.getLeftMotorCount(), controller.getRightMotorCount());

    // 回頭角度の精度は、期待出力 + 5度まで許容する
    ASSERT_LE(expected, actual);
    ASSERT_GE(expected + 5, actual);
  }
}  // namespace etrobocon2019_test
