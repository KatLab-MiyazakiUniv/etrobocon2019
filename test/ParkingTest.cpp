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

  TEST(Parking, L_ParkingTest)
  {
    int targetBrightness = 70;
    Controller controller;
    Parking parking(controller, targetBrightness);

    Parking parkAtAL();
  }

  TEST(Parking, R_ParkingTest)
  {
    int targetBrightness = 70;
    Controller controller;
    Parking parking(controller, targetBrightness);

    Parking parkAtAR();
  }


}  // namespace etrobocon2019_test
