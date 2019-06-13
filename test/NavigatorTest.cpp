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

  /* TEST(Navigator, moveForwardTest)
   {
     Controller controller;
     Navigator navigator(controller);

     navigator.move(1000);
   }
 */
  TEST(Navigator, moveForwardTestExistPwm)
  {
    Controller controller;
    Navigator navigator(controller);

    navigator.move(1000, 50);
  }

  TEST(Navigator, moveBackwardTest)
  {
    Controller controller;
    Navigator navigator(controller);

    navigator.move(-1000);
  }

  TEST(Navigator, moveBackwardTestExistPwm)
  {
    Controller controller;
    Navigator navigator(controller);

    navigator.move(-1000, 50);
  }
}  // namespace etrobocon2019_test
