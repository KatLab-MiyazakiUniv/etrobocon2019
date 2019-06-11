/**
 *  @file   NavigatorTest.cpp
 *  @brief  Navigatorクラスのテストファイル
 *  @author Oiwane
 */
#include <gtest/gtest.h>
#include "Navigator.h"

namespace etrobocon2019_test
{
TEST(Navigator, NavigatorTest_init)
{
  Navigator navigator;
}

TEST(Navigator, NavigatorTest_init_existArgs)
{
  Controller controller;
  Navigator navigator(controller);
}

TEST(Navigator, moveForwardTest)
{
  Navigator navigator;

  navigator.move(1000);
}

TEST(Navigator, moveForwardTestExistPwm)
{
  Navigator navigator;

  navigator.move(1000, 50);
}

TEST(Navigator, moveBackTest)
{
  Navigator navigator;

  navigator.move(-1000);
}

TEST(Navigator, moveBackTestExistPwm)
{
  Navigator navigator;

  navigator.move(-1000, 50);
}
} // namespace etrobocon2019_test
