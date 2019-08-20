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

  TEST(BlockBingo, execOrderMoveTest)
  {
    Controller controller;
    BlockBingo blockbingo(controller);
    Distance distance;
    std::array<OrderProperty, 1> propertys = { { Order::MOVE, 0.0, Color::black } };

    blockbingo.execOrder<1>(propertys);

    int leftAngle = controller.getLeftMotorCount();
    int rightAngle = controller.getRightMotorCount();

    double actual = distance.getDistance(leftAngle, rightAngle);
    double expected = 350.0;

    ASSERT_LE(expected, actual);
    ASSERT_LE(actual, expected + 5.0);
  }

  TEST(BlockBingo, execOrderSpinTest)
  {
    Controller controller;
    BlockBingo blockbingo(controller);

    std::array<OrderProperty, 1> propertys = { { Order::SPIN, 45.0, Color::black } };
    blockbingo.execOrder<1>(propertys);
  }

  TEST(BlockBingo, execOrderColorTest)
  {
    Controller controller;
    BlockBingo blockbingo(controller);

    std::array<OrderProperty, 1> propertys = { { Order::COLOR, 0.0, Color::black } };
    blockbingo.execOrder<1>(propertys);

    int r = 0;
    int g = 0;
    int b = 0;
    controller.getRawColor(r, g, b);
    controller.convertHsv(r, g, b);
    Color actual = controller.hsvToColor(controller.getHsv());

    ASSERT_TRUE(propertys[0].paramColor == actual);
  }
}  // namespace etrobocon2019_test
