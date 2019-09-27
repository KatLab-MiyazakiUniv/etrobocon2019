/**
 *  @file   MoveDirectGarageTest.cpp
 *  @brief  MoveDirectGarageクラスのテストファイル
 *  @author match97
 */
#include <gtest/gtest.h>
#include "MoveDirectGarage.h"

namespace etrobocon2019_test {

  TEST(MoveDirectGarage, MoveDirectGarageTest_init)
  {
    int targetBrightness = 70;
    Controller controller;
    MoveDirectGarage moveDirectGarage(controller, targetBrightness);
  }

  TEST(MoveDirectGarage, MoveDirectGarageRTest)
  {
    Controller controller;
    MoveDirectGarage moveDirectGarage(controller, targetBrightness);

    MoveDirectGarage moveDirectGarageR();
  }

  TEST(MoveDirectGarage, MoveDirectGarageLTest)
  {
    Controller controller;
    MoveDirectGarage moveDirectGarage(controller, targetBrightness);

    MoveDirectGarage moveDirectGarageL();
  }


}  // namespace etrobocon2019_test