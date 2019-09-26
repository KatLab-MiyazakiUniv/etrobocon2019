/**
 *  @file   ParkingTest.cpp
 *  @brief  Parkingクラスのテストファイル
 *  @author Oiwane
 */
#include <gtest/gtest.h>
#include "Parking.h"

namespace etrobocon2019_test {

  TEST(Parking, ParkingTest_init)
  {
    int targetBrightness = 70;
    Controller controller;
    Parking parking(controller, targetBrightness);
  }

}  // namespace etrobocon2019_test
