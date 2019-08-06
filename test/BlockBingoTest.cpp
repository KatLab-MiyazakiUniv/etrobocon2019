/**
 *  @file   BlockBingo.cpp
 *  @brief  BlockBingoクラスのテストファイル
 *  @author Oiwane
 */
#include <gtest/gtest.h>
#include "BlockBingo.h"

namespace etrobocon2019_test {

  TEST(BlockBingo, init)
  {
    Controller controller;
    BlockBingo blockbing(controller);
  }

  TEST(BlockBingo, moveCircle4OfLTEST)
  {
    Controller controller;
    BlockBingo blockbingo(controller);

    blockbingo.moveCircle4OfL();
  }

  TEST(BlockBingo, execOrderTest)
  {
    Controller controller;
    BlockBingo blockbingo(controller);
    Distance distance;
    std::array<OrderProperty, 1> propertys = { { Order::MOVE, 0.0, Color::black } };

    blockbingo.execOrder<1>(propertys);

    int leftAngle = controller.getLeftMotorCount();
    int rightAngle = controller.getRightMotorCount();

    double actualDistance = distance.getDistance(leftAngle, rightAngle);
    double expectedDistance = 350.0;

    ASSERT_LE(expectedDistance, actualDistance);
    ASSERT_LE(actualDistance, expectedDistance + 5.0);

    propertys = { { Order::SPIN, 45.0, Color::black } };
    blockbingo.execOrder<1>(propertys);
    // 特にテストなし

    Color expectedColor = Color::yellow;
    propertys = { { Order::COLOR, 0.0, expectedColor } };
    blockbingo.execOrder<1>(propertys);

    int r = 0;
    int g = 0;
    int b = 0;
    controller.getRawColor(r, g, b);
    controller.convertHsv(r, g, b);
    Color actualColor = controller.hsvToColor(controller.getHsv());

    ASSERT_EQ(expectedColor, actualColor);
  }
}  // namespace etrobocon2019_test
