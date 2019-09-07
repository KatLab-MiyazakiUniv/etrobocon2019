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
    Controller controller;
    Parking parking(controller);
  }

}  // namespace etrobocon2019_test
