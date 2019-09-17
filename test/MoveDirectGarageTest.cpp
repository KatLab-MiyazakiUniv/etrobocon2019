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
    Controller controller;
    MoveDirectGarage moveDirectGarage(controller);
  }

  TEST(MoveDirectGarage, MoveDirectGarageTest_init)
  {
    Controller controller;
    MoveDirectGarage moveDirectGarageR();
  }

  TEST(MoveDirectGarage, MoveDirectGarageTest_init)
  {
    Controller controller;
    MoveDirectGarage moveDirectGarageL();
  }


}  // namespace etrobocon2019_test